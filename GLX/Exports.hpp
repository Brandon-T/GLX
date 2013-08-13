#ifndef EXPORTS_HPP_INCLUDED
#define EXPORTS_HPP_INCLUDED

#include <cstring>
#include <vector>
#include <memory>
#include "Platform.hpp"
#include "Structures.hpp"
#include "SharedMemory.hpp"

#define ExportCount         13
#define SharedImageSize     8294400     //Highest Resolution Support: 1920 x 1080 x sizeof(RGBA)
#define TotalImageSize      (SharedImageSize * 2)  //Image + DebugImage
#define SharedHookSize      5000000

extern char* Exports[];
extern HINSTANCE hInstance;

extern std::string SharedImageName;
extern std::string SharedHookName;
extern std::unique_ptr<SharedMemory> SharedImageData;
extern std::unique_ptr<SharedMemory> SharedHookData;

extern "C" int __declspec(dllexport) GetPluginABIVersion();
extern "C" int __declspec(dllexport) GetFunctionCount();
extern "C" int __declspec(dllexport) GetFunctionInfo(int Index, void* &Address, char* &Definition);

extern "C" bool __declspec(dllexport) GLXSetup(int ProcessID);
extern "C" bool __declspec(dllexport) GLXMapHooks(int ProcessID);
extern "C" void* __declspec(dllexport) GLXImagePointer();
extern "C" void* __declspec(dllexport) GLXDebugPointer();
extern "C" void __declspec(dllexport) GLXViewPort(int &X1, int &Y1, int &X2, int &Y2);
extern "C" Texture* __declspec(dllexport) GLXTextures(std::uint32_t &Size);
extern "C" Model* __declspec(dllexport) GLXModels(std::uint32_t &Size);
extern "C" Font* __declspec(dllexport) GLXFonts(std::uint32_t &Size);
extern "C" Matrices* __declspec(dllexport) GLXMatrices();
extern "C" std::uint8_t* __declspec(dllexport) GLXMap(int &Width, int &Height, float X[4], float Y[4]);
extern "C" void __declspec(dllexport) GLXMapCoords(float X[4], float Y[4]);
extern "C" void __declspec(dllexport) GLXDebug(std::uint32_t Mode, std::uint32_t HudID, int X1, int Y1, int X2, int Y2);
extern "C" void __declspec(dllexport) GLXSetColourCapture(bool Enabled);

extern void GetDesktopResolution(int &width, int &height);
extern bool CreateSharedMemory(int ProcessID);
extern bool OpenSharedMemory(int ProcessID);
extern bool MapHooks(int ProcessID);
extern bool UnMapSharedMemory();

#endif // EXPORTS_HPP_INCLUDED
