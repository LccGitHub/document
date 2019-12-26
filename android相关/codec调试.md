# codec调试

## kernel生成的相关文件

     ls -l /proc/asound/card0/
     ls -l /sys/class/sound/
     ls -l /dev/snd


## wm9806的驱动 
### 播放音乐

    amix 'SEC_MI2S_RX Audio Mixer MultiMedia1' 1
    amix 'SIMCOM Switch Device' 'Handset' 2
    aplay /data/incoming.wav
    amix 'SIMCOM Switch Device' 'Sleep' 1



### 电话声音
    amix 'SEC_MI2S_RX_Voice Mixer CSVoice' 1
    amix 'Voice_Tx Mixer SEC_MI2S_TX_Voice' 1
    amix 'SIMCOM Switch Device' 'Handset' 2
    aplay -D hw:0,2 -P &
    arec -D hw:0,2 -P -R 8000 -C 1 &
    amix 'SIMCOM Set Mic Gain' 3
    amix 'SIMCOM Set Out Gain' 8




## nau88c10 驱动
### 播放音乐

    amix 'SEC_AUX_PCM_RX Audio Mixer MultiMedia1' 1
    aplay /data/incoming.wav




### 电话声音
    amix 'SEC_AUX_PCM_RX_Voice Mixer CSVoice' 1
    amix 'Voice_Tx Mixer SEC_AUX_PCM_TX_Voice' 1
    aplay -D hw:0,2 -P &
    arec -D hw:0,2 -P -R 8000 -C 1 &