/**
 * 
 * ACNHItemMsbt.cpp
 * 
 * Copyright (c) 2021-2021, Slattz.
 * 
 * This file is part of LibACNH (https://github.com/Slattz/LibACNH).
 * 
 * LibACNH is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * LibACNH is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with LibACNH.  If not, see <https://www.gnu.org/licenses/>
 */

#include "ACNHItemMsbt.hpp"
#include <cstring>

ACNHItemMsbt::ACNHItemMsbt(const char* filePath) : MSBT(filePath) {
    if (IsValid())
        FixItemNames();
}

ACNHItemMsbt::ACNHItemMsbt(u8* inBuffer, u64 bufSize, bool manageMem) : MSBT(inBuffer, bufSize, manageMem) {
    if (IsValid())
        FixItemNames();
}

ACNHItemMsbt::~ACNHItemMsbt() {
    if (autoManageMem) {
        delete[] this->data;
        autoManageMem = false;
    }
}

//Hacky, assumes MSBT param sizes
void ACNHItemMsbt::FixItemNames() {
    for (size_t i = 0; i < Texts.size(); i++) {
        MSBTString& text = Texts[i];

        if (text.encoding == Encoding_UTF16) {
            u32 offset = 0;
            if (text.stringBytes[0] == 0xE) offset = 0xC; //All Items
            if (text.stringBytes[0xC] == 0xE) offset += 0x8; //Special "π pie" handling
            text.stringBytes += offset;
            text.stringSize -= offset;
        }
    }
}