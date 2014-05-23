#ifndef RUNE_FUNCS
#define	RUNE_FUNCS

struct s_runeInfo
{
	int			RuneID;							// the #define identifier of the rune
	char		*runeName;						// The name		ie "Flight Rune"
	char		*shortName;						// Abbreviated lower case name of the rune ie "flight"
	qboolean	dropOnDeath;					// can this rune be dropped onto the level when you die?  (if rune dropping is enabled that is)
												// Divine Wind, for example, is not dropped when you die, otherwise you'd have people constantly setting it off
	qboolean	deleteOnDeath;					// When you die, does this rune delete itself from your information?  
												// vamp and phoenix, for example, need to stay attached even after the player dies							
	qboolean	spawnable;						// can this rune be spawned? (used for rune banning code)
	char		*runeIcon;						// name of the shader for the Rune in the runes.shader file
	char		*runeDescription[RUNE_MAX_DESCRIPTION_LINES];

	qboolean	teamRune;						// is this rune for use in teamplay games only?
	qboolean	botRune;						// is this rune useable by bots?
};



// NOTE:  The number of slot that each of these goes into MUST MATCH EXACTLY the ID number of the rune
struct s_runeInfo runeInfo[] = 
{
	{
		RUNE_NONE,
		"No Rune",
		"none",
		qfalse,
		qfalse,
		qfalse,
		"icons/norune.tga",
		{
			"",
			"",
			""
		},
		qfalse,
		qfalse,
	},
	{
		RUNE_STRENGTH,
		"Strength Rune",
		"strength",
		qtrue,
		qtrue,
		qtrue,
		"icons/strength",
		{
			"Your attacks do double damage",
			"",
			""
		},
		qfalse,
		qtrue,
	},
	{
		RUNE_BERSERK,
		"Berserk Rune",
		"berserk",
		qtrue,					
		qtrue,
		qtrue,
		"icons/berserk",
		{
			"Deal 6x damage",
			"Take 3x damage",
			""
		},
		qfalse,
		qtrue,
	},
	{
		RUNE_RESISTANCE,
		"Rune of Resistance",
		"resistance",
		qtrue,			//dropOnDeath
		qtrue,			//deleteOnDeath
		qtrue,			//spawnable
		"icons/resistance",
		{
			"You take half damage",
			"",
			""
		},
		qfalse,
		qtrue,
	},
	{
		RUNE_PIERCING,
		"Rune of Armor Piercing",
		"piercing",
		qtrue,			//dropOnDeath
		qtrue,			//deleteOnDeath
		qtrue,			//spawnable
		"icons/piercing",
		{
			"Your attacks ignore target's armor",
			"",
			""
		},
		qfalse,
		qtrue,
	},
	{
		RUNE_HASTE,
		"Haste Rune",
		"haste",
		qtrue,			//dropOnDeath
		qtrue,			//deleteOnDeath
		qtrue,			//spawnable
		"icons/haste",
		{
			"Weapons shoot faster",
			"You run faster",
			""
		},
		qfalse,
		qtrue,
	},
	{
		RUNE_GOOD_HEALTH,
		"Rune of Good Health",
		"health",
		qtrue,			//dropOnDeath
		qtrue,			//deleteOnDeath
		qtrue,			//spawnable
		"icons/goodhealth",
		{
			"Maximum health set to 600",
			"",
			""
		},
		qfalse,
		qtrue,
	},
	{
		RUNE_PLENTIFUL_ARMOR,
		"Rune of Plentiful Armor",
		"armor",
		qtrue,			//dropOnDeath
		qtrue,			//deleteOnDeath
		qtrue,			//spawnable
		"icons/plentifularmor",
		{
			"Max armor is now 700",
			"",
			""
		},
		qfalse,
		qtrue,
	},
	{
		RUNE_REGENERATION,
		"Regeneration Rune",
		"regen",
		qtrue,			//dropOnDeath
		qtrue,			//deleteOnDeath
		qtrue,			//spawnable
		"icons/regen",
		{
			"Regenerates health and",
			"armor if you have it",
			""
		},
		qfalse,
		qtrue,
	},
	{
		RUNE_ENVIRO,
		"Environmental Protection",
		"enviro",
		qtrue,					//dropOnDeath
		qtrue,					//deleteOnDeath
		qtrue,					//spawnable
		"icons/enviro",
		{
			"Protection from some runes",
			"Slime and lava give health",
			""
		},
		qfalse,
		qtrue,
	},
	{
		RUNE_VENGEANCE,
		"Vengeance Rune",
		"vengeance",
		qtrue,			//dropOnDeath
		qtrue,			//deleteOnDeath
		qtrue,			//spawnable
		"icons/vengeance",
		{
			"Damage done to you",
			"also done to attacker",
			""
		},
		qfalse,
		qtrue,
	},
	{
		RUNE_SELF_PRESERVATION,
		"Rune of Self Preservation",
		"preservation",
		qtrue,			//dropOnDeath
		qtrue,			//deleteOnDeath
		qtrue,			//spawnable
		"icons/selfpres",
		{
			"Your attacks can't hurt you",
			"Immune to Vengeance",
			""
		},
		qfalse,
		qtrue,
	},
	{
		RUNE_ACTION_MOVIE,
		"Action Movie Arsenal",
		"arsenal",
		qtrue,			//dropOnDeath
		qtrue,			//deleteOnDeath
		qtrue,			//spawnable
		"icons/arsenal",
		{
			"Gives ammo and weapons",
			"",
			""
		},
		qfalse,
		qtrue,
	},
	{
		RUNE_FLIGHT,
		"Rune of Flight",
		"flight",
		qtrue,			//dropOnDeath
		qtrue,			//deleteOnDeath
		qtrue,			//spawnable
		"icons/flight",
		{
			"Gravity does not affect you",
			"",
			""
		},
		qfalse,
		qfalse,
	},
	{
		RUNE_SHIELD,
		"Rune of Shielding",
		"shield",
		qtrue,					//dropOnDeath
		qtrue,					//deleteOnDeath
		qtrue,					//spawnable
		"icons/shield",
		{
			"Invulnerability for 3",
			"seconds when activated",
			"5 second recharge"
		},
		qfalse,
		qfalse,
	},
	{
		RUNE_SPRINT,
		"Sprint Rune",
		"sprint",
		qtrue,					//dropOnDeath
		qtrue,					//deleteOnDeath
		qtrue,					//spawnable
		"icons/sprint",
		{
			"Activate for a massive",
			"burst of running speed",
			""
		},
		qfalse,
		qfalse,
	},
	{
		RUNE_OVERKILL,
		"Rune of Overkill",
		"overkill",
		qtrue,					//dropOnDeath
		qtrue,					//deleteOnDeath
		qtrue,					//spawnable
		"icons/overkill",
		{
			"Greatly increased",
			"rate of fire",
			""
		},
		qfalse,
		qtrue,
	},
	{
		RUNE_TELEPORT,
		"Teleport Shuffle",
		"teleport",
		qtrue,					//dropOnDeath
		qtrue,					//deleteOnDeath
		qtrue,					//spawnable
		"icons/teleport",
		{
			"Activate to teleport anywhere",
			"you can see",
			"Telefrag your enemies"
		},
		qfalse,
		qfalse,
	},
	{
		RUNE_SWITCH,
		"Switch Rune",
		"switch",
		qtrue,					//dropOnDeath
		qtrue,					//deleteOnDeath
		qtrue,					//spawnable
		"icons/switch",
		{
			"Activate to switch place, items,",
			"ammo and powerups with enemy",
			""
		},
		qfalse,
		qfalse,
	},
	{
		RUNE_NEGATION,
		"Rune of Negation",	
		"negation",
		qtrue,					//dropOnDeath
		qtrue,					//deleteOnDeath
		qtrue,					//spawnable
		"icons/negation",
		{
			"Used once on an enemy then removed",
			"Removes all weapons, ammo, and powerups",
			"Costs 50 health!"
		},
		qfalse,
		qfalse,
	},
	{
		RUNE_REFLECTION,
		"Rune of Reflection",
		"reflection",
		qtrue,					//dropOnDeath
		qtrue,					//deleteOnDeath
		qtrue,					//spawnable
		"icons/reflection",
		{
			"Reflects some projectiles",
			"and rune effects",
			"You are immune to rail shots"
		},
		qfalse,
		qtrue,
	},
	{
		RUNE_PHASE,
		"Phase Rune",
		"phase",
		qtrue,					//dropOnDeath
		qtrue,					//deleteOnDeath
		qtrue,					//spawnable
		"icons/phase",
		{
			"Stand near a wall and",
			"activate to walk through the wall",
			"USE AT OWN RISK!!"
		},
		qfalse,
		qtrue,
	},
	{
		RUNE_IMPACT,
		"Impact Rune",
		"impact",
		qtrue,					//dropOnDeath
		qtrue,					//deleteOnDeath
		qtrue,					//spawnable
		"icons/impact",
		{
			"Attacks move foes around and",
			"hurt more, hockey-style checking",
			"does serious damage"
		},
		qfalse,
		qtrue,
	},
	{
		RUNE_ATHLETICS,
		"Rune of Athletics",
		"athletics",
		qtrue,					//dropOnDeath
		qtrue,					//deleteOnDeath
		qtrue,					//spawnable
		"icons/athletics",
		{
			"Run and shoot faster",
			" more health,take less damage",
			"Activate to super jump!"
		},
		qfalse,
		qtrue,
	},
	{
		RUNE_FLASH,
		"Flash Rune",
		"flash",
		qtrue,					//dropOnDeath
		qtrue,					//deleteOnDeath
		qtrue,					//spawnable
		"icons/flash",
		{
			"Use to blind everyone in a",
			"certain radius",
			""
		},
		qfalse,
		qfalse,
	},
	{
		RUNE_DISARMAMENT,
		"Rune of Disarmament",
		"disarm",
		qtrue,					//dropOnDeath
		qtrue,					//deleteOnDeath
		qtrue,					//spawnable
		"icons/ceasefire",
		{
			"Use it to stun people",
			"around you and prevent",
			"them from firing weapons"
		},
		qfalse,
		qfalse,
	},
	{
		RUNE_EXCLUSION,
		"Rune of Exclusion",
		"exclusion",
		qtrue,					//dropOnDeath
		qtrue,					//deleteOnDeath
		qtrue,					//spawnable
		"icons/exclusion",
		{
			"Activate to randomly",
			"teleport anyone close",
			"to you"
		},
		qfalse,
		qfalse,
	}
	/*
	{
		RUNE_EMP,
		"Electromagnetic Pulse",
		"emp",
		qtrue,					//dropOnDeath
		qtrue,					//deleteOnDeath
		qtrue,					//spawnable
		"icons/emp",
		{
			"Activate to destroy all",
			"weapons in a radius",
			"including yours!"
		},
		qfalse,
		qfalse,
	},
	{
		RUNE_CLOAKING,
		"Rune of Cloaking",
		"cloaking",
		qtrue,					//dropOnDeath
		qtrue,					//deleteOnDeath
		qtrue,					//spawnable
		"icons/cloak",
		{
			"You are silent and",
			"invisible unless you fire",
			""
		},
		qfalse,
		qtrue,
	},
	{
		RUNE_LIGHTNING,
		"Rune of Lightning",
		"lightning",
		qtrue,					//dropOnDeath
		qtrue,					//deleteOnDeath
		qtrue,					//spawnable
		"icons/lightning",
		{
			"Enemies attacked with electricity",
			"when they get too close",
			"Avoid water!"
		},
		qfalse,
		qtrue,
	},
	{
		RUNE_RECALL,
		"Rune of Recall",
		"recall",
		qtrue,					//dropOnDeath
		qtrue,					//deleteOnDeath
		qtrue,					//spawnable
		"icons/recall",
		{
			"Use once to set your recall point",
			"Use again to go back to that point",
			""
		},
		qfalse,
		qfalse,
	},
	{
		RUNE_DUAL_RECALL,
		"Rune of Dual Recall",
		"dual",
		qtrue,					//dropOnDeath
		qtrue,					//deleteOnDeath
		qtrue,					//spawnable
		"icons/dual",
		{
			"Activate to teleport to last",
			"place where you activated it",
			"Telefrag your enemies"
		},
		qfalse,
		qfalse,
	}
	{
		RUNE_GRAVITY,
		"Gravity Rune",
		"gravity",
		qtrue,					//dropOnDeath
		qtrue,					//deleteOnDeath
		qtrue,					//spawnable
		"icons/gravity",
		{
			"Sphere of gravity sucks",
			"in enemies and items",
			""
		},
		qfalse,
		qfalse,
	},
	{
		RUNE_ICE_TRAPS,
		"Ice Traps",
		"ice",
		qtrue,					//dropOnDeath
		qtrue,					//deleteOnDeath
		qtrue,					//spawnable
		"icons/ice_trap",
		{
			"Leave icy traps which",
			"immobilize when touched",
			""
		},
		qfalse,
		qfalse,
	},
	{
		RUNE_DEATH_SPOTS,
		"Death Spots",
		"death",
		qtrue,					//dropOnDeath
		qtrue,					//deleteOnDeath
		qtrue,					//spawnable
		"icons/death_spots",
		{
			"Leave black traps which",
			"kill anything when touched",
			""
		},
		qfalse,
		qfalse,
	},

	{
		RUNE_BLINK,
		"Blink Rune",
		"blink",
		qtrue,					//dropOnDeath
		qtrue,					//deleteOnDeath
		qtrue,					//spawnable
		"icons/blink",
		{
			"\"Random\" teleportation",
			"",
			""
		},
		qfalse,
		qfalse,
	},
	{
		RUNE_BOXER,
		"Boxer Rune",
		"boxer",
		qtrue,					//dropOnDeath
		qtrue,					//deleteOnDeath
		qtrue,					//spawnable
		"icons/boxer",
		{
			"Use your gauntlet to",
			"cause serious damage",
			"Max health is 250"
		},
		qfalse,
		qfalse,
	},
	{
		RUNE_RADIOACTIVITY,
		"Rune of Radioactivity",
		"radio",
		qtrue,					//dropOnDeath
		qtrue,					//deleteOnDeath
		qtrue,					//spawnable
		"icons/radioactivity",
		{
			"Irradiate areas, opponents die",
			"slowly but you are healed",
			"3 areas maximum"
		},
		qfalse,
		qtrue,
	},
	{
		RUNE_QUAD_DAMAGE,
		"Rune of Quad Damage",
		"quad",
		qtrue,					//dropOnDeath
		qtrue,					//deleteOnDeath
		qtrue,					//spawnable
		"icons/quad",
		{
			"Quad damage for 3",
			"seconds when activated",
			"5 second recharge"
		},
		qfalse,
		qfalse,
	},
	{
		RUNE_PHOENIX,
		"Phoenix Rune",
		"phoenix",
		qfalse,					//dropOnDeath
		qfalse,					//deleteOnDeath
		qtrue,					//spawnable
		"icons/phoenix",
		{
			"Come back to life with",
			"quad and items",
			"3 lives maximum"
		},
		qfalse,
		qtrue,
	},
	{
		RUNE_VAMPIRE,
		"Vampiric Rune",
		"vamp",
		qfalse,					//dropOnDeath
		qfalse,					//deleteOnDeath
		qtrue,					//spawnable
		"icons/vamp",
		{
			"Damage other players to",
			"get their health",
			""
		},
		qfalse,
		qtrue,
	},
	{
		RUNE_DIVINE_WIND,
		"Rune of Divine Wind",
		"divine",
		qfalse,					//dropOnDeath
		qtrue,					//deleteOnDeath
		qtrue,					//spawnable
		"icons/divine",
		{
			"Kamikaze attack kills",
			"everyone in view",
			"Use to start countdown"
		},
		qfalse,
		qfalse,
	},
	{
		RUNE_JUMPING,
		"Rune of Uncontrollable Jumping",
		"jumping",
		qtrue,					//dropOnDeath
		qtrue,					//deleteOnDeath
		qtrue,					//spawnable
		"icons/jump",
		{
			"Enemies jump uncontrollably",
			"when in view",
			""
		},
		qfalse,
		qtrue,
	},
	{
		RUNE_DEATH_ORB,
		"Orb of Death",
		"orb",
		qtrue,					//dropOnDeath
		qtrue,					//deleteOnDeath
		qtrue,					//spawnable
		"icons/orb",
		{
			"Sphere of death circles you and",
			"damages enemies upon contact",
			""
		},
		qfalse,
		qtrue,
	},
	{
		RUNE_REPULSION,
		"Rune of Repulsion",
		"repulsion",
		qtrue,					//dropOnDeath
		qtrue,					//deleteOnDeath
		qtrue,					//spawnable
		"icons/repulsion",
		{
			"Push rockets, death spots,",
			"and people back from you",
			"Use it to push people"
		},
		qfalse,
		qtrue,
	},
	{
		RUNE_ILLUSION,
		"Rune of Illusions",
		"illusion",
		qtrue,					//dropOnDeath
		qtrue,					//deleteOnDeath
		qtrue,					//spawnable
		"icons/illusion",
		{
			"Your body appears slightly",
			"offset of where you actually are,",
			"throwing off enemy's aim"
		},
		qfalse,
		qtrue,
	},
	{
		RUNE_HOLOGRAM,
		"Holorune",
		"holo",
		qtrue,					//dropOnDeath
		qtrue,					//deleteOnDeath
		qtrue,					//spawnable
		"icons/hologram",
		{
			"Activate to leave holograms",
			"of yourself whereever you are",
			"standing.  6 maximum."
		},
		qfalse,
		qfalse,
	},
	{
		RUNE_WEIRDNESS,
		"Rune of Weirdness",
		"weird",
		qtrue,					//dropOnDeath
		qtrue,					//deleteOnDeath
		qtrue,					//spawnable
		"icons/weirdness",
		{
			"Small colored balls induce",
			"drug-like effects in foes",
			""
		},
		qfalse,
		qtrue,
	},
	{
		RUNE_FIRE,
		"Rune of Fire",
		"fire",
		qtrue,					//dropOnDeath
		qtrue,					//deleteOnDeath
		qtrue,					//spawnable
		"icons/fire",
		{
			"Better flame weapons",
			"Up to 6 flaming traps",
			"Beware of water!"
		},
		qfalse,
		qtrue,
	},
	{
		RUNE_PACK_RAT,
		"Pack Rat",
		"packrat",
		qtrue,					//dropOnDeath
		qtrue,					//deleteOnDeath
		qtrue,					//spawnable
		"icons/packrat",
		{
			"Collect runes to score",
			"bonus frags with each kill",
			""
		},
		qfalse,
		qtrue,
	},
	{
		RUNE_TRANSFERENCE,
		"Rune of Transference",
		"transfer",
		qtrue,					//dropOnDeath
		qtrue,					//deleteOnDeath
		qtrue,					//spawnable
		"icons/transference",
		{
			"Use on a person to transfer",
			"a portion of the damage you",
			"take to them"
		},
		qfalse,
		qfalse,
	},
	{
		RUNE_MEDIC,
		"Medic Rune",
		"medic",
		qtrue,					//dropOnDeath
		qtrue,					//deleteOnDeath
		qtrue,					//spawnable
		"icons/medic",
		{
			"Teammates around you slowly heal.",
			"Use on a teammate to give them a",
			"health boost."
		},
		qtrue,
		qtrue,
	},
	{
		RUNE_LUCK,
		"Rune of Luck",
		"luck",
		qtrue,					//dropOnDeath
		qtrue,					//deleteOnDeath
		qtrue,					//spawnable
		"icons/luck",
		{
			"When you take deadly damage",
			"will (possibly) teleport you",
			"away with no armor and 50 health"
		},
		qfalse,
		qtrue,
	},
	{
		RUNE_PLAGUE,
		"Plague Rune",
		"plague",
		qtrue,					//dropOnDeath
		qtrue,					//deleteOnDeath
		qtrue,					//spawnable
		"icons/plague",
		{
			"Infect people with a disease",
			"that can only be cured by",
			"getting a health box"
		},
		qfalse,
		qtrue,
	}
*/
};

char *getRuneName(int runeNum)
{
	if (runeNum>RUNE_TOTAL)
		return "INVALID RUNE NUMBER";

	return runeInfo[runeNum].runeName;
}

char *getRuneIcon(int runeNum)
{
	if (runeNum>RUNE_TOTAL)
		return "INVALID RUNE NUMBER";

	return runeInfo[runeNum].runeIcon;
}

char *getRuneDesc(int runeNum, int descNumber)
{
	if (runeNum>RUNE_TOTAL)
		return "INVALID RUNE NUMBER";

	if (descNumber >= RUNE_MAX_DESCRIPTION_LINES)
		return "INVALID DESC NUMBER";
	else
		return runeInfo[runeNum].runeDescription[descNumber];
}

qboolean hasRuneDesc(int runeNum, int descNumber)
{
	if (runeNum>RUNE_TOTAL)
		return qfalse;

	if (descNumber >= RUNE_MAX_DESCRIPTION_LINES)
		return qfalse;
	else
		return Q_stricmp(runeInfo[runeNum].runeDescription[descNumber],"");
}

qboolean deleteOnDeath(int runeNum)
{
	if (runeNum>RUNE_TOTAL)
		return qfalse;

	return runeInfo[runeNum].deleteOnDeath;
}

qboolean dropOnDeath(int runeNum)
{
	if (runeNum>RUNE_TOTAL)
		return qfalse;

	return runeInfo[runeNum].dropOnDeath;
}

int getRuneIDFromName(char *runeName)
{
	int i;
	for(i=1;i<=RUNE_TOTAL;i++)
	{
		if (!Q_stricmp(runeInfo[i].shortName,runeName))
		{
			return runeInfo[i].RuneID;
		}
	}

	return 0;
}

void banRune(int runeNum)
{
	if (!(runeNum>RUNE_TOTAL))
	{
		runeInfo[runeNum].spawnable = qfalse;
	}
}

qboolean isBanned(int runeNum)
{
	if (!(runeNum>RUNE_TOTAL))
		return !runeInfo[runeNum].spawnable;

	return qfalse;
}

void unbanRune(int runeNum)
{
	if (!(runeNum>RUNE_TOTAL))
	{
		runeInfo[runeNum].spawnable = qtrue;		
	}
}

qboolean spawnable(int runeNum)
{
	if (!(runeNum>RUNE_TOTAL))
		return runeInfo[runeNum].spawnable;

	return qfalse;
}

qboolean canBotUse(int runeNum)
{
	if (!(runeNum>RUNE_TOTAL))
		return runeInfo[runeNum].botRune;

	return qfalse;
}

qboolean isTeamRune(int runeNum)
{
	if (!(runeNum>RUNE_TOTAL))
		return runeInfo[runeNum].teamRune;

	return qfalse;
}

void MarkTeamRunes(qboolean spawnable)
{
	int i=1;

	for (i=1;i<=RUNE_TOTAL;i++)
	{
		if (isTeamRune(i))
		{
			if (spawnable)
				unbanRune(i);
			else
				banRune(i);
		}
	}
}

#else

char *getRuneName(int runeNum);
char *getRuneIcon(int runeNum);
char *getRuneDesc(int runeNum, int descNumber);
qboolean hasRuneDesc(int runeNum, int descNumber);
qboolean deleteOnDeath(int runeNum);
qboolean dropOnDeath(int runeNum);
int getRuneIDFromName(char *runeName);
void banRune(int runeNum);
void unbanRune(int runeNum);
qboolean spawnable(int runeNum);
qboolean canBotUse(int runeNum);
qboolean isTeamRune(int runeNum);
void MarkTeamRunes(qboolean spawnable);
#endif

