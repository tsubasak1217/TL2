#include "TextureConverter.h"

void TextureConverter::ConvertTextureWicToDDS(const std::string& inputFilePath){
    // WICテクスチャをファイルから読み込む
    LoadWICTextureFromFile(inputFilePath);
    assert(scratchImage_.GetImageCount() > 0);

    // ファイル名を分解
    std::filesystem::path path = inputFilePath;
    directoryPath_ = path.parent_path().wstring();
    fileName_ = path.stem().wstring();
    fileExt_ = path.extension().wstring();

    // 画像を圧縮
    CompressTexture();

    // DDSファイルに保存
    std::wstring outputFilePath = directoryPath_ + L"\\" + fileName_ + L".dds";
    HRESULT hr = SaveToDDSFile(scratchImage_.GetImages(), scratchImage_.GetImageCount(), metadata_, DirectX::DDS_FLAGS_NONE, outputFilePath.c_str());
    assert(SUCCEEDED(hr));
    Print("Converted to " + ConvertString(outputFilePath));
}

// WICテクスチャをファイルから読み込む
void TextureConverter::LoadWICTextureFromFile(const std::string& filePath){

    // 文字列を変換
    std::wstring wFilePath = ConvertString(filePath);
    assert(!wFilePath.empty());

    // WICテクスチャを読み込む
    HRESULT hr = LoadFromWICFile(wFilePath.c_str(), DirectX::WIC_FLAGS_NONE, &metadata_, scratchImage_);
}

void TextureConverter::CompressTexture(){

    // mipmapの生成
    DirectX::ScratchImage mipChain;
    HRESULT hr = GenerateMipMaps(
        scratchImage_.GetImages(), scratchImage_.GetImageCount(), scratchImage_.GetMetadata(),
        TEX_FILTER_DEFAULT, 0, mipChain
    );
    if(SUCCEEDED(hr)){
        scratchImage_ = std::move(mipChain);
        metadata_ = scratchImage_.GetMetadata();
    }

    // 読み込んだ画像を圧縮
    metadata_.format = MakeSRGB(metadata_.format);
    DirectX::ScratchImage convertedImage;
    hr = Compress(
        scratchImage_.GetImages(), scratchImage_.GetImageCount(), metadata_,
        DXGI_FORMAT_BC7_UNORM_SRGB,
        TEX_COMPRESS_BC7_QUICK | TEX_COMPRESS_SRGB_OUT | TEX_COMPRESS_PARALLEL,
        1.0f, convertedImage
    );

    if(SUCCEEDED(hr)){
        scratchImage_ = std::move(convertedImage);
        metadata_ = scratchImage_.GetMetadata();
    }
}
