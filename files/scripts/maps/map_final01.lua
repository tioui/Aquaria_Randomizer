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

dofile("scripts/maps/finalcommon.lua")

function init()
	v.initFinalSpirits()
	
	if getFlag(FLAG_SUNKENCITY_PUZZLE) >= SUNKENCITY_BOSSDONE and isFlag(FLAG_FINAL, FINAL_START) then
		setFlag(FLAG_LI, 200)
	
		local node = getNode("LIHEART")
		local ent = getLi()
		if ent == 0 then
			ent = createEntity("Li", "")
		end
		entity_setPosition(ent, node_x(node), node_y(node))
		entity_setState(ent, STATE_TRAPPEDINCREATOR, -1, 1)
		
		local node = getNode("CCHEART")
		local ent = createEntity("CC_Final", "", node_x(node), node_y(node))
	end
end
