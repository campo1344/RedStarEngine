#pragma once

#ifdef RSS_EXPORTS
#define RSS_API __declspec(dllexport)
#else
#define RSS_API __declspec(dllimport)
#endif

#define CALL __cdecl

#include <map>
#include <vector>
#include <iostream>

#ifdef __cplusplus
extern "C"
{
#endif

    RSS_API void CALL Check();
    class RSS_API Audio
    {
    private:
        std::map<std::string, std::string> soundList;

    public:
        Audio();
        ~Audio();
        void Init();
        void AddListSound(std::string nameSound, std::string FilePath);
        void Play(std::string nameSound);
        void Quit();
    };

#ifdef __cplusplus
}
#endif