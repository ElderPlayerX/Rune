#ifndef RUNE_H
#define RUNE_H

#define		RUNE_MAX_DESCRIPTION_LINES			3
#define		RUNE_MAX_RUNES						128


#define		RUNE_TOTAL							RUNE_DISARMAMENT

typedef enum {
	RUNE_NONE,									//0
	RUNE_STRENGTH,								//1
	RUNE_BERSERK,								//2
	RUNE_RESISTANCE,							//3
	RUNE_PIERCING,								//4
	RUNE_HASTE,									//5
	RUNE_GOOD_HEALTH,							//6
	RUNE_PLENTIFUL_ARMOR,						//7
	RUNE_REGENERATION,							//8
	RUNE_ENVIRO,								//9
	RUNE_VENGEANCE,								//10
	RUNE_SELF_PRESERVATION,						//11
	RUNE_ACTION_MOVIE,							//12
	RUNE_FLIGHT,								//13
	RUNE_SHIELD,								//14
	RUNE_SPRINT,								//15
	RUNE_OVERKILL,								//16
	RUNE_TELEPORT,								//17
	RUNE_SWITCH,								//18
	RUNE_NEGATION,								//19
	RUNE_REFLECTION,							//20
	RUNE_PHASE,									//21
	RUNE_IMPACT,								//22
	RUNE_ATHLETICS,								//23
	RUNE_FLASH,									//24
	RUNE_DISARMAMENT,							//25

	RUNE_EXCLUSION


} runeTypes;

/*
	RUNE_EMP,
RUNE_EXCLUSION
RUNE_EMP

RUNE_PLAGUE
RUNE_FIRE

RUNE_RECALL
RUNE_DUAL_RECALL
RUNE_BLINK

RUNE_ICE_TRAPS
RUNE_DEATH_SPOTS
RUNE_GRAVITY
RUNE_RADIOACTIVITY
RUNE_HOLOGRAM

	ANTIGRAVITY
	DEATH'S HELPER
	#define		RUNE_CLOAKING			13
	#define		RUNE_LIGHTNING			14
	#define		RUNE_BOXER				23
	#define		RUNE_QUAD_DAMAGE		26
	#define		RUNE_PHOENIX			28
	#define		RUNE_VAMPIRE			29
	#define		RUNE_DIVINE_WIND		34
	#define		RUNE_JUMPING			35
	#define		RUNE_DEATH_ORB			36
	#define		RUNE_REPULSION			37
	#define		RUNE_WEIRDNESS			40
	#define		RUNE_PACK_RAT			42
	#define		RUNE_MEDIC				47
	#define		RUNE_LUCK				49

*/

// we get 8 shells to work with
typedef enum {
	SFX_SHELL_BERSERK,
	SFX_SHELL_SHIELD,
	SFX_SHELL_REFLECTION,
	SFX_SHELL_FROZEN,
	SFX_SHELL_QUAD,
	SFX_SOUND_QUAD,
	SFX_SHELL_7,
	SFX_SHELL_8
} colorShells;

typedef enum {
	DYN_SOUND_MEGAHEALTH,
	DYN_SOUND_ARMOR,
	DYN_SOUND_IMPACT
} dynamicSounds;



// how far over health and armor we can go with certain items
#define		RUNE_HEALTH_OVER_MAX				100
#define		RUNE_ARMOR_OVER_MAX					100

// applied to both walking speed (as an increase) and firing delay (as a decrease)
#define		RUNE_HASTE_SPEED_INCREASE			1.3	

// max health for good health
#define		RUNE_GOOD_HEALTH_MAX_HEALTH			600

// max armor for armor
#define		RUNE_PLENTINFUL_ARMOR_MAX			700
// percentage of damage absorbed by plentiful armor
#define		RUNE_PLENTIFUL_ARMOR_PROTECTION		0.8f

#define		RUNE_REGEN_MAX_HEALTH				100
#define		RUNE_REGEN_MAX_ARMOR				200
#define		RUNE_REGEN_ARMOR_INCREASE			5
#define		RUNE_REGEN_HEALTH_INCREASE			5

#define		RUNE_SHIELD_DURATION				3000
#define		RUNE_SHIELD_RECHARGE				4500

#define		RUNE_SPRINT_DURATION				3000
#define		RUNE_SPRINT_RECHARGE				4500
#define		RUNE_SPRINT_SPEED_INCREASE			3

#define		RUNE_OVERKILL_INCREASE				2

// % chance of telefragging someone you hit directly with teleport shuffle
#define		RUNE_TELEPORT_TELEFRAG_CHANCE		15

// how much health using the Negation rune costs
#define		RUNE_NEGATION_COST					50		

// how much damage reflection sends back for rockets, etc
#define		RUNE_REFLECTION_AMOUNT				.4			
// how much for lightning
#define		RUNE_REFLECTION_LIGHTNING_AMOUNT	.7			

#define		RUNE_PHASE_RECHARGE					1000
// percent chance that missles go right through
#define		RUNE_PHASE_AVOID_CHANCE				50			

// impact gives a small overall increase in damage
#define		RUNE_IMPACT_DAMAGE_BONUS			1.1			
// how much (multiplied) your weapon's kick is increased by
#define		RUNE_IMPACT_KICK_BONUS				2			
#define		RUNE_IMPACT_RECHARGE				250
#define		RUNE_IMPACT_BODYCHECK_DAMAGE		50
#define		RUNE_IMPACT_BODYCHECK_INSANE_KICK	600
#define		RUNE_IMPACT_BODYCHECK_KICK			250

// percent of damage let through (ie:  10% of damage is blocked)
#define		RUNE_ATHLETICS_DAMAGE_PROTECTION	0.9
// Z velocity add for super jump
#define		RUNE_ATHLETICS_JUMP_HEIGHT			900
// time between jumps
#define		RUNE_ATHLETICS_RECHARGE				2000		
#define		RUNE_ATHLETICS_SPEED_INCREASE		1.1
#define		RUNE_ATHLETICS_MAX_HEALTH			150

// radius of flash effect
#define		RUNE_FLASH_RADIUS					700
#define		RUNE_FLASH_DURATION					5000
#define		RUNE_FLASH_FADEIN					2000
#define		RUNE_FLASH_RECHARGE					11000

// radius
#define		RUNE_DISARMAMENT_RADIUS				700			
#define		RUNE_DISARMAMENT_DURATION			5000		// how long the weapons are stunned, in msecs
#define		RUNE_DISARMAMENT_RECHARGE			11000		// milliseconds

// radius
#define		RUNE_EMP_RADIUS						900

// radius
#define		RUNE_EXCLUSION_RECHARGE				10000
#define		RUNE_EXCLUSION_RADIUS				700	












#define		RUNE_WEIRDNESS_DURATION				15000		// how long weirdness effects last
#define		RUNE_WEIRDNESS_NUMBER				6			// how many weird bubbles to spawn at the death point



#define		RUNE_ITEM_PICKUP_ICON				"icons/regen"
#define		RUNE_ITEM_PICKUP_NAME				"Rune"
#define		RUNE_ITEM_PICKUP_SOUND				"sound/misc/am_pkup.wav"
#define		RUNE_ITEM_PICKUP_SOUND2				"sound/items/regen.wav"
#define		RUNE_ITEM_MODEL1					"models/runes/magic.md3"
#define		RUNE_ITEM_MODEL_RING1				""
#define		RUNE_ITEM_MODEL2					"models/runes/reflection.md3"
#define		RUNE_ITEM_MODEL_RING2				""
#define		RUNE_ITEM_MODEL3					"models/runes/regen.md3"
#define		RUNE_ITEM_MODEL_RING3				""
#define		RUNE_ITEM_MODEL4					"models/runes/resist.md3"
#define		RUNE_ITEM_MODEL_RING4				""
#define		RUNE_ITEM_MODEL5					"models/runes/strength.md3"
#define		RUNE_ITEM_MODEL_RING5				""
#define		RUNE_ITEM_MODEL6					"models/runes/haste.md3"
#define		RUNE_ITEM_MODEL_RING6				""
#endif //RUNE_H