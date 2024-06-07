#include "soundsystem.h"

#ifdef _XBOX //Big-Endian
#define fourccRIFF 'RIFF'
#define fourccDATA 'data'
#define fourccFMT 'fmt '
#define fourccWAVE 'WAVE'
#define fourccXWMA 'XWMA'
#define fourccDPDS 'dpds'
#endif

#ifndef _XBOX //Little-Endian
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'
#endif

HRESULT SoundSystem::Init() {
	HRESULT hr;
	if (FAILED(hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED)))
		return hr;
	if (FAILED(hr = XAudio2Create(&pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR)))
		return hr;
	if (FAILED(hr = pXAudio2->CreateMasteringVoice(&pMasterVoice)))
		return hr;
}

void SoundSystem::Release() {
    for (auto& [src, s] : Sources)
        delete s;
    Sources.clear();

    pMasterVoice->DestroyVoice();
    pMasterVoice = nullptr;
    pXAudio2->Release();
    pXAudio2 = nullptr;

    callbackContainer.clear();

    CoUninitialize();
}

/* https://learn.microsoft.com/en-us/windows/win32/xaudio2/how-to--load-audio-data-files-in-xaudio2 */
HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition)
{
    HRESULT hr = S_OK;
    if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
        return HRESULT_FROM_WIN32(GetLastError());

    DWORD dwChunkType;
    DWORD dwChunkDataSize;
    DWORD dwRIFFDataSize = 0;
    DWORD dwFileType;
    DWORD bytesRead = 0;
    DWORD dwOffset = 0;

    while (hr == S_OK)
    {
        DWORD dwRead;
        if (0 == ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL))
            hr = HRESULT_FROM_WIN32(GetLastError());

        if (0 == ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL))
            hr = HRESULT_FROM_WIN32(GetLastError());

        switch (dwChunkType)
        {
        case fourccRIFF:
            dwRIFFDataSize = dwChunkDataSize;
            dwChunkDataSize = 4;
            if (0 == ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL))
                hr = HRESULT_FROM_WIN32(GetLastError());
            break;

        default:
            if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT))
                return HRESULT_FROM_WIN32(GetLastError());
        }

        dwOffset += sizeof(DWORD) * 2;

        if (dwChunkType == fourcc)
        {
            dwChunkSize = dwChunkDataSize;
            dwChunkDataPosition = dwOffset;
            return S_OK;
        }

        dwOffset += dwChunkDataSize;

        if (bytesRead >= dwRIFFDataSize) return S_FALSE;

    }

    return S_OK;

}

HRESULT ReadChunkData(HANDLE hFile, void* buffer, DWORD buffersize, DWORD bufferoffset)
{
	HRESULT hr = S_OK;
	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, bufferoffset, NULL, FILE_BEGIN))
		return HRESULT_FROM_WIN32(GetLastError());
	DWORD dwRead;
	if (0 == ReadFile(hFile, buffer, buffersize, &dwRead, NULL))
		hr = HRESULT_FROM_WIN32(GetLastError());
	return hr;
}

SoundSystem::SoundSystem(){}
SoundSystem::~SoundSystem() {
    if(pXAudio2)
        Release();
}

XAudio SoundSystem::CreateAudio(LPCWSTR src)
{
    XAudio out;
	HANDLE hFile = CreateFile(
		src,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return out;
	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
		return out;
	
	DWORD dwChunkSize;
	DWORD dwChunkPosition;
	//check the file type, should be fourccWAVE or 'XWMA'
	FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition);
	DWORD filetype;
	ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);
	if (filetype != fourccWAVE)
		return out;

    FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition);
    ReadChunkData(hFile, &out.wfx, dwChunkSize, dwChunkPosition);

    FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition);
    BYTE* pDataBuffer = new BYTE[dwChunkSize];
    ReadChunkData(hFile, pDataBuffer, dwChunkSize, dwChunkPosition);
    out.buffer.AudioBytes = dwChunkSize;
    out.buffer.pAudioData = pDataBuffer;
    out.buffer.Flags = XAUDIO2_END_OF_STREAM;
    return out;
}

void SoundSystem::AddAudio(LPCWSTR src, XAudio* AUD) {
    XAudio* audio = AUD;
    if (!audio)
    {
        audio = new XAudio(CreateAudio(src));
    }
    Sources[src] = audio;
}

HRESULT SoundSystem::PlayAudio(LPCWSTR src, const float& volume) {
    if (Sources.find(src) == Sources.end())
        AddAudio(src);
    XAudio* audio = Sources[src];
    return PlayAudio(audio, volume);
}

void STDMETHODCALLTYPE SoundSystemSourceCallback::OnBufferEnd(void* pBufferContext) {
    if (!source || !sSystem)
        return;
}
void STDMETHODCALLTYPE SoundSystemSourceCallback::OnLoopEnd(void* pBufferContext)  { 
    if (!source || !sSystem)
        return;
}
void STDMETHODCALLTYPE SoundSystemSourceCallback::OnBufferStart(void* pBufferContext) {
    if (!source || !sSystem)
        return;
}
void STDMETHODCALLTYPE SoundSystemSourceCallback::OnStreamEnd() {
    if (!source || !sSystem)
        return;
    source->DestroyVoice();
    source = nullptr;
}
void STDMETHODCALLTYPE SoundSystemSourceCallback::OnVoiceProcessingPassEnd() { 
    if (!source || !sSystem)
        return;
}
void STDMETHODCALLTYPE SoundSystemSourceCallback::OnVoiceProcessingPassStart(UINT32 BytesRequired) {
    if (!source || !sSystem)
        return;
}
void STDMETHODCALLTYPE SoundSystemSourceCallback::OnVoiceError(void* pBufferContext, HRESULT Error) { 
    if (!source || !sSystem)
        return;
}

HRESULT SoundSystem::PlayAudio(XAudio* audio, const float& volume) {
    if (!audio)
        return S_FALSE;
    IXAudio2SourceVoice* pSourceVoice;
    std::shared_ptr<SoundSystemSourceCallback> pCallBack = std::make_shared<SoundSystemSourceCallback>(this);
    callbackContainer.push_back(pCallBack);

    HRESULT hr;
    if (FAILED(hr = pXAudio2->CreateSourceVoice(&pSourceVoice, (WAVEFORMATEX*)&audio->wfx, 0U, 2.0F, pCallBack.get())))
    {
         return hr;
    }
    pCallBack->source = pSourceVoice;
    pSourceVoice->SetVolume(volume);
    if (FAILED(hr = pSourceVoice->SubmitSourceBuffer(&audio->buffer))) {
        delete pSourceVoice;

        return hr;
    }
    if (FAILED(hr = pSourceVoice->Start(0))) {
        delete pSourceVoice;
        return hr;
    }

    return S_OK;
}