#ifndef VIDEOINFORMATION_H
#define VIDEOINFORMATION_H

#include<QString>
extern "C"{
    #include<libavcodec/avcodec.h>
    #include<libavformat/avformat.h>
};

class VideoInformation
{
public:
    VideoInformation();
    ~VideoInformation(){
        avformat_close_input(&input_AVFormat_context);
    }

    //获取视频信息
    void getVideoInfo(QString file_path);

    //获取格式
    QString getFormat(){
        return format;
    }

    //获取视频长度
    QString getDuration(){
        return duration;
    }

    //获取视频帧率
    int getFrameRate(){
        return frame_rate;
    }

    //获取视频码率
    int getVideoAverageBitRate(){
            return this->video_average_bit_rate;
    }

    //获取视频宽度
    int getWidth(){
        return width;
    }

    //获取视频高度
    int getHeight(){
        return height;
    }

    //获取视频流大小
    float getVideoSize(){
        return video_size;
    }

    //获取视频编码方式
    QString getVideoFormat(){
        return video_format;
    }

    //获取音频编码
    QString getAudioFormat(){
        return audio_format;
    }

    //获取音频平均码率
    int getAudioAverageBitRate(){
        return audio_average_bit_rate;
    }

    //获取音频通道
    int getChannelNumbers(){
        return channel_nums;
    }

    //获取音频采样率
    int getSampleRate(){
        return sample_rate;
    }

    //获取音频大小
    float getAudioSize(){
        return audio_size;
    }


private:
    AVFormatContext* input_AVFormat_context;

    //流数
    unsigned int stream_numbers;

    //视频流索引号
    unsigned int video_stream_index;
    //音频流索引号
    unsigned int audio_stream_index;

    //视频、音频共有属性
    QString format;//格式
    QString duration;//时长

    //视频
    int frame_rate;//帧率
    int video_average_bit_rate;//平均码率
    int width;//宽度
    int height;//高度
    float video_size;//视频流大小
    QString video_format;//视频编码格式

    //音频
    QString audio_format;//音频编码格式
    int audio_average_bit_rate;//音频平均码率
    int channel_nums;//声道数
    int sample_rate;//采样率
    int audio_size;//音频流大小
};

#endif // VIDEOINFORMATION_H
