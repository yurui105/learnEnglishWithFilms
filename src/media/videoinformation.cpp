#include "videoinformation.h"

VideoInformation::VideoInformation()
{
    //动态申请内存
    input_AVFormat_context = avformat_alloc_context();
}

void VideoInformation::getVideoInfo(QString file_path)
{
    if(avformat_open_input(&input_AVFormat_context,file_path.toStdString().c_str(),0,NULL)<0){
        //打开文件失败
        return;
    }

    if(avformat_find_stream_info(input_AVFormat_context,NULL)<0){
        //error
        return;
    }

    //获取数据流
    stream_numbers = input_AVFormat_context->nb_streams;

    //计算视频长度
    int hours,mins,secs;
    secs = input_AVFormat_context->duration/1000000;
    mins = secs/60;
    secs %=60;
    hours = mins/60;
    mins %= 60;

    //格式化视频长度
    duration = QString("%1:%2:%3").arg(hours).arg(mins).arg(mins);

    //获取视频的封装格式
    AVInputFormat* infoFormat = input_AVFormat_context->iformat;
    format = infoFormat->name;

    //遍历视频流
    for (unsigned int i = 0;i<stream_numbers ;i++ ) {
        //取出一路视频流，并生成aVStream对象
        AVStream* input_stream = input_AVFormat_context->streams[i];

        //判断是否为视频
        if(input_stream->codecpar->codec_type == AVMEDIA_TYPE_VIDEO){
            //avg_frame_rate = avg_grame_rate.num(分子)/avg_frame_den(分母)
            frame_rate = input_stream->avg_frame_rate.num/input_stream->avg_frame_rate.den;

            //取出视频流中的编码参数，生成部分AVCodecParamters对象
            AVCodecParameters* codec_par = input_stream->codecpar;

            //利用编码参数对象AVCdecParamters得到视频宽度，高度，码率，视频大小
            width = codec_par->width;
            height = codec_par->height;
            video_average_bit_rate = codec_par->bit_rate/1000;
            video_size = video_average_bit_rate*secs/(8.0*1024);

            //利用avcodec_paramters_to_context()函数产生AVCodecContext对象
            //input_stream->codec已经被淘汰，不推荐使用这种方式生成AVCodecContext
            AVCodecContext* avctx_video;
            avctx_video = avcodec_alloc_context3(NULL);
            int ret = avcodec_parameters_to_context(avctx_video,codec_par);
            if(ret < 0){
                avcodec_free_context(&avctx_video);
                return;
            }

            //获取视频编码方式
            video_format = avcodec_get_name(codec_par->codec_id);

        //当输入为音频时
        }else if(input_stream->codecpar->codec_type == AVMEDIA_TYPE_AUDIO){
            AVCodecParameters* codec_par = input_stream->codecpar;
            AVCodecContext* avctx_audio;
            avctx_audio = avcodec_alloc_context3(NULL);
            int ret = avcodec_parameters_to_context(avctx_audio,codec_par);
            if(ret<0){
                avcodec_free_context(&avctx_audio);
                return;
            }

            audio_format = avcodec_get_name(avctx_audio->codec_id);
            audio_average_bit_rate = codec_par->bit_rate/1000;
            channel_nums = codec_par->channels;
            sample_rate = codec_par->sample_rate;
            audio_size = audio_average_bit_rate*secs/(8.0*1024);
        }
    }
}


