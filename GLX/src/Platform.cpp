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

#include "Platform.hpp"

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
