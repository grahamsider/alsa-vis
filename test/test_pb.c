/**
 * Test playback program to write pseudo-random 
 * bits to ALSA PCM driver. If using pulse, run
 * with:                 pasuspend -- ./test_pb
 */

#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>

#define PCM_DEVICE "default"

int main(int argc, char *argv[])
{
    printf("[ test_pb ] Start\n");
    
    int   err;
    short hw_buf[128];

    snd_pcm_t           *pcm_handle;
    snd_pcm_hw_params_t *hw_params;

    // Open PCM Device
    if ((err = snd_pcm_open (&pcm_handle, PCM_DEVICE, SND_PCM_STREAM_PLAYBACK, 0)) < 0)
    {
        fprintf(stderr, "[ test_pb ] Error: Cannot open audio device %s (%s)\n",
                PCM_DEVICE,
                snd_strerror(err));
        exit(1);
    }

    // Close PCM Device
    snd_pcm_close(pcm_handle);

    printf("[ test_pb ] End\n");
    return(0);
}
