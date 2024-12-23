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

-- regular areas
local TURTLE_REGULAR	= 0

v.seat = 0
v.seat2 = 0
v.tame = 0
v.n = 0
v.li = 0
v.lights = false
v.leave = 0
v.avatarAttached = false
v.liAttached = false
v.myCheckFlag = 0
v.myFlag = 0
v.check = 0
v.turtleType = TURTLE_REGULAR

v.destination = 0

v.light1 = 0
v.light2 = 0

v.seen = false

v.sbank = 0

function init(me)
	v.n = getNaija()
	
	setupEntity(me, "")
	entity_initSkeletal(me, "TransTurtle")
	
	entity_setEntityType(me, ET_NEUTRAL)
	entity_setActivation(me, AT_CLICK, 128, 512)
	
	v.seat = entity_getBoneByName(me, "Seat")
	v.seat2 = entity_getBoneByName(me, "Seat2")
	v.tame = entity_getBoneByName(me, "Tame")
	entity_setCullRadius(me, 1024)
	bone_alpha(v.seat, 0)
	bone_alpha(v.seat2, 0)
	bone_alpha(v.tame, 0)
	debugLog("Loading Turtle")
	
	if isMapName("VEIL01") then
		v.myCheckFlag = FLAG_TRANSTURTLE_VEIL01_CHECK
		v.myFlag = FLAG_TRANSTURTLE_VEIL01
		v.sbank = 1014
		v.check = "transturtle_veil01"
	elseif isMapName("VEIL02") then
		v.myCheckFlag = FLAG_TRANSTURTLE_VEIL02_CHECK
		v.myFlag = FLAG_TRANSTURTLE_VEIL02
		v.sbank = 1014
		v.check = "transturtle_veil02"
	elseif isMapName("OPENWATER03") then
		v.myCheckFlag = FLAG_TRANSTURTLE_OPENWATER03_CHECK
		v.myFlag = FLAG_TRANSTURTLE_OPENWATER03
		v.sbank = 1009
		v.check = "transturtle_openwater03"
	elseif isMapName("FOREST04") then
		v.myCheckFlag = FLAG_TRANSTURTLE_FOREST04_CHECK
		v.myFlag = FLAG_TRANSTURTLE_FOREST04
		v.sbank = 1010
		v.check = "transturtle_forest04"
	elseif isMapName("MAINAREA") then
		v.myCheckFlag = FLAG_TRANSTURTLE_MAINAREA_CHECK
		v.myFlag = FLAG_TRANSTURTLE_MAINAREA
		v.sbank = 1008
		v.check = "transturtle_mainarea"
	elseif isMapName("ABYSS03") then
		v.myCheckFlag = FLAG_TRANSTURTLE_ABYSS03_CHECK
		v.myFlag = FLAG_TRANSTURTLE_ABYSS03
		v.turtleType = TURTLE_REGULAR
		v.sbank = 1015
		v.check = "transturtle_abyss03"
	elseif isMapName("FINALBOSS") then
		v.myCheckFlag = FLAG_TRANSTURTLE_FINALBOSS_CHECK
		v.myFlag = FLAG_TRANSTURTLE_FINALBOSS
		v.turtleType = TURTLE_REGULAR
		v.sbank = 1021
		v.check = "transturtle_finalboss"
	elseif isMapName("FOREST05") then
		v.myCheckFlag = FLAG_TRANSTURTLE_FOREST05_CHECK
		v.myFlag = FLAG_TRANSTURTLE_FOREST05
		v.turtleType = TURTLE_REGULAR
		v.sbank = 1010
		v.check = "transturtle_forest05"
	elseif isMapName("SEAHORSE") then
		v.myCheckFlag = FLAG_TRANSTURTLE_SEAHORSE_CHECK
		v.myFlag = FLAG_TRANSTURTLE_SEAHORSE
		v.turtleType = TURTLE_REGULAR
		v.sbank = 1028
		v.check = "transturtle_seahorse"
	end
	
	v.light1 = entity_getBoneByName(me, "Light1")
	v.light2 = entity_getBoneByName(me, "Light2")
	
	bone_setBlendType(v.light1, BLEND_ADD)
	bone_setBlendType(v.light2, BLEND_ADD)
	
	loadSound("TransTurtle-Light")
	loadSound("transturtle-takeoff")
	
	
end


local function lights(me, on, t)
	local a = 1
	if not on then
		a = 0
		debugLog("Lights off!")
	else
		debugLog("Lights on!")
	end
	v.lights = on
	bone_alpha(v.light1, a, t)
	bone_alpha(v.light2, a, t)
end

function postInit(me)
	v.leave = entity_getNearestNode(me, "TRANSTURTLELEAVE")
	
	if v.turtleType == TURTLE_REGULAR then
		debugLog("Regular turtle")
		if isFlag(v.myCheckFlag, 0) then
			lights(me, false, 0)
		else
			lights(me, true, 0)
		end
		
		if v.sbank ~= 0 then
			if entity_isEntityInRange(me, getNaija(), 600) then
				centerText(getStringBank(v.sbank))
			end
		end
	else
		debugLog("Special turtle")
		lights(me, true, 0)
	end
	
	
	-- if naija starts on a turtle, ignore the seen/hint
	if entity_isEntityInRange(me, v.n, 350) then
		v.seen = true
	end
end

local function isOtherFlag(flag)
	return (v.myFlag ~= flag and isFlag(flag, 1))
end

local function anyOtherFlag()
--	if v.turtleType == TURTLE_REGULAR then
--		debugLog("turtle is regular")
		if isOtherFlag(FLAG_TRANSTURTLE_VEIL01) then
			return true
		elseif isOtherFlag(FLAG_TRANSTURTLE_VEIL02) then
			return true
		elseif isOtherFlag(FLAG_TRANSTURTLE_OPENWATER03) then
			return true
		elseif isOtherFlag(FLAG_TRANSTURTLE_FOREST04) then
			return true
		elseif isOtherFlag(FLAG_TRANSTURTLE_MAINAREA) then
			return true
		elseif isOtherFlag(FLAG_TRANSTURTLE_FINALBOSS) then
			return true
		elseif isOtherFlag(FLAG_TRANSTURTLE_ABYSS03) then
			return true
		elseif isOtherFlag(FLAG_TRANSTURTLE_FOREST05) then
			return true
		elseif isOtherFlag(FLAG_TRANSTURTLE_SEAHORSE) then
			return true
		end
--	end
--	if v.turtleType == TURTLE_SECRET1 then
--		debugLog("turtle is secret")
--		return true
--	end
--	debugLog("turtle is nothing")
	return false
end

function update(me, dt)

	if v.turtleType == TURTLE_REGULAR and isFlag(v.myCheckFlag, 1) and not v.lights then
		lights(me, true, 1.5)
	end
--	if anyOtherFlag() then
--		entity_setActivationType(me, AT_CLICK)
--	else
--		entity_setActivationType(me, AT_NONE)
--	end
	
	if v.avatarAttached then
		--entity_flipToSame(v.n, me)
		local x, y = bone_getWorldPosition(v.seat)
		
		entity_setRidingData(me, x, y, 0, entity_isfh(me))
	end
	
	if v.liAttached then
		local x, y = bone_getWorldPosition(v.seat2)
		entity_setPosition(v.li, x, y)
		entity_rotate(v.li, entity_getRotation(me))
		if entity_isfh(me) and not entity_isfh(v.li) then
			entity_fh(v.li)
		elseif not entity_isfh(me) and entity_isfh(v.li) then
			entity_fh(v.li)
		end
	end
	
	if entity_isEntityInRange(me, v.n, 300) then
		if not v.seen then
			emote(EMOTE_NAIJAWOW)
--			if not anyOtherFlag() then
--				setControlHint(getStringBank(226), 0, 0, 0, 5, "transturtle/headicon")
--			else
--				setControlHint(getStringBank(225), 0, 0, 0, 5, "transturtle/headicon")
--			end
			v.seen = true
		end
	end
	
		if isNested() then return end
		if entity_isEntityInRange(me, v.n, 300) and not isFlag(v.myCheckFlag, 1) and entity_isUnderWater(v.n) then
			entity_idle(v.n)
			entity_setInvincible(v.n, true)
			entity_flipToEntity(v.n, me)
			cam_toEntity(me)
			watch(1.5)
			playSfx("TransTurtle-Light")
			--lights(me, true, 1.5)
			--watch(2)
			cam_toEntity(v.n)
			watch(1)
			setFlag(v.myCheckFlag, 1)
			randomizerCheck(v.check)
			pickupGem("Turtle")
		end
end

function activate(me)
	if entity_getRiding(getNaija())~=0 then
		return
	end
	
--	if anyOtherFlag() then
		entity_setActivation(me, AT_NONE)
		
		if not isFlag(v.myCheckFlag, 1) then
			setFlag(v.myCheckFlag, 1)
			randomizerCheck(v.check)
			pickupGem("Turtle")
		end

		if isFlag(FLAG_FIRSTTRANSTURTLE, 0) then
			local x, y = bone_getWorldPosition(v.tame)
			entity_swimToPosition(v.n, x, y)
			entity_watchForPath(v.n)
			entity_flipToEntity(v.n, me)
			entity_animate(v.n, "tameTurtle", 0, LAYER_UPPERBODY)
			entity_animate(me, "tame")
			while entity_isAnimating(me) do
				watch(FRAME_TIME)
			end
			entity_idle(v.n)
			entity_animate(me, "idle")
			watch(0.5)
			-- don't forget this later: 
			setFlag(FLAG_FIRSTTRANSTURTLE, 1)
		end
		v.li = 0
		if hasLi() then
			v.li = getLi()
			if entity_isEntityInRange(v.n, v.li, 512) then
			else
				fade2(1, 0.2, 1, 1, 1)
				watch(0.2)
				entity_setPosition(v.li, entity_x(v.n), entity_y(v.n))
				fade2(0, 0.5)
				watch(0.5)
			end
		end
		local x, y = bone_getWorldPosition(v.seat)

		v.destination = askTransportation()

		if v.destination > 0 then
			entity_swimToPosition(v.n, x, y)
			entity_watchForPath(v.n)
			entity_animate(v.n, "rideTurtle", -1)
			v.avatarAttached = true
			if entity_isfh(me) and not entity_isfh(v.n) then
				entity_fh(v.n)
			elseif not entity_isfh(me) and entity_isfh(v.n) then
				entity_fh(v.n)
			end
			
			if v.li ~= 0 then
				debugLog("here!")
				entity_setState(v.li, STATE_PUPPET, -1, 1)
				local x2, y2 = bone_getWorldPosition(v.seat2)
				entity_swimToPosition(v.li, x2, y2)
				entity_watchForPath(v.li)
				entity_animate(v.li, "rideTurtle", -1)
				v.liAttached = true
				entity_setRiding(v.li, me)
			end
			
			
			entity_setRiding(v.n, me)
			overrideZoom(0.75, 1.5)
			if isMapName("VEIL01") then
				entity_rotate(me, -80, 2, 0, 0, 1)
			end
			entity_animate(me, "swimPrep")
			while entity_isAnimating(me) do
				watch(FRAME_TIME)
			end
			
	
			entity_moveToNode(me, v.leave, SPEED_FAST)
			entity_animate(me, "swim", -1)
			
			playSfx("transturtle-takeoff")
			watch(1)
			fade(1, 1)
			watch(1)
			
			-- HACK: Keep the mouse cursor from reappearing for an instant
			-- when under keyboard or joystick control.
			disableInput()

			if v.destination == FLAG_TRANSTURTLE_ABYSS03 then
				warpNaijaToSceneNode("ABYSS03", "TRANSTURTLE")
			elseif v.destination == FLAG_TRANSTURTLE_FINALBOSS then
				warpNaijaToSceneNode("FINALBOSS", "TRANSTURTLE")
			elseif v.destination == FLAG_TRANSTURTLE_OPENWATER03 then
				warpNaijaToSceneNode("OPENWATER03", "TRANSTURTLE")
			elseif v.destination == FLAG_TRANSTURTLE_MAINAREA then
				warpNaijaToSceneNode("MAINAREA", "TRANSTURTLE")
			elseif v.destination == FLAG_TRANSTURTLE_FOREST05 then
				warpNaijaToSceneNode("FOREST05", "TRANSTURTLE")
			elseif v.destination == FLAG_TRANSTURTLE_FOREST04 then
				warpNaijaToSceneNode("FOREST04", "TRANSTURTLE")
			elseif v.destination == FLAG_TRANSTURTLE_SEAHORSE then
				warpNaijaToSceneNode("SEAHORSE", "TRANSTURTLE")
			elseif v.destination == FLAG_TRANSTURTLE_VEIL02 then
				warpNaijaToSceneNode("VEIL02", "TRANSTURTLE")
			elseif v.destination == FLAG_TRANSTURTLE_VEIL01 then
				warpNaijaToSceneNode("VEIL01", "TRANSTURTLE")
			elseif v.destination == FLAG_TRANSTURTLE_NAIJAHOME then
				warpNaijaToSceneNode("VEDHACAVE", "TRANSTURTLE")
			else
				warpNaijaToSceneNode("NAIJACAVE", "TRANSTURTLE")
			end
		else
			entity_setActivation(me, AT_CLICK, 128, 512)
		end
		
--	else
--		debugLog("TransTurtle: no other flag set")
--		playSfx("denied")
--		setControlHint(getStringBank(225), 0, 0, 0, 4, "transturtle/headicon")
--	end
	--end
end

function enterState(me)
	if entity_isState(me, STATE_IDLE) then
		entity_animate(me, "idle", -1, 0, -1)
	end
end

function exitState(me)
end
