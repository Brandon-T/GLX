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

#ifndef SYSTEM_HPP_INCLUDED
#define SYSTEM_HPP_INCLUDED

#include <string>

template<typename T>
struct is_literal
{
    enum {value = false};
};

template<>
struct is_literal<char>
{
    enum {value = true};
};

template<>
struct is_literal<char*>
{
    enum {value = true};
};

template<>
struct is_literal<const char*>
{
    enum {value = true};
};

template<typename Char, typename Traits, typename Alloc>
struct is_literal<std::basic_string<Char, Traits, Alloc>>
{
    enum {value = true};
};

template<typename T>
std::string to_string(T value)
{
    static_assert(is_literal<T>::value, "Argument: Value Must be of literal type.");
    std::string Result;
    Result += value;
    return Result;
}

template<typename T, typename U>
bool xDetour(T &FunctionDefinition, U FunctionAddress)
{
    return (FunctionDefinition = reinterpret_cast<T>(FunctionAddress));
}

#endif // SYSTEM_HPP_INCLUDED
