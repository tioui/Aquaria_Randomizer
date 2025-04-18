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

v.door = 0
function init(me)
	node_setCursorActivation(me, true)
	v.door = node_getNearestEntity(me, "EnergyDoor")
	if v.door ~= 0 and isFlag(FLAG_MITHALAS_THRONEROOM,1) then
		entity_setState(v.door, STATE_OPENED)
	end
end

function update(me, dt)
	if entity_getState(v.door) ~= STATE_OPENED and v.door ~= 0 and isFlag(FLAG_MITHALAS_THRONEROOM,1) then
		entity_setState(v.door, STATE_OPENED)

	end
end

function activate(me)
	local n = getNaija()
	
	entity_idle(n)
	
	entity_swimToNode(n, me)
	entity_watchForPath(n)
	
	
	entity_animate(n, "sitThrone", -1)

	overrideZoom(0.5, 2)
	
	watch(2)

	if isFlag(FLAG_SEAL_PRINCE,1) then
		randomizerCheck("sitting_on_throne")
	end
	
--	if isFlag(FLAG_MITHALAS_THRONEROOM,0) then
--		--if isFlag(FLAG_SEAL_KING,1) and isFlag(FLAG_SEAL_QUEEN,1) and isFlag(FLAG_SEAL_PRINCE,1) then
--		if isFlag(FLAG_SEAL_PRINCE,1) then
--			debugLog("OPENED DOOR")
--			
--			entity_setState(v.door, STATE_OPEN)
--			setFlag(FLAG_MITHALAS_THRONEROOM, 1)
--			cam_toEntity(v.door)
--			watch(2)
--			cam_toEntity(n)
--		end
--	end
	
	while (not isLeftMouse()) and (not isRightMouse()) do
		watch(FRAME_TIME)
	end
	
	entity_idle(n)
	entity_addVel(n, 0, -200)
	overrideZoom(1, 1)
	watch(1)
	overrideZoom(0)
end
