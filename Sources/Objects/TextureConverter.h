#pragma once
#include <string>
#include <wrl.h>
#include <cassert>
#include <filesystem>
#include <External/DirectXTex/DirectXTex.h>
#include "../Functions/Functions.h"
using namespace DirectX;

class TextureConverter{
public:
    void ConvertTextureWicToDDS(const std::string& inputFilePath);

private:
    void LoadWICTextureFromFile(const std::string& filePath);
    void CompressTexture();

private:
    DirectX::TexMetadata metadata_;
    DirectX::ScratchImage scratchImage_;
    std::wstring directoryPath_;
    std::wstring fileName_;
    std::wstring fileExt_;
};

