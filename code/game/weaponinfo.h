#ifndef WEAPON_FUNCS
#define	WEAPON_FUNCS

struct s_weaponInfo
{
	int			WeaponID;						// the #define WP_
	char		*shortName;						// Abbreviated lower case name of the weapon ie "machinegun"
	char		*className;						// classname of the weapon ie weapon_machinegun
	char		*ammoClassname;					// classname of the ammo for this weapon ie ammo_bullets
	qboolean	spawn;							// do you spawn with this weapon?
	int			spawnAmount;					// if spawn = true, then how much ammo you spawn with
												// -1 = infinite ammo
	qboolean	banned;							// is this weapon banned on this level
	int			regenRate;						// how fast this weap regens ammo with Action Movie
	int			threshold;						// how many ammo you need to have for Action Movie
												//  to give you the weapon
};



// NOTE:  The number of slot that each of these goes into MUST MATCH EXACTLY the WP_ number of the weapon
struct s_weaponInfo weaponInfo[] = 
{
	{
		WP_NONE,
		"none",
		"weapon_none",
		"ammo_none",
		qfalse,
		0,
		qfalse,
		0,
		0,
	},
	{
		WP_GAUNTLET,
		"gauntlet",
		"weapon_gauntlet",
		"ammo_none",
		qtrue,
		-1,
		qfalse,
		0,
		0,
	},
	{
		WP_MACHINEGUN,
		"machinegun",
		"weapon_machinegun",
		"ammo_bullets",
		qtrue,
		100,
		qfalse,
		2,
		0,
	},
	{
		WP_SHOTGUN,
		"shotgun",
		"weapon_shotgun",
		"ammo_shells",
		qfalse,
		0,
		qfalse,
		1,
		10,
	},
	{
		WP_GRENADE_LAUNCHER,
		"grenade",
		"weapon_grenadelauncher",
		"ammo_grenades",
		qfalse,
		0,
		qfalse,
		1,
		13,
	},
	{
		WP_ROCKET_LAUNCHER,
		"rocket",
		"weapon_rocketlauncher",
		"ammo_rockets",
		qfalse,
		0,
		qfalse,
		1,
		15,
	},
	{
		WP_LIGHTNING,
		"lightning",
		"weapon_lightning",
		"ammo_lightning",
		qfalse,
		0,
		qfalse,
		2,
		30,
	},
	{
		WP_RAILGUN,
		"railgun",
		"weapon_railgun",
		"ammo_slugs",
		qfalse,
		0,
		qfalse,
		1,
		20,
	},
	{
		WP_PLASMAGUN,
		"plasma",
		"weapon_plasmagun",
		"ammo_cells",
		qfalse,
		0,
		qfalse,
		2,
		25,
	},
	{
		WP_BFG,
		"bfg",
		"weapon_bfg",
		"ammo_bfg",
		qfalse,
		0,
		qfalse,
		1,
		30,
	}
};


int getWeaponIDFromName(char *weaponName)
{
	int i;
	for(i=1;i<WP_NUM_WEAPONS;i++)
	{
		if (!Q_strncmp(weaponInfo[i].shortName,weaponName,strlen(weaponInfo[i].shortName)))
		{
			return weaponInfo[i].WeaponID;
		}
	}

	return 0;
}

int getWeaponIDFromClassname(char *weaponName)
{
	int i;
	for(i=1;i<WP_NUM_WEAPONS;i++)
	{
		if (!Q_strncmp(weaponInfo[i].shortName,weaponName,strlen(weaponInfo[i].shortName)))
		{
			return weaponInfo[i].WeaponID;
		}
	}

	return 0;
}

char *getClassnameFromWeaponNum(int weaponNum)
{
	return weaponInfo[weaponNum].className;
}

char *getAmmoClassnameFromWeaponNum(int weaponNum)
{
	return weaponInfo[weaponNum].ammoClassname;
}


void banWeapon(int weaponNum)
{
	gentity_t *ent;
	if (!(weaponNum>WP_NUM_WEAPONS))
	{
		weaponInfo[weaponNum].banned = qtrue;

		while (ent = G_Find (NULL, FOFS(classname),getClassnameFromWeaponNum(weaponNum)))
		{
			G_FreeEntity(ent);
		}
	}
}

qboolean isWeaponBanned(int weaponNum)
{
	if (!(weaponNum>WP_NUM_WEAPONS))
		return weaponInfo[weaponNum].banned;

	return qfalse;
}

int getWeaponRegen(int weaponNum)
{
	if (!(weaponNum>WP_NUM_WEAPONS))
		return weaponInfo[weaponNum].regenRate;

	return 0;
}

int getWeaponThreshold(int weaponNum)
{
	if (!(weaponNum>WP_NUM_WEAPONS))
		return weaponInfo[weaponNum].threshold;

	return 0;
}

void unbanWeapon(int weaponNum)
{
	if (!(weaponNum>WP_NUM_WEAPONS))
	{
		weaponInfo[weaponNum].banned = qfalse;		
	}
}

void addWeapon(int weaponNum, int ammo)
{
	if (!(weaponNum>WP_NUM_WEAPONS))
	{
		weaponInfo[weaponNum].spawn = qtrue;
		weaponInfo[weaponNum].spawnAmount = ammo;	
		unbanWeapon(weaponNum);
	}
}

void removeWeapon(int weaponNum)
{
	if (!(weaponNum>WP_NUM_WEAPONS))
	{
		weaponInfo[weaponNum].spawn = qfalse;
		weaponInfo[weaponNum].spawnAmount = 0;	
	}
}

qboolean spawnWithWeapon(int weaponNum)
{
	return weaponInfo[weaponNum].spawn;
}

// this function should be preceeded by a check to spawnWithWeapon()
int getStartingAmmo(int weaponNum)
{
	return weaponInfo[weaponNum].spawnAmount;
}

#else

int getWeaponIDFromName(char *weaponName);
void banWeapon(int weaponNum);
qboolean isWeaponBanned(int weaponNum);
void unbanWeapon(int weaponNum);
void addWeapon(int weaponNum, int ammo);
void removeWeapon(int weaponNum);

#endif

