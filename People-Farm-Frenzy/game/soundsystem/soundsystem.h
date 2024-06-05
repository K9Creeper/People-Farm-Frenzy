#pragma once
#include <Windows.h>
#include <xaudio2.h>

#include <unordered_map>
#include <vector>

struct XAudio {
	WAVEFORMATEXTENSIBLE wfx = { 0 };
	XAUDIO2_BUFFER buffer = { 0 };
};

class SoundSystem {
public:
	SoundSystem();
	~SoundSystem();
private:
	IXAudio2* pXAudio2 = nullptr;
	IXAudio2MasteringVoice* pMasterVoice = nullptr;

	std::unordered_map<LPCWSTR, XAudio*>Sources{};
	std::vector<IXAudio2SourceVoice*>Audio{};

	void ValidtateAudio();
public:
	HRESULT Init();
	void Release();
	XAudio CreateAudio(LPCWSTR src);
	void AddAudio(LPCWSTR src, XAudio* audio = nullptr);

	HRESULT PlayAudio(LPCWSTR src, const float& volume = 1.f);
	HRESULT PlayAudio(XAudio* audio, const float& volume = 1.f);

};

inline SoundSystem* soundSystem = nullptr;