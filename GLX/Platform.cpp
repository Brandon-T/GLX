#include "Platform.hpp"

/** @file Platform.hpp */

Library::Library(std::string Library)
{
    #if defined _WIN32 || defined _WIN64
    this->Module = LoadLibrary(Library.c_str());
    #else
    this->Module = dlopen(Library.c_str(), RTLD_LAZY);
    #endif
}

Library::~Library()
{
    #if defined _WIN32 || defined _WIN64
    FreeLibrary(static_cast<HMODULE>(this->Module));
    #else
    dlclose(this->Module);
    #endif
}

/*
bool Library::xGetFunctionAddress(void* FunctionDefinition, std::string FunctionName)
{
    return *static_cast<std::int64_t(__stdcall **)()>(FunctionDefinition) = this->xGetProcAddress(FunctionName.c_str());
}
*/
