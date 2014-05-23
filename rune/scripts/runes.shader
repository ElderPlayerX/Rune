//
// special effects as seen on players
//

powerups/regen
{
	deformVertexes wave 100 sin 3 0 0 0
	{
		map textures/effects/regenmap2.tga
		blendfunc GL_ONE GL_ONE
		tcGen environment
        tcmod scroll 0 1.03
	}
}


icons/charm
{
	nopicmip
	{
		map icons/charm.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/antigrav
{
	nopicmip
	{
		map icons/antigrav.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/emp
{
	nopicmip
	{
		map icons/emp.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/overkill
{
	nopicmip
	{
		map icons/overkill.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/necro
{
	nopicmip
	{
		map icons/necro.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
models/runes/resist
{
	{
		map models/runes/resist_fluid.tga
		tcMod scroll 0 2
		blendfunc GL_ONE GL_ONE
	}
	{
		map models/powerups/armor/energy_red1.tga 
                blendFunc GL_ONE GL_ONE
		tcMod scroll 7.6 1.3
		alphaGen lightingSpecular
	}
}

models/runes/haste
{
	{
		map textures/sfx/firegorre.tga
                tcMod scroll 0 3
                blendfunc GL_ONE GL_ONE
                
        }
}


models/runes/magic
{
	{
                map textures/effects/envmapblue2.jpg
                tcMod scroll 0 3
                blendfunc GL_ONE GL_ONE
                
        }
}

models/runes/reflection
{	
	{
                map textures/effects/tinfxb.jpg
                tcMod scroll 0 3
                blendfunc GL_ONE GL_ONE
                
        }   
 }
 
models/runes/regen
{	
	{
                map textures/effects/envmapgold2.jpg
                tcMod scroll 1 1
                blendfunc GL_ONE GL_ONE
                
        }
}

models/runes/strength
{
	{
		map textures/effects/envmapplas.jpg
                tcMod scroll 0 3
                blendfunc GL_ONE GL_ONE
                
        }
}
chainLightningBoltNew
{
	cull none
	{
		map gfx/misc/chainlightningnew.tga
		blendFunc GL_ONE GL_ONE
                rgbgen wave sin 1 0.5 0 7.1
                 tcmod scale  2 1
		tcMod scroll -5 0
	}
    {
		map gfx/misc/chainlightningnew.tga
		blendFunc GL_ONE GL_ONE
                rgbgen wave sin 1 0.8 0 8.1
                tcmod scale  -1.3 -1
		tcMod scroll -7.2 0
	}
}

runes/phase
{
	{
		map textures/effects/phasemap.tga
                //map textures/sfx/specular.tga
		blendfunc GL_ONE GL_ONE
		tcMod turb 0 0.15 0 0.25
		tcGen environment
	}
}
runes/weird
{
	deformVertexes wave 100 sin 3 0 0 0
	{
		map textures/effects/weirdmask.tga
		blendfunc GL_ONE GL_ONE
		tcGen environment
                tcmod rotate 30
		//tcMod turb 0 0.2 0 .2
                tcmod scroll 1 .1
	}
}
grapplingHook
{
	cull none
	{
		map textures/effects/grapplingHook.tga
		blendFunc GL_ONE GL_ONE
                rgbgen wave sin 1 0.5 0 7.1
                 tcmod scale  2 1
		tcMod scroll -5 0
	}
}
burningEffect
{
	cull none
	entityMergable		// allow all the sprites to be merged together
	{
		animmap 5 models/weaphits/rlboom/rlboom_2.tga models/weaphits/rlboom/rlboom_3.tga models/weaphits/rlboom/rlboom_4.tga models/weaphits/rlboom/rlboom_5.tga models/weaphits/rlboom/rlboom_6.tga
		rgbGen wave inversesawtooth 0 1 0 5
		blendfunc GL_ONE GL_ONE
	}
}
iceshard
{
	{
		map textures/effects/freezemap2.tga
		blendFunc GL_ONE GL_ONE
	}
}
weirdTrail
{
	cull none
	entityMergable		// allow all the sprites to be merged together
	{
		map textures/effects/weirdpuff.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen		vertex
		alphaGen	vertex
	}
}
frozen
{
	{
		map textures/effects/frozenmap.tga
		blendfunc GL_ONE GL_ONE
		tcGen environment
	}
}
deathSpot
{
	cull none
	entityMergable		// allow all the sprites to be merged together
	{
		map sprites/deathspotsprite.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen		vertex
		alphaGen	vertex
	}
}
sprites/flameball
{
	cull disable
	{
		clampmap sprites/flameball.tga
		blendfunc GL_ONE GL_ONE
                tcMod rotate 931
	}
}
sprites/gravwell
{
	cull disable
	{
		clampmap sprites/gravwell.tga
		blendfunc GL_ONE GL_ONE
		tcMod rotate 310
	}
}
rq3menuback
{
	nopicmip
	nomipmaps
	{
		map textures/sfx/RQ3Logo512.tga
		rgbgen identity
	}   
}
models/powerups/ammo/flameammo
{
       {
	        map textures/effects/envmapligh.tga
		 //tcmod scale 3 3
                tcmod rotate 350
                tcmod scroll 3 1
		//tcGen environment
		blendfunc GL_ONE GL_ZERO
                rgbGen identity
       }
       {
	        map models/powerups/ammo/lighammo.tga
		blendfunc blend
                rgbGen lightingDiffuse
       }
}
models/powerups/ammo/flameammo1
{
	{
	        map textures/effects/envmapligh.tga
                tcGen environment
		//tcmod scale 2 2
                tcmod rotate 6
                tcmod scroll .09 .09
		blendfunc GL_ONE GL_ZERO
                rgbGen lightingDiffuse
       }
}
models/powerups/ammo/flameammo2
{
	{
		map models/powerups/ammo/lighammo2.tga
		rgbGen identity
	}
	
}


// Rune Icon Shaders
icons/arsenal
{
	nopicmip
	{
		map icons/arsenal.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/athletics
{
	nopicmip
	{
		map icons/athletics.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/berserk
{
	nopicmip
	{
		map icons/berserk.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/blink
{
	nopicmip
	{
		map icons/blink.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/boxer
{
	nopicmip
	{
		map icons/boxer.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/ceasefire
{
	nopicmip
	{
		map icons/ceasefire.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/cloak
{
	nopicmip
	{
		map icons/cloak.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/death_spots
{
	nopicmip
	{
		map icons/death_spots.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/divine
{
	nopicmip
	{
		map icons/divine.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/dual
{
	nopicmip
	{
		map icons/dual.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/enviro
{
	nopicmip
	{
		map icons/enviro.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/exclusion
{
	nopicmip
	{
		map icons/exclusion.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/fire
{
	nopicmip
	{
		map icons/fire.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/flight
{
	nopicmip
	{
		map icons/flight.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/goodhealth
{
	nopicmip
	{
		map icons/goodhealth.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/gravity
{
	nopicmip
	{
		map icons/gravity.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/haste
{
	nopicmip
	{
		map icons/haste.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/hologram
{
	nopicmip
	{
		map icons/hologram.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/ice_trap
{
	nopicmip
	{
		map icons/ice_trap.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/illusion
{
	nopicmip
	{
		map icons/illusion.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/impact
{
	nopicmip
	{
		map icons/impact.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/jump
{
	nopicmip
	{
		map icons/jump.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/lightning
{
	nopicmip
	{
		map icons/lightning.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/negation
{
	nopicmip
	{
		map icons/negation.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/orb
{
	nopicmip
	{
		map icons/orb.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/packrat
{
	nopicmip
	{
		map icons/packrat.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/phase
{
	nopicmip
	{
		map icons/phase.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/phoenix
{
	nopicmip
	{
		map icons/phoenix.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/piercing
{
	nopicmip
	{
		map icons/piercing.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/plentifularmor
{
	nopicmip
	{
		map icons/plentifularmor.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/radioactivity
{
	nopicmip
	{
		map icons/radioactivity.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/recall
{
	nopicmip
	{
		map icons/recall.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/regen
{
	nopicmip
	{
		map icons/regen.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/repulsion
{
	nopicmip
	{
		map icons/repulsion.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/resistance
{
	nopicmip
	{
		map icons/resistance.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/selfpres
{
	nopicmip
	{
		map icons/selfpres.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/shield
{
	nopicmip
	{
		map icons/shield.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/sprint
{
	nopicmip
	{
		map icons/sprint.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/strength
{
	nopicmip
	{
		map icons/strength.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/switch
{
	nopicmip
	{
		map icons/switch.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/teleport
{
	nopicmip
	{
		map icons/teleport.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/transference
{
	nopicmip
	{
		map icons/transference.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/vamp
{
	nopicmip
	{
		map icons/vamp.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/vengeance
{
	nopicmip
	{
		map icons/vengeance.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/weirdness
{
	nopicmip
	{
		map icons/weirdness.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/iconw_flechette
{
	nopicmip
	{
		map icons/iconw_flechette.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/iconw_auto_shotgun
{
	nopicmip
	{
		map icons/iconw_auto_shotgun.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/iconw_homing_missile
{
	nopicmip
	{
		map icons/iconw_homing_missile.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/iconw_chaingun
{
	nopicmip
	{
		map icons/iconw_chaingun.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/iconw_mega_railgun
{
	nopicmip
	{
		map icons/iconw_mega_railgun.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/iconw_mortar
{
	nopicmip
	{
		map icons/iconw_mortar.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/iconw_triple_plasma
{
	nopicmip
	{
		map icons/iconw_triple_plasma.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/medic
{
	nopicmip
	{
		map icons/medic.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/iconw_pipebomb
{
	nopicmip
	{
		map icons/iconw_pipebomb.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/iconw_clustergrenade
{
	nopicmip
	{
		map icons/iconw_clustergrenade.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/flash
{
	nopicmip
	{
		map icons/flash.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/iconw_chainlightning
{
	nopicmip
	{
		map icons/iconw_chainlightning.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/iconw_balllightning
{
	nopicmip
	{
		map icons/iconw_balllightning.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/iconw_deathblossom
{
	nopicmip
	{
		map icons/iconw_deathblossom.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/luck
{
	nopicmip
	{
		map icons/luck.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/reflection
{
	nopicmip
	{
		map icons/reflection.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/plague
{
	nopicmip
	{
		map icons/plague.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
icons/forcefield
{
	nopicmip
	{
		map icons/forcefield.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}
models/powerups/ammo/flameammo
{
       {
	        map textures/effects/tinfx2d.tga
		tcGen environment
		blendfunc GL_ONE GL_ZERO
                rgbGen identity
       }
       {
	        map models/powerups/ammo/flameammo.tga
		blendfunc blend
                rgbGen lightingDiffuse
       }
}
models/powerups/ammo/flameammo1
{
       {
	        map textures/effects/envmapmach.tga
		tcGen environment
		blendfunc GL_ONE GL_ZERO
                rgbGen lightingDiffuse
       }
}
models/powerups/ammo/flameammo2
{
	{
		map models/powerups/ammo/flameammo2.tga
		rgbGen identity
	}
	
}
reflectionShader
{
	deformVertexes wave 100 sin 3 0 0 0
	{
		map textures/effects/reflectionmap.tga
		blendfunc GL_ONE GL_ONE
		tcGen environment
                tcmod rotate 30
		//tcMod turb 0 0.2 0 .2
                tcmod scroll 1 .1
	}
}
reflectionShaderWeapon
{
	deformVertexes wave 100 sin 0.5 0 0 0
	{
		map textures/effects/reflectionmap.tga
		blendfunc GL_ONE GL_ONE
		tcGen environment
                tcmod rotate 30
		//tcMod turb 0 0.2 0 .2
                tcmod scroll 1 .1
	}
}
berserkShader
{
	deformVertexes wave 100 sin 3 0 0 0
	{
		map textures/effects/blueflagmap.tga
		blendfunc GL_ONE GL_ONE
		tcGen environment
		tcMod turb 0 0.2 0 1
	}
}
berserkShaderWeapon
{
	deformVertexes wave 100 sin 0.5 0 0 0
	{
		map textures/effects/blueflagmap.tga
		blendfunc GL_ONE GL_ONE
		tcGen environment
		tcMod turb 0 0.2 0 1
	}
}

plaguePuff
{
	cull none
	entityMergable		// allow all the sprites to be merged together
	{
		map gfx/misc/plaguepuff.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen		vertex
		alphaGen	vertex
	}
}
medal_wallshot
{
	nopicmip
	{
		clampmap menu/medals/medal_wallshot.tga
		blendFunc blend
	}
}
//medal_impact
//{
//	nopicmip
//	{
//		clampmap icons/impact.tga
//		blendFunc blend
//	}
//}
chainLightningBolt
{
	cull none
	{
		map gfx/misc/chainlightning.tga
		blendFunc GL_ONE GL_ONE
                rgbgen wave sin 1 0.5 0 7.1
                 tcmod scale  2 1
		tcMod scroll -5 0
	}
    {
		map gfx/misc/chainlightning.tga
		blendFunc GL_ONE GL_ONE
                rgbgen wave sin 1 0.8 0 8.1
                tcmod scale  -1.3 -1
		tcMod scroll -7.2 0
	}
}
icons/icon_backpack
{
	nopicmip
	{
		map icons/icon_backpack.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}

models/backpack
{      
 
        {
                map textures/sfx/specular.tga            
                blendFunc GL_ONE GL_ZERO
                tcGen environment
	}  
        {
		map models/backpack.tga
        blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen lightingDiffuse
	}
                
}
cloakingeffect
{
	{
		map textures/effects/tinfx.tga
		blendfunc blend
		tcGen environment
		tcMod turb 0 1 1 0.2
		rgbGen entity
		alphaGen entity
	}
}
flechettetrail
{
	sort nearest
	cull none
	{
		clampmap models/weaphits/flechettetrail.tga 
		blendFunc Add
		rgbGen vertex
                tcMod rotate -30
	}

}
forceField
{
	cull none
	entityMergable		// allow all the sprites to be merged together
	{
		map sprites/forcefield.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen		vertex
		alphaGen	vertex
		//tcMod turb 0 0.2 0 .2
	}
}
sprites/balllightning
{
	cull disable
	{
		clampmap sprites/balllightning.tga
		blendfunc GL_ONE GL_ONE
                tcMod rotate 354
	}
}