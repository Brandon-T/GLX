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

#ifndef DEBUGGER_HPP_INCLUDED
#define DEBUGGER_HPP_INCLUDED

#include <cstdint>
#include <algorithm>
#include "Graphics.hpp"
#include "Render.hpp"
#include "Structures.hpp"

class DebugGraphics
{
    private:
        Render* Renderer;
        struct Box{int X1, Y1, X2, Y2;};

        int Mode = 0;
        Box Filters[4];
        std::uint32_t HudID = 0;

    public:
        void SetMode(std::uint32_t Mode);
        void SetRenderer(Render* Renderer);
        void SetArea(int X1, int Y1, int X2, int Y2);
        void SetTexture(std::uint32_t ID);
        void Draw();
};

#endif // DEBUGGER_HPP_INCLUDED
