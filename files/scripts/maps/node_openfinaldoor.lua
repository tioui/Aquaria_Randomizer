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

v.n = 0
v.done = false
v.ent = 0

function init(me)
	v.ent = node_getNearestEntity(me, "FinalDoor")
	v.n = getNaija()
end

function activate(me)
end

function update(me, dt)
	if not v.done then
		-- Ajouter des conditions ici pour permettre d'ouvrir la porte seulement si les conditions sont respectés.
		if node_isEntityIn(me, v.n) and not (entity_isState(v.ent, STATE_OPENED) or entity_isState(v.ent, STATE_OPEN)) then
			if randomizerAccessFinalBoss() then
				entity_setState(v.ent, STATE_OPEN, -1, 1)
				v.done = true
				entity_setActivation(v.ent, AT_NONE)
			else
			    entity_setActivation(v.ent, AT_CLICK, 150, 400)
			end
		end
	end
end
