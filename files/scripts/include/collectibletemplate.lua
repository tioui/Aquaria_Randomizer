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

-- COLLECTIBLE ITEM

v.myFlag = 0
v.back = false

v.isCostume = false

function v.commonInit(me, gfx, flag, cst)
	v.myFlag = flag
	setupEntity(me, gfx)
	debugLog("in common init")
	if isFlag(flag, 1) then
		debugLog("setting state collected")
		entity_setState(me, STATE_COLLECTED)
		entity_alpha(me, 0, 0)
	end	
	
	local nd = entity_getNearestNode(me, "layerback")
	if nd ~= 0 and node_isEntityIn(nd, me) then
		entity_setEntityLayer(me, -1)
		v.back = true
	end
	
	v.isCostume = cst or false
end

function v.commonUpdate(me, dt)
	if entity_isState(me, STATE_IDLE) then
		if v.back then
			local e = getFirstEntity()
			while e ~= 0 do
				if eisv(e, EV_TYPEID, EVT_ROCK) then
					if entity_isEntityInRange(me, e, 64) then
						return
					end
				end
				e = getNextEntity()
			end
		end
	end
end

v.incut = false

function v.commonEnterState(me, state)
	if v.incut then return end
	
	if entity_isState(me, STATE_COLLECTED) then	
		debugLog("COLLECTED, fading OUT alpha")
		entity_alpha(me, 0, 1)
	elseif entity_isState(me, STATE_COLLECTEDINHOUSE) then
		debugLog("COLLECTEDINHOUSE.. fading IN")
		entity_alpha(me, 1, 0.1)
	end
end

