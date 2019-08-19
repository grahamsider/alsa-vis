/**
 * Test playback program to write pseudo-random 
 * bits to ALSA PCM driver. If using pulse, run
 * with:                 pasuspend -- ./test_pb
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <alsa/asoundlib.h>

#define PCM_DEVICE "default"

int alsa_init (snd_pcm_t **pcm_handle, snd_pcm_hw_params_t **hw_params)
{
    printf("[ TEST_PB ]\tInitializing ALSA...\n");
    int err;

    // Open PCM Device
    if ((err = snd_pcm_open (pcm_handle, PCM_DEVICE, SND_PCM_STREAM_PLAYBACK, 0)) < 0)
    {
        fprintf (stderr, "[ TEST_PB ]\tError: Cannot open audio device %s (%s)\n",
                 PCM_DEVICE,
                 snd_strerror (err));
        return (err);
    }

    // Allocate Space for HW Params
    if ((err = snd_pcm_hw_params_malloc (hw_params)) < 0)
    {
        fprintf (stderr, "[ TEST_PB ]\tError: Cannot allocate configuration space (%s)\n",
                 snd_strerror (err));
        snd_pcm_close (*pcm_handle);
        return (err);
    }

    return (0);
}


void alsa_close (snd_pcm_t **pcm_handle, snd_pcm_hw_params_t **hw_params)
{
    printf("[ TEST_PB ]\tClosing PCM...\n");

    // De-allocate Space for HW Params
    snd_pcm_hw_params_free (*hw_params);

    // Close PCM Device
    snd_pcm_close (*pcm_handle);
}

int main (int argc, char *argv[])
{
    short                 hw_buf[128];
    snd_pcm_t            *pcm_handle;
    snd_pcm_hw_params_t  *hw_params;

    if ((alsa_init (&pcm_handle, &hw_params)) < 0)
    {
        printf("[ TEST_PB ]\tExiting...");
        exit (1);
    }

    sleep (1);

    alsa_close (&pcm_handle, &hw_params);

    printf("[ TEST_PB ]\tDone.\n");
    return (0);
}
