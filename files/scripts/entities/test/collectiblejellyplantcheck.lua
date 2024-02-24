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

-- song cave collectible

dofile("scripts/entities/collectiblechecktemplate.lua")

v.glow = 0

function init(me)
	v.commonInit(me, "Collectibles/jellyplant", FLAG_COLLECTIBLE_JELLYPLANT, "collect_jelly_plant")
end

function update(me, dt)
	v.commonUpdate(me, dt)
	v.glow = createQuad("Naija/LightFormGlow", 13)
	quad_scale(v.glow, 10, 10)

	if v.glow ~= 0 then
		if entity_isInDarkness(me) then
			quad_alpha(v.glow, 1, 0.5)
		else

			quad_alpha(v.glow, 0, 0.5)
		end
	end
	
	quad_setPosition(v.glow, entity_getPosition(me))
	quad_delete(v.glow, 0.1)
	v.glow = 0
end
