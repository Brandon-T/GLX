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

#ifndef SERIALIZATION_H_INCLUDED
#define SERIALIZATION_H_INCLUDED

#include <vector>
#include <sstream>
#include <iostream>
#include <list>
#include <array>

class Serialize
{
    private:
        std::ostringstream Data;

    public:
        Serialize(const void* Buffer, std::size_t BufferSize) : Data()
        {
            Data.rdbuf()->pubsetbuf(const_cast<char*>(reinterpret_cast<const char*>(Buffer)), BufferSize);
        }

        template <typename T>
        friend Serialize& operator << (Serialize& Destination, const T& Value)
        {
            Destination.Data.write(reinterpret_cast<const char*>(&Value), sizeof(T));
            return Destination;
        }
};

template <typename T, typename Allocator>
Serialize& operator <<(Serialize& Destination, const std::vector<T, Allocator>& Value)
{
    typedef typename std::vector<T, Allocator>::const_iterator Iterator;
    Destination << Value.size();
    for(Iterator it = Value.begin(); it != Value.end(); ++it)
    {
        Destination << (*it);
    }
    return Destination;
}

template <typename T, typename Allocator>
Serialize& operator << (Serialize& Destination, const std::list<T, Allocator>& Value)
{
    typedef typename std::list<T, Allocator>::const_iterator Iterator;
    Destination << Value.size();
    for(Iterator it = Value.begin(); it != Value.end(); ++it)
    {
        Destination << (*it);
    }
    return Destination;
}

template <typename T, unsigned int Size>
Serialize& operator << (Serialize& Destination, const std::array<T, Size>& Value)
{
    typedef typename std::array<T, Size>::const_iterator Iterator;
    Destination << Value.size();
    for (Iterator it = Value.begin(); it != Value.end(); ++it)
    {
        Destination << (*it);
    }
    return Destination;
}

class DeSerialize
{
    private:
        std::istringstream Data;

    public:
        DeSerialize(const void *Buffer, std::size_t Size) : Data()
        {
            Data.rdbuf()->pubsetbuf(const_cast<char*>(reinterpret_cast<const char*>(Buffer)), Size);
        }

        template <typename T>
        friend DeSerialize& operator >> (DeSerialize& Source, T& Value)
        {
            Source.Data.read(reinterpret_cast<char*>(&Value), sizeof(T));
            return Source;
        }
};

template <typename T, typename Allocator>
DeSerialize& operator >> (DeSerialize& Source, std::vector<T, Allocator>& Value)
{
    typedef typename std::vector<T, Allocator>::size_type SizeType;
    SizeType Size;
    Source >> Size;
    Value.reserve(Size);
    for(SizeType I = 0; I < Size; ++I)
    {
        T Temp = T();
        Source >> Temp;
        Value.emplace_back(Temp);
    }
    return Source;
}

template <typename T, typename Allocator>
DeSerialize& operator >> (DeSerialize& Source, std::list<T, Allocator>& Value)
{
    typedef typename std::list<T, Allocator>::size_type SizeType;
    SizeType Size;
    Source >> Size;
    for(SizeType I = 0; I < Size; ++I)
    {
        T Temp = T();
        Source >> Temp;
        Value.emplace_back(Temp);
    };
    return Source;
}

template <typename T, unsigned int Size>
DeSerialize& operator >> (DeSerialize& Source, std::array<T, Size>& Value)
{
    typedef typename std::array<T, Size>::size_type SizeType;
    SizeType size;
    Source >> size;
    if (size == Size)
    {
        for(SizeType I = 0; I < Size; ++I)
        {
            T Temp = T();
            Source >> Temp;
            Value[I] = Temp;
        }
    }
    return Source;
}

Serialize& operator << (Serialize& Destination, const std::string &Value);
DeSerialize& operator >> (DeSerialize& Source, std::string &Value);

#endif // SERIALIZATION_H_INCLUDED
