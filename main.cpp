#include "Sources/Functions/Functions.h"
#include "Sources/Objects/TextureConverter.h"
#include "Sources/Enums/MainFuncAuguments.h"

int main(int argc, char* argv[]){
    // コンバータの初期化
    HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    assert(SUCCEEDED(hr));

    // テクスチャの変換
    TextureConverter converter;
    converter.ConvertTextureWicToDDS(argv[(int)MainFuncAuguments::kInputFilePath]);

    system("pause");

    // コンバータの終了処理
    CoUninitialize();

    return 0;
};