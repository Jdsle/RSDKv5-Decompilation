#define LockAudioDevice()   SDL_LockAudioDevice(AudioDevice::device)
#define UnlockAudioDevice() SDL_UnlockAudioDevice(AudioDevice::device)

#include <thread>

namespace RSDK
{
class AudioDevice : public AudioDeviceBase
{
public:
    static SDL_AudioDeviceID device;

    static bool32 Init();
    static void Release();

    static void FrameInit() {}

    inline static void HandleStreamLoad(ChannelInfo *channel, bool32 async)
    {
        if (async) {
            // SDL_CreateThread((SDL_ThreadFunction)LoadStream, "LoadStream", (void *)channel);

            // ... we don't talk about this
            std::thread thread(LoadStream, channel);
            thread.detach();
        }
        else {
            LoadStream(channel);
        }
    }

private:
    static SDL_AudioSpec deviceSpec;

    static uint8 contextInitialized;

    static void InitAudioChannels();

    static void AudioCallback(void *data, uint8 *stream, int32 len);
};
} // namespace RSDK