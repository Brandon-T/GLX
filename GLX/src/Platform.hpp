/**  © 2013, Brandon T. All Rights Reserved.
  *
  *  This file is part of the GLX Library.
  *  GLX is free software: you can redistribute it and/or modify
  *  it under the terms of the GNU General Public License as published by
  *  the Free Software Foundation, either version 3 of the License, or
  *  (at your option) any later version.
  *
  *  GLX is distributed in the hope that it will be useful,
  *  but WITHOUT ANY WARRANTY; without even the implied warranty of
  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  *  GNU General Public License for more details.
  *
  *  You should have received a copy of the GNU General Public License
  *  along with GLX.  If not, see <http://www.gnu.org/licenses/>.
  */

#ifndef PLATFORM_HPP_INCLUDED
#define PLATFORM_HPP_INCLUDED

#if defined _WIN32 || defined _WIN64
#include <windows.h>
#else
#include <dlfcn.h>
#endif

#include <string>
#include <cstdint>
#include <stdexcept>

class Library
{
    private:
        void* Module;

    public:

        Library(std::string Library);
        ~Library();

        template<typename T>
        T FunctionAddress(std::string FunctionName);

        template<typename T>
        bool FunctionAddress(T &FunctionDefinition, std::string FunctionName);

        template<typename T, typename ...Args>
        auto CallFunction(void* Function, Args... args) -> decltype(reinterpret_cast<T>(Function)(args...));
};

template<typename T>
T Library::FunctionAddress(std::string FunctionName)
{
    #if defined _WIN32 || defined _WIN64
    T Result = reinterpret_cast<T>(GetProcAddress(static_cast<HMODULE>(this->Module), FunctionName.c_str()));
    return Result ? Result : throw std::runtime_error(FunctionName);
    #else
    T Result = reinterpret_cast<T>(dlsym(this->Module, FunctionName.c_str()));
    return Result ? Result : throw std::runtime_error(FunctionName);
    #endif
}

template<typename T>
bool Library::FunctionAddress(T &FunctionDefinition, std::string FunctionName)
{
    return (FunctionDefinition = this->FunctionAddress<T>(FunctionName));
}

template<typename T, typename ...Args>
auto Library::CallFunction(void* Function, Args... args) -> decltype(reinterpret_cast<T>(Function)(args...))
{
    return reinterpret_cast<T>(Function)(args...);
}

#endif // PLATFORM_HPP_INCLUDED
