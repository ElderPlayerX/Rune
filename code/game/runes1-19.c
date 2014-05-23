#include "g_local.h"

////////////////////////////////////////////////
//
//	Runes1-19.c
//		functions for Runes 1-19
//
//		Enviro, Action Movie


////////////////////////////////////////////////
//
//		Environmental Protection
//
void Rune_Enviro_Use(gentity_t *ent)
{
	if (ent->waterlevel==2)
	{
		ent->client->ps.velocity[2] = 900;
	}
}

////////////////////////////////////////////////
//
//		Action Movie Arsenal
//

void Rune_ActionMovie_Use(gentity_t *ent)
{
	if (ent->runevar == 1)
	{
		trap_SendServerCommand( ent->s.clientNum, va("print \"Now Charging All Weapons\n\""));
		ent->runevar = 0;
	}
	else
	{
		trap_SendServerCommand( ent->s.clientNum, va("print \"Now Charging Currently Equipped Weapon ONLY\n\""));
		ent->runevar = 1;
	}
}

void Rune_ActionMovie_AddAmmo(gentity_t *ent,int weapon)
{
	ent->client->ps.ammo[weapon] +=getWeaponRegen(weapon);
	if (ent->client->ps.ammo[weapon]>200)
		ent->client->ps.ammo[weapon]=200;

	if (getWeaponThreshold(weapon)>0)
	{
		if (ent->client->ps.ammo[weapon]>=getWeaponThreshold(weapon))
			ent->client->ps.stats[STAT_WEAPONS] |= ( 1 << weapon );
	}
}

int Rune_ActionMovie_Think(gentity_t *ent, qboolean allWeapons)
{
	int i=0;

	if (allWeapons)
	{
		for (i=WP_MACHINEGUN;i<WP_NUM_WEAPONS;i++)
		{
			if (!isWeaponBanned(i))
				Rune_ActionMovie_AddAmmo(ent,i);
		}
		return level.time+2000;
	}
	else
	{
		Rune_ActionMovie_AddAmmo(ent,ent->client->ps.weapon);
		return level.time+1200;
	}
	
}


////////////////////////////////////////////////
//
//		Flight
//

void Rune_Flight_Think(gentity_t *ent)
{
	if (g_RuneFlightDuration.integer >0)
	{
		if (ent->runetime < level.time)
		{
			Rune_Delete(ent,qfalse);
		}
		else
		{
			ent->client->ps.stats[STAT_RUNE_COUNTER]=(ent->runetime - level.time)/1000;
		}
	}
}



////////////////////////////////////////////////
//
//		Shield
//

// runevar values
//	0 - shield has been activated and no shield request is pending
//	1 - shield request pending, as soon as it recharges, it will activate
void Rune_Shield_Use(gentity_t *ent)
{
	if (ent->runetime<level.time)
	{
		ent->client->ps.powerups[PW_SHIELD] = level.time + RUNE_SHIELD_DURATION;
		ent->runetime = level.time + RUNE_SHIELD_DURATION + RUNE_SHIELD_RECHARGE;
		ent->runevar=0;
		ent->client->ps.stats[STAT_RUNE_COUNTER]=0;
	}
	else
	{
		if (ent->runevar==0)
		{
			trap_SendServerCommand( ent->s.clientNum, va("print \"Shield is recharging\n\""));
			ent->runevar=1;
		}
		else
		{
			trap_SendServerCommand( ent->s.clientNum, va("print \"Shield activation cancelled\n\""));
			ent->runevar=0;
		}
	}
}



////////////////////////////////////////////////
//
//		Sprint
//

// runevar values
//	0 - sprint has been activated and no sprint request is pending
//	1 - sprint request pending, as soon as it recharges, it will activate
void Rune_Sprint_Use(gentity_t *ent)
{
	if (ent->runetime<level.time)
	{
		ent->client->ps.powerups[PW_HASTE] = level.time + RUNE_SPRINT_DURATION;
		ent->runetime = level.time + RUNE_SPRINT_DURATION + RUNE_SPRINT_RECHARGE;
		ent->runevar=0;
		ent->client->ps.stats[STAT_RUNE_COUNTER]=0;
	}
	else
	{
		if (ent->runevar==0)
		{
			trap_SendServerCommand( ent->s.clientNum, va("print \"Sprint is recharging\n\""));
			ent->runevar=1;
		}
		else
		{
			trap_SendServerCommand( ent->s.clientNum, va("print \"Sprint activation cancelled\n\""));
			ent->runevar=0;
		}
	}
}

////////////////////////////////////////////////
//
//		Teleport Shuffle
//

void Rune_Teleport_Use(gentity_t *ent)
{
	gentity_t *traceEnt;
	vec3_t muzzle,forward,right,up,end,min,max;
	trace_t trace;

	if (ent->runetime>level.time)
		return;

	ent->runetime = level.time+1000;

	VectorSet (min, -ITEM_RADIUS, -ITEM_RADIUS, -ITEM_RADIUS);
	VectorSet (max, ITEM_RADIUS, ITEM_RADIUS, ITEM_RADIUS);

	AngleVectors (ent->client->ps.viewangles, forward, right, up);
	CalcMuzzlePoint ( ent, forward, right, up, muzzle );

	VectorMA (muzzle, 3000, forward, end);
	trap_Trace (&trace, muzzle, min, max, end, ent->s.number, MASK_PLAYERSOLID );
	SnapVectorTowards( trace.endpos, muzzle );

	if ( trace.entityNum < ENTITYNUM_MAX_NORMAL ) 
	{
		traceEnt = &g_entities[ trace.entityNum ];
		if (traceEnt->inuse)
		{
			if ( traceEnt->takedamage && !Q_stricmp(traceEnt->classname,"player"))
			{
				if (traceEnt->client)
				{
					if (traceEnt->client->ps.powerups[RUNE_POWERUP_SLOT]!= RUNE_EXCLUSION)
					{
						if ((int)(random()*100)%100 < RUNE_TELEPORT_TELEFRAG_CHANCE)
						{
							TeleportPlayer(ent,traceEnt->client->ps.origin,ent->client->ps.viewangles, qtrue, qfalse );	
						}
						else
						{
							SwapPlayerPositions(ent,traceEnt);
							trap_SendServerCommand( traceEnt->s.clientNum, va("print \"Someone switched places with you!\n\""));
							//Rune_SetEffect(traceEnt,EFFECT_SWITCHED,3);
							return;
						}
					}
				}
			}
		}
		return;
	}
	
	
	// if we didn't trace a player, then we traced a solid of some sort.
	//		pull yourself back some units and then teleport there
	VectorInverse(forward);
	VectorMA (trace.endpos, 75, forward, end);
	if(	!( trap_PointContents( end, -1 ) & CONTENTS_SOLID))
		TeleportPlayer(ent,end,ent->client->ps.viewangles, qtrue, qfalse);

}



////////////////////////////////////////////////
//
//		Switch
//

void LookAtSwitcher( gentity_t *switchee, gentity_t *switcher ) 
{
	vec3_t		dir;
	vec3_t		angles;

	VectorSubtract (switcher->s.pos.trBase, switchee->s.pos.trBase, dir);

	angles[YAW] = vectoyaw ( dir );
	angles[PITCH] = 0; 
	angles[ROLL] = 0;

	VectorCopy(angles,switchee->client->ps.viewangles);
}

void Rune_Switch_Use(gentity_t *ent)
{
	gentity_t *traceEnt,*tent;
	vec3_t muzzle,forward,right,up,end,min,max;
	trace_t trace;
	int tempInt,i;

	if (ent->runetime>level.time)
		return;

	// prevent keyboard repeat
	ent->runetime = level.time + 100;

	VectorSet (min, -ITEM_RADIUS, -ITEM_RADIUS, -ITEM_RADIUS);
	VectorSet (max, ITEM_RADIUS, ITEM_RADIUS, ITEM_RADIUS);

	AngleVectors (ent->client->ps.viewangles, forward, right, up);
	CalcMuzzlePoint ( ent, forward, right, up, muzzle );

	VectorMA (muzzle, 3000, forward, end);
	trap_Trace (&trace, muzzle, min, max, end, ent->s.number, MASK_PLAYERSOLID );
	SnapVectorTowards( trace.endpos, muzzle );


	if ( trace.entityNum < ENTITYNUM_MAX_NORMAL ) 
	{
		traceEnt = &g_entities[ trace.entityNum ];
		if (traceEnt->inuse)
		{
			if ( traceEnt->takedamage && !Q_stricmp(traceEnt->classname,"player"))
			{
				if (traceEnt->client)
				{
					if (Can_Affect_Player(ent,traceEnt) && traceEnt->client->ps.powerups[RUNE_POWERUP_SLOT]!= RUNE_EXCLUSION)
					{
						// Swap Weapons
						tempInt = traceEnt->client->ps.stats[STAT_WEAPONS];
						traceEnt->client->ps.stats[STAT_WEAPONS] = ent->client->ps.stats[STAT_WEAPONS];
						ent->client->ps.stats[STAT_WEAPONS] = tempInt;

						// Swap Ammo
						for (i=0;i<WP_NUM_WEAPONS;i++)
						{
							tempInt = ent->client->ps.ammo[i];
							ent->client->ps.ammo[i] = traceEnt->client->ps.ammo[i];
							traceEnt->client->ps.ammo[i] = tempInt;
						}

						// Swap Quad, if either of them has it
						tempInt = ent->client->ps.powerups[PW_QUAD];
						ent->client->ps.powerups[PW_QUAD] = traceEnt->client->ps.powerups[PW_QUAD];
						traceEnt->client->ps.powerups[PW_QUAD] = tempInt;

						// Swap Health
						tempInt = ent->health;
						ent->health = traceEnt->health;
						traceEnt->health = tempInt;

						ent->client->ps.stats[STAT_HEALTH] = ent->health;
						traceEnt->client->ps.stats[STAT_HEALTH] = traceEnt->health;

						// Swap Armor
						tempInt=ent->client->ps.stats[STAT_ARMOR];
						ent->client->ps.stats[STAT_ARMOR] = traceEnt->client->ps.stats[STAT_ARMOR];
						traceEnt->client->ps.stats[STAT_ARMOR] = tempInt;

						// switch ent to highest weapon
						ent->client->ps.weapon = 1;
						for ( i = WP_NUM_WEAPONS - 1 ; i > 0 ; i-- ) 
						{
							if ( ent->client->ps.stats[STAT_WEAPONS] & ( 1 << i ) ) 
							{
								ent->client->ps.weapon = i;
								break;
							}
						}

						// switch traceEnt to highest weapon
						traceEnt->client->ps.weapon = 1;
						for ( i = WP_NUM_WEAPONS - 1 ; i > 0 ; i-- ) 
						{
							if ( traceEnt->client->ps.stats[STAT_WEAPONS] & ( 1 << i ) ) 
							{
								traceEnt->client->ps.weapon = i;
								break;
							}
						}

						// Swap positions
						SwapPlayerPositions(ent,traceEnt);
						trap_SendServerCommand( traceEnt->s.clientNum, va("print \"You've been switched!\n\""));
						//Rune_SetEffect(traceEnt,EFFECT_SWITCHED,3);
						LookAtSwitcher(traceEnt,ent);

						//Draw a bolt between the two
						tent = G_TempEntity( ent->client->ps.origin, EV_LIGHTNINGBOLT );
						VectorCopy( traceEnt->client->ps.origin, tent->s.origin2 );

						tent->s.frame = 150; // length of time bolt is visible
						tent->s.eventParm = 255; // don't make the explosion at the end

						// remember who controls the bolt
						tent->s.clientNum = traceEnt->s.clientNum;
					}
				}
			}
		}
	}
}


////////////////////////////////////////////////
//
//		Negation
//

void Rune_Negation_Use(gentity_t *ent)
{
	gentity_t *traceEnt;
	vec3_t muzzle,forward,right,up,end,min,max;
	trace_t trace;
	int i;
	gitem_t *item;
	item = NULL;

	if (ent->runetime>level.time)
		return;

	// prevent keyboard repeat
	ent->runetime = level.time + 100;

	VectorSet (min, -ITEM_RADIUS, -ITEM_RADIUS, -ITEM_RADIUS);
	VectorSet (max, ITEM_RADIUS, ITEM_RADIUS, ITEM_RADIUS);

	AngleVectors (ent->client->ps.viewangles, forward, right, up);
	CalcMuzzlePoint ( ent, forward, right, up, muzzle );

	VectorMA (muzzle, 3000, forward, end);
	trap_Trace (&trace, muzzle, min, max, end, ent->s.number, MASK_PLAYERSOLID );
	SnapVectorTowards( trace.endpos, muzzle );


	if ( trace.entityNum < ENTITYNUM_MAX_NORMAL ) 
	{
		traceEnt = &g_entities[ trace.entityNum ];
		if (traceEnt->inuse)
		{
			if ( traceEnt->takedamage && !Q_stricmp(traceEnt->classname,"player"))
			{
				if (Can_Affect_Player(ent,traceEnt))
			
					if (traceEnt->client->ps.powerups[RUNE_POWERUP_SLOT] == RUNE_REFLECTION)
					{
						// Negate Weapons
						ent->client->ps.stats[STAT_WEAPONS] = 0;
						ent->client->ps.stats[STAT_WEAPONS] = ( 1 << WP_MACHINEGUN );
						ent->client->ps.stats[STAT_WEAPONS] |= ( 1 << WP_GAUNTLET ); 

						// Negate Ammo (except for machinegun)
						for (i=WP_SHOTGUN;i<WP_NUM_WEAPONS;i++)
						{
							ent->client->ps.ammo[i] = 0;
						}

						// Negate Quad
						ent->client->ps.powerups[PW_QUAD] = 0;

						// Negate Armor
						ent->client->ps.stats[STAT_ARMOR] = 0;

						// Negate Rune
						Cmd_Rune_Drop(ent,qtrue);

						// switch to machine gun
						ent->client->ps.weapon = WP_MACHINEGUN;

						// negate flag in CTF
						if ( ent->client->ps.powerups[ PW_REDFLAG ] ) 
						{
							item = BG_FindItemForPowerup( PW_REDFLAG );
							i = PW_REDFLAG;
						} 
						else if ( ent->client->ps.powerups[ PW_BLUEFLAG ] ) 
						{
							item = BG_FindItemForPowerup( PW_BLUEFLAG );
							i = PW_BLUEFLAG;
						}

						if ( item ) 
						{
							ent->client->ps.powerups[ i ] = 0;

							Team_ReturnFlagSound(Team_ResetFlag(traceEnt->client->sess.sessionTeam), traceEnt->client->sess.sessionTeam);
							PrintMsg( NULL, "%s" S_COLOR_WHITE " returned the %s flag!\n", traceEnt->client->pers.netname, TeamName(traceEnt->client->sess.sessionTeam));
							AddScore(traceEnt, traceEnt->r.currentOrigin, CTF_RECOVERY_BONUS);
							traceEnt->client->pers.teamState.flagrecovery++;
							traceEnt->client->pers.teamState.lastreturnedflag = level.time;

						}

						trap_SendServerCommand( ent->s.clientNum, va("print \"%s negated your items!!\n\"",traceEnt->client->pers.netname));
						//Rune_SetEffect(ent,EFFECT_REFLECTION,3);
						VectorSet(end,0,0,0);

						trap_SendServerCommand( traceEnt->s.clientNum, va("print \"%s negated your rune\n\"",ent->client->pers.netname));
						//Rune_SetEffect(traceEnt,EFFECT_NEGATION,3);

						G_Damage(ent,NULL,ent,end,end,RUNE_NEGATION_COST,0,MOD_RUNE_NEGATION);
						Cmd_Rune_Drop(ent,qtrue);
						Cmd_Rune_Drop(traceEnt,qtrue);
					}
					else
					{
						// Negate Weapons
						traceEnt->client->ps.stats[STAT_WEAPONS] = 0;
						traceEnt->client->ps.stats[STAT_WEAPONS] = ( 1 << WP_MACHINEGUN );
						traceEnt->client->ps.stats[STAT_WEAPONS] |= ( 1 << WP_GAUNTLET ); 

						// Negate Ammo (except for machinegun)
						for (i=WP_SHOTGUN;i<WP_NUM_WEAPONS;i++)
						{
							traceEnt->client->ps.ammo[i] = 0;
						}

						// Negate Quad
						traceEnt->client->ps.powerups[PW_QUAD] = 0;

						// Negate Armor
						traceEnt->client->ps.stats[STAT_ARMOR] = 0;

						// Negate Rune
						Cmd_Rune_Drop(traceEnt,qtrue);

						// switch to machine gun
						traceEnt->client->ps.weapon = WP_MACHINEGUN;

						// negate flag in CTF
						if ( traceEnt->client->ps.powerups[ PW_REDFLAG ] ) 
						{
							item = BG_FindItemForPowerup( PW_REDFLAG );
							i = PW_REDFLAG;
						} 
						else if ( traceEnt->client->ps.powerups[ PW_BLUEFLAG ] ) 
						{
							item = BG_FindItemForPowerup( PW_BLUEFLAG );
							i = PW_BLUEFLAG;
						}

						if ( item ) 
						{
							traceEnt->client->ps.powerups[ i ] = 0;

							Team_ReturnFlagSound(Team_ResetFlag(ent->client->sess.sessionTeam), ent->client->sess.sessionTeam);
							PrintMsg( NULL, "%s" S_COLOR_WHITE " returned the %s flag!\n", ent->client->pers.netname, TeamName(ent->client->sess.sessionTeam));
							AddScore(ent, ent->r.currentOrigin, CTF_RECOVERY_BONUS);
							ent->client->pers.teamState.flagrecovery++;
							ent->client->pers.teamState.lastreturnedflag = level.time;

						}

						trap_SendServerCommand( traceEnt->s.clientNum, va("print \"%s negated your items!!\n\"",ent->client->pers.netname));
						//Rune_SetEffect(traceEnt,EFFECT_NEGATION,3);
						VectorSet(end,0,0,0);
						G_Damage(ent,NULL,ent,end,end,RUNE_NEGATION_COST,0,MOD_RUNE_NEGATION);
						Cmd_Rune_Drop(ent,qtrue);
					//}
				}
			}
		}
	}
}