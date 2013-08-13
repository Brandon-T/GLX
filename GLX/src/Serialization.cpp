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

#include "Serialization.hpp"

Serialize& operator << (Serialize& Destination, const std::string &Value)
{
    Destination << Value.size();
    for (auto it = Value.begin(); it != Value.end(); ++it)
    {
        Destination << *it;
    }
    return Destination;
}

DeSerialize& operator >> (DeSerialize& Source, std::string &Value)
{
    typedef typename std::string::size_type SizeType;
    SizeType Size;
    Source >> Size;
    Value.reserve(Size);
    for (SizeType I = 0; I < Size; ++I)
    {
        char Temp;
        Source >> Temp;
        Value += Temp;
    }
    return Source;
}
