-- Copyright (C) 2007, 2010 - Bit-Blot
--
-- This file is part of Aquaria.
--
-- Aquaria is free software; you can redistribute it and/or
-- modify it under the terms of the GNU General Public License
-- as published by the Free Software Foundation; either version 2
-- of the License, or (at your option) any later version.
--
-- This program is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
--
-- See the GNU General Public License for more details.
--
-- You should have received a copy of the GNU General Public License
-- along with this program; if not, write to the Free Software
-- Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

if not v then v = {} end
if not AQUARIA_VERSION then dofile("scripts/entities/entityinclude.lua") end

function init(me)
end

function update(me, dt)	
---isFlag(FLAG_ENERGYGODENCOUNTER, 2) and 
	if isFlag(FLAG_NAIJA_ENERGYFORMSHOT,0) and hasSong(SONG_ENERGYFORM) then
		if node_isEntityIn(me, getNaija()) then
			voice("naija_energyformshot")
			if isPlat(PLAT_MAC) then
				setControlHint(getStringBank(90), 0, 1)
			else
				setControlHint(getStringBank(70), 0, 1)
			end
			setFlag(FLAG_NAIJA_ENERGYFORMSHOT, 1)
		end
	end
end
