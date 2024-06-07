#pragma once
#include <Windows.h>
#include <xaudio2.h>

#include <memory>

#include <unordered_map>
#include <vector>

struct XAudio {
	WAVEFORMATEXTENSIBLE wfx = { 0 };
	XAUDIO2_BUFFER buffer = { 0 };
};

class SoundSystem;

class SoundSystemSourceCallback : public IXAudio2VoiceCallback
{
public:
	/*IXAudio2VoiceCallback Overrides*/
	// Called when the voice has just finished playing a contiguous audio stream.
	void STDMETHODCALLTYPE OnBufferEnd(void* pBufferContext) override;
	// Called when the voice reaches the end position of a loop.
	void STDMETHODCALLTYPE OnLoopEnd(void* pBufferContext) override;
	// Called when the voice has just finished processing a buffer.
	void STDMETHODCALLTYPE OnBufferStart(void* pBufferContext) override;
	// Called just after the voice is about to start processing a new stream.
	void STDMETHODCALLTYPE OnStreamEnd() override;
	// Called when the voice is about to start processing a new voice loop.
	void STDMETHODCALLTYPE OnVoiceProcessingPassEnd() override;
	// Called when the voice is about to start processing a new voice loop.
	void STDMETHODCALLTYPE OnVoiceProcessingPassStart(UINT32 BytesRequired) override;
	// Called when the voice encounters a critical error during processing.
	void STDMETHODCALLTYPE OnVoiceError(void* pBufferContext, HRESULT Error) override;

	IXAudio2SourceVoice* source = nullptr;
	SoundSystem* sSystem = nullptr;

	SoundSystemSourceCallback(SoundSystem* sSystem) :sSystem{ sSystem } {};
	~SoundSystemSourceCallback() { /* Hopefully you would have destroyed source */ }
};

class SoundSystem {
public:
	SoundSystem();
	~SoundSystem();
private:
	IXAudio2* pXAudio2 = nullptr;
	IXAudio2MasteringVoice* pMasterVoice = nullptr;

	std::unordered_map<LPCWSTR, XAudio*>Sources{};
	std::vector<std::shared_ptr<SoundSystemSourceCallback>> callbackContainer;

public:
	HRESULT Init();
	void Release();
	XAudio CreateAudio(LPCWSTR src);
	void AddAudio(LPCWSTR src, XAudio* audio = nullptr);

	HRESULT PlayAudio(LPCWSTR src, const float& volume = 1.f);
	HRESULT PlayAudio(XAudio* audio, const float& volume = 1.f);
};

inline SoundSystem* soundSystem = nullptr;