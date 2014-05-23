#include "g_local.h"
#include "rune.h"
#include "runeinfo.h"
#include "weaponInfo.h"

int runeTotal;
int bigCountTime;
int checkForSpawnerTime;

gentity_t *SelectRandomDeathmatchSpawnPoint( void );
gentity_t *LaunchItem( gitem_t *item, vec3_t origin, vec3_t velocity );


gentity_t *SelectRuneSpawnPoint( int seed )
{
	int iters, count=0;
	int targ=0;
	gentity_t *runespawn=g_entities;

	srand(level.time+seed);
	targ=(rand()%level.num_entities);
	if (targ<=MAX_CLIENTS)
		targ=MAX_CLIENTS;

	runespawn = &g_entities[targ];


	iters = (rand()%15)+1;
	for ( count=0; count<iters ; )
	{
		runespawn++;
		if (!(runespawn < &g_entities[level.num_entities]))
			runespawn=&g_entities[MAX_CLIENTS];

		if (!(runespawn->inuse))
			continue;

		if (!(runespawn->classname))
			continue;

		if ((runespawn->s.eType==ET_ITEM)||!Q_stricmp (runespawn->classname, "info_player_deathmatch")||!Q_stricmp (runespawn->classname, "team_CTF_redspawn")||!Q_stricmp (runespawn->classname, "team_CTF_bluespawn"))
			count++;
	}

	return runespawn;
	
}



void Rune_Initialize(gentity_t *ent, int runeType)
{
	gentity_t *tent;

	ent->client->ps.powerups[RUNE_POWERUP_SLOT] = runeType;
	ent->runeid = level.time;
	ent->runeDropDelay = level.time+(g_RuneDropTime.integer * 1000);

	switch (runeType)
	{
	case RUNE_STRENGTH:
		ent->client->ps.generic1 |= (1 << SFX_SOUND_QUAD);
		break;
	case RUNE_BERSERK:
		ent->client->ps.generic1 |= (1 << SFX_SHELL_BERSERK);
		ent->client->ps.generic1 |= (1 << SFX_SOUND_QUAD);
		break;
	case RUNE_HASTE:
		ent->client->ps.powerups[PW_HASTE]=level.time+1000000;
		break;
	case RUNE_GOOD_HEALTH:
		ent->health+=100;
		tent = G_TempEntity (ent->client->ps.origin, EV_DYNAMIC_SOUND);
		tent->s.eventParm = DYN_SOUND_MEGAHEALTH;
		break;
	case RUNE_PLENTIFUL_ARMOR:
		ent->client->ps.stats[STAT_ARMOR]+=100;
		tent = G_TempEntity (ent->client->ps.origin, EV_DYNAMIC_SOUND);
		tent->s.eventParm = DYN_SOUND_ARMOR;
		break;
	case RUNE_VENGEANCE:
		ent->client->ps.powerups[PW_VENGEANCE]=level.time+1000000;
		break;	
	case RUNE_FLIGHT:
		if (g_RuneFlightDuration.integer > 0)
		{
			ent->runetime = level.time + (g_RuneFlightDuration.integer*1000);
			ent->client->ps.stats[STAT_RUNE_COUNTER] = g_RuneFlightDuration.integer;
		}
		break;
	case RUNE_SHIELD:
		ent->runevar=0;
		ent->runetime = level.time;
		ent->client->ps.stats[STAT_RUNE_COUNTER]=0;
		break;
	case RUNE_SPRINT:
		ent->runevar=0;
		ent->runetime = level.time;
		ent->client->ps.stats[STAT_RUNE_COUNTER]=0;
	case RUNE_TELEPORT:
		ent->runetime = level.time + 100;
		break;	break;
	case RUNE_SWITCH:
		ent->runetime = level.time + 100;
		break;
	case RUNE_NEGATION:
		ent->runetime = level.time + 100;
		break;
	case RUNE_REFLECTION:
		ent->client->ps.generic1 |= (1 << SFX_SHELL_REFLECTION);
		break;
	case RUNE_PHASE:
		ent->runetime=level.time;
		ent->client->ps.powerups[PW_PHASE]=level.time+1000000;
		break;
	case RUNE_IMPACT:
		ent->runetime = level.time;
		break;
	case RUNE_ATHLETICS:
		ent->runevar=1;
		ent->runetime = level.time;
		break;
	case RUNE_FLASH:
		ent->runevar=0;
		ent->runetime = level.time;
		ent->client->ps.stats[STAT_RUNE_COUNTER]=0;		
		break;
	case RUNE_DISARMAMENT:
		ent->runevar=0;
		ent->runetime = level.time;
		ent->client->ps.stats[STAT_RUNE_COUNTER]=0;		
		break;

/*
	case RUNE_LIGHTNING:
		ent->runevar = 0;
		Rune_Lightning_Spawn(ent);
		break;
	case RUNE_CLOAKING:
		ent->runevar= 0;
		ent->runetime = level.time;
		break;
	case RUNE_GOOD_HEALTH:
		ent->health+=100;
		break;
	case RUNE_PLENTIFUL_ARMOR:
		ent->client->ps.stats[STAT_ARMOR]+=100;
		tent = G_TempEntity (ent->r.currentOrigin, EV_PLENTIFULARMOR);
		break;
	case RUNE_RECALL:
		ent->runevar=0;
		break;
	case RUNE_DUAL_RECALL:
		VectorCopy(ent->r.currentOrigin,ent->runevector);
		break;
	case RUNE_GRAVITY:
		ent->runevar=0;
		break;
	case RUNE_ICE_TRAPS:
		ent->runevar=RUNE_ICE_TRAP_NUMBER;
		break;
	case RUNE_DEATH_SPOTS:
		ent->runevar=RUNE_DEATH_SPOT_NUMBER;
		break;
	case RUNE_SHIELD:
		ent->runevar=0;
		ent->runetime = level.time;
		ent->client->ps.stats[STAT_RUNE_COUNTER]=0;
		break;
	case RUNE_BLINK:
		ent->runevar = level.time;
		ent->runetime = level.time;
		break;
	case RUNE_IMPACT:
		ent->runetime = level.time;
		break;
	case RUNE_RADIOACTIVITY:
		ent->runevar=RUNE_RADIOACTIVITY_NUMBER;
		break;
	case RUNE_QUAD_DAMAGE:
		ent->runevar=0;
		ent->runetime = level.time;
		ent->client->ps.stats[STAT_RUNE_COUNTER]=0;
		break;
	case RUNE_PHASE:
		ent->runetime=level.time;
		ent->client->ps.powerups[PW_PHASE]=level.time+10000000;
		break;
	case RUNE_PHOENIX:
		ent->runevar=RUNE_PHOENIX_NUMBER;
		break;
	case RUNE_TELEPORT:
		ent->runetime = level.time + 100;
		break;
	case RUNE_SWITCH:
		ent->runetime = level.time + 100;
		break;
	case RUNE_NEGATION:
		ent->runetime = level.time + 100;
		break;
	case RUNE_ATHLETICS:
		ent->runetime = level.time;
		break;
	case RUNE_DIVINE_WIND:
		ent->runevar=-1;
		ent->client->ps.stats[STAT_RUNE_COUNTER]=0;
		Rune_Divine_Wind_Hat_Spawn(ent);
		break;
	case RUNE_JUMPING:
		ent->runetime = level.time;
		break;
	case RUNE_DEATH_ORB:
		Rune_Death_Orb_Spawn(ent);
		break;
	case RUNE_REPULSION:
		ent->runevar = level.time-1;
		ent->runetime = level.time-1;
		break;
	case RUNE_ILLUSION:
		ent->client->ps.powerups[PW_ILLUSION]=level.time+10000000;
		break;
	case RUNE_HOLOGRAM:
		ent->runevar=RUNE_HOLOGRAM_NUMBER;
		break;
	case RUNE_WEIRDNESS:
		ent->runetime = level.time;
		ent->runevar = level.time;
		break;
	case RUNE_FIRE:
		ent->client->ps.powerups[PW_BURNING]=level.time+10000000;
		ent->runevar = RUNE_FIRE_TRAP_NUMBER;
		break;
	case RUNE_PACK_RAT:
		ent->runevar=0;
		ent->runeentity = NULL;
	case RUNE_SPRINT:
		ent->runevar=0;
		ent->runetime = level.time;
		ent->client->ps.stats[STAT_RUNE_COUNTER]=0;
		break;
	case RUNE_EXCLUSION:
		ent->runevar=0;
		ent->runetime = level.time;
		ent->client->ps.stats[STAT_RUNE_COUNTER]=0;		
		break;
	case RUNE_TRANSFERENCE:
		if (ent->runeentity)
		{
			if (ent->runeentity->health < 0)
				ent->runeentity=0;
		}
		break;

	case RUNE_MEDIC:
		ent->runetime = level.time-1;
		break;
	case RUNE_FLASH:
		ent->runevar=0;
		ent->runetime = level.time;
		ent->client->ps.stats[STAT_RUNE_COUNTER]=0;		
		break;
	case RUNE_LUCK:
		ent->runetime = 0;
		break;
	case RUNE_REFLECTION:
		ent->client->ps.powerups[PW_REFLECTION]=level.time+10000000;
		break;
	case RUNE_PLAGUE:
		ent->client->ps.powerups[PW_INFECTED]=level.time+10000000;
		ent->runevar = RUNE_PLAGUE_TRAP_NUMBER;
		ent->runevector[0] = 0;
		ent->runevector[1] = level.time;
		Rune_Plague_Use(ent);
		break;
*/
	default:
		break;
	}
}


void Rune_Delete(gentity_t *ent, qboolean silent)
{
	switch (ent->client->ps.powerups[RUNE_POWERUP_SLOT])
	{
	case RUNE_HASTE:
		ent->client->ps.powerups[PW_HASTE]=0;
		break;
	case RUNE_VENGEANCE:
		ent->client->ps.powerups[PW_VENGEANCE]=0;
		break;
	case RUNE_SHIELD:
		ent->client->ps.powerups[PW_SHIELD]=level.time-1;
		break;
	case RUNE_SPRINT:
		ent->client->ps.powerups[PW_HASTE]=level.time-1;
		break;
	case RUNE_PHASE:
		ent->client->ps.powerups[PW_PHASE]=level.time-1;
		break;
		/*
	case RUNE_CLOAKING:
		ent->client->ps.powerups[PW_CLOAK]=level.time-1;
		break;

	case RUNE_QUAD_DAMAGE:
		ent->client->ps.powerups[PW_QUAD]=level.time-1;
		break;
	case RUNE_PHASE:
		ent->client->ps.powerups[PW_PHASE]=level.time-1;
		break;
	case RUNE_ILLUSION:
		ent->client->ps.powerups[PW_ILLUSION]=level.time-1;
		break;
	case RUNE_FIRE:
		ent->client->ps.powerups[PW_BURNING]=level.time-1;
		break;
	case RUNE_SPRINT:
		ent->client->ps.powerups[PW_HASTE]=level.time-1;
		break;
	case RUNE_REFLECTION:
		ent->client->ps.powerups[PW_REFLECTION]=level.time-1;
		break;
	case RUNE_PLAGUE:
		ent->client->ps.powerups[PW_INFECTED]=level.time-1;
		break;
		*/
	default:
		break;
	}

	ent->client->ps.powerups[RUNE_POWERUP_SLOT]=RUNE_NONE;
	ent->client->ps.stats[STAT_RUNE_COUNTER]=0;
	VectorSet(ent->runevector,0,0,0);
	VectorSet(ent->runevector2,0,0,0);
	ent->runetime = level.time;
	ent->runevar = 0;
	ent->burntime = 0;
	ent->infectedtime = 0;
	ent->runeid = 0;

	if (!silent)
		trap_SendServerCommand( ent->s.clientNum, va("rune_dropinform 0"));
}



// rune_dropinform vales
// 0	Rune was removed
// -1	No Rune
// -2	Rune Removal Cancelled
// -3	Can't remove runes
// All other values indicate the length of time before the rune can be removed
void Cmd_Rune_Drop( gentity_t *ent, qboolean immediate ) 
{

	// immediate is used for rune give commands and any time where you have to force a rune
	//		removal without regard for how long they've had it
	if (immediate)
	{
		//if (ent->client->ps.powerups[RUNE_POWERUP_SLOT]==RUNE_PACK_RAT)
		//	Rune_Pack_Rat_Drop(ent,qfalse,qtrue);
		Rune_Delete(ent,qtrue);
		return;
	}
/*
	if (ent->client->ps.powerups[RUNE_POWERUP_SLOT]==RUNE_PACK_RAT && ent->runevar >0)
	{
		Rune_Pack_Rat_Drop(ent,qtrue,qtrue);
		Rune_Delete(ent,qfalse);
		return;
	}
*/
	if (ent->client->ps.powerups[RUNE_POWERUP_SLOT] == RUNE_NONE)
		trap_SendServerCommand( ent->s.clientNum, va("rune_dropinform -1"));
	else if (g_RuneDropTime.integer==-1)
		trap_SendServerCommand( ent->s.clientNum, va("rune_dropinform -3"));
	else if (ent->runeDropDelay < 0)
	{
		trap_SendServerCommand( ent->s.clientNum, va("rune_dropinform -2"));
		ent->runeDropDelay = 0 - ent->runeDropDelay;
	}
	else if (ent->runeDropDelay > level.time)
	{
		trap_SendServerCommand( ent->s.clientNum, va("rune_dropinform %i",(ent->runeDropDelay - level.time)/1000));
		ent->runeDropDelay = 0 - ent->runeDropDelay;
	}
	else
		Rune_Delete(ent,qfalse);
}

/*
===============
Touch_Rune
===============
*/
void Touch_Rune (gentity_t *ent, gentity_t *other, trace_t *trace) 
{
	if (!other->client)
		return;
	if (other->health < 1)
		return;		// dead people can't pickup

	/*
	if (other->client->ps.powerups[RUNE_POWERUP_SLOT] == RUNE_PACK_RAT)
	{
		if (ent->enemy == other)
		{
			if (ent->runeDropDelay < level.time)
			{
				ent->runeDropDelay = level.time + 3000;
				trap_SendServerCommand(other->s.clientNum,"print \"You killed the owner of this rune\n\"");
			}
		}
		else
			Rune_Pack_Rat_Touch(other,ent);
		return;
	}
	*/

	if (other->client->ps.powerups[RUNE_POWERUP_SLOT]!=RUNE_NONE)
		return;

	if (other == ent->parent)
	{
		// tell them they can't pick up their own rune
		// but only do it once every 3 seconds so that they don't get that same message about 1000 times a sec
		if (ent->runeDropDelay < level.time)
		{
			ent->runeDropDelay = level.time + 3000;
			trap_SendServerCommand(other->s.clientNum,"rune_dropinform -4");
		}
		return;
	}

	// its a bot, make sure it can use this Rune
	if (other->r.svFlags & SVF_BOT)
	{
		while (!canBotUse(ent->runevar))
		{
			ent->runevar = floor(random()*RUNE_TOTAL)+1;
		}
	}

	G_LogPrintf( "Item: %i Rune %i\n", other->s.number, ent->runevar );

	Rune_Initialize(other,ent->runevar);
	runeTotal--;

	G_FreeEntity( ent );
}


void setSpawnerTime(int theTime)
{
	checkForSpawnerTime = theTime;
}

int getSpawnerTime()
{
	return checkForSpawnerTime;
}

void CheckFreeRune(gentity_t *ent)
{
	if (ent->classname)
	{
		if (!Q_stricmp (ent->classname, "item_rune"))
		{
			runeTotal--;
		}

		if (!Q_stricmp (ent->classname, "rune_spawner"))
		{
			G_Printf("WARNING:  Rune Spawner was just freed\n");
			G_LogPrintf("WARNING:  Rune Spawner was just freed\n");
		}
	}

}


void G_Rune_Think( gentity_t *ent ) 
{
	if (ent->runetime < level.time)
	{
		runeTotal--;

		G_FreeEntity(ent);
	}
	else
	{

	}

	ent->nextthink = level.time + 1000;
}



gentity_t *Rune_Spawn(vec3_t origin, int runetype, gentity_t *spawnee, qboolean randomDir)
{
	vec3_t	velocity,forward,right,up,muzzle;
	gitem_t		*item;
	float ran1,ran2,ran3;
	gentity_t	*dropped;

	if (g_RuneModels.integer == 2)
	{
		item = BG_FindItem (va("Rune%i",(int)(random()*100)%6+1));
	}
	else
	{
		if (g_RuneModels.integer)
		{
			item = BG_FindItem (va("Rune%i",runetype%6+1));
		}
		else
		{
			item = BG_FindItem("Rune1");
		}
	}


	if (randomDir)
	{
		srand(level.time);
		ran1 = floor(random()*300);
		ran2 = floor(random()*360)+((int)(random()*10)%2*-360);
		ran3 = floor(random()*360)+((int)(random()*10)%2*-360);

		//if ((int)(random()*10)%2==0)
		//	ran1*=-1;
		if ((int)(random()*10)%2==0)
			ran2*=-1;
		if ((int)(random()*10)%2==0)
			ran3*=-1;

		VectorSet(velocity,ran3,ran2,ran1);
	}
	else
	{
		AngleVectors (spawnee->client->ps.viewangles, forward, right, up);
		CalcMuzzlePoint ( spawnee, forward, right, up, muzzle );
		VectorMA(muzzle,100,forward,origin);
		VectorScale(forward,200,forward);
		VectorCopy( forward, velocity );
	}


	// get em off the ground a little so they don't get stuck in things
	//FIXME: this needs to be replaced by a check to see if the rune spawned in something solid
	//sorigin[2]+=25;
	


	dropped = G_Spawn();

	dropped->s.eType = ET_ITEM;
	dropped->s.modelindex = item - bg_itemlist;	// store item number in modelindex
	dropped->s.modelindex2 = 1; // This is non-zero is it's a dropped item

	dropped->classname = item->classname;
	dropped->item = item;
	VectorSet (dropped->r.mins, -ITEM_RADIUS, -ITEM_RADIUS, -ITEM_RADIUS);
	VectorSet (dropped->r.maxs, ITEM_RADIUS, ITEM_RADIUS, ITEM_RADIUS);
	dropped->r.contents = CONTENTS_TRIGGER;

	dropped->touch = Touch_Rune;

	G_SetOrigin( dropped, origin );
	dropped->s.pos.trType = TR_GRAVITY;
	dropped->s.pos.trTime = level.time;
	VectorCopy( velocity, dropped->s.pos.trDelta );

	dropped->s.eFlags |= EF_BOUNCE_HALF;


	dropped->think = G_Rune_Think;
	dropped->nextthink = level.time;
	dropped->runetime = level.time  + 20000 + random()*10000;
	dropped->runevar = runetype;
	dropped->parent = spawnee;
	dropped->runeDropDelay = level.time;


	dropped->flags = FL_DROPPED_ITEM;

	trap_LinkEntity (dropped);

	runeTotal++;

	return dropped;
}


void Cmd_Rune_Use( gentity_t *ent, int clientNum ) 
{	
	if (ent->client->ps.powerups[RUNE_POWERUP_SLOT]==RUNE_NONE)
		return;

	switch(ent->client->ps.powerups[RUNE_POWERUP_SLOT])
	{
	case RUNE_ENVIRO:
		Rune_Enviro_Use(ent);
		break;
	case RUNE_ACTION_MOVIE:
		Rune_ActionMovie_Use(ent);
		break;
	case RUNE_SHIELD:
		Rune_Shield_Use(ent);
		break;
	case RUNE_SPRINT:
		Rune_Sprint_Use(ent);
		break;
	case RUNE_TELEPORT:
		Rune_Teleport_Use(ent);
		break;
	case RUNE_SWITCH:
		Rune_Switch_Use(ent);
		break;
	case RUNE_NEGATION:
		Rune_Negation_Use(ent);
		break;
	case RUNE_PHASE:
		Rune_Phase_Use(ent);
		break;
	case RUNE_ATHLETICS:
		Rune_Athletics_Use(ent);
		break;
	case RUNE_FLASH:
		Rune_Flash_Use(ent);
		break;
	case RUNE_DISARMAMENT:
		Rune_Disarm_Use(ent);
		break;
		/*
	case RUNE_EMP:
		Rune_EMP_Use(ent);
		break;
		
	case RUNE_LIGHTNING:
		Rune_Lightning_Use(ent);
		break;
	case RUNE_RECALL:
		Rune_Recall_Use(ent);
		break;
	case RUNE_DUAL_RECALL:
		Rune_Dual_Recall_Use(ent);
		break;

	case RUNE_GRAVITY:
		Rune_Gravity_Use(ent);
		break;
	case RUNE_ICE_TRAPS:
		Rune_Ice_Trap_Use(ent);
		break;
	case RUNE_DEATH_SPOTS:
		Rune_Death_Spot_Use(ent);
		break;
	case RUNE_SHIELD:
		Rune_Shield_Use(ent);
		break;
	case RUNE_BLINK:
		Rune_Blink_Use(ent);
		break;
	case RUNE_RADIOACTIVITY:
		Rune_Radioactivity_Use(ent);
		break;
	case RUNE_QUAD_DAMAGE:
		Rune_Quad_Damage_Use(ent);
		break;
	case RUNE_PHASE:
		Rune_Phase_Use(ent);
		break;
	case RUNE_TELEPORT:
		Rune_Teleport_Use(ent);
		break;
	case RUNE_SWITCH:
		Rune_Switch_Use(ent);
		break;
	case RUNE_NEGATION:
		Rune_Negation_Use(ent);
		break;
	case RUNE_ATHLETICS:
		Rune_Athletics_Use(ent);
		break;
	case RUNE_DIVINE_WIND:
		Rune_Divine_Wind_Arm(ent);
		break;
	case RUNE_REPULSION:
		Rune_Repulsion_Use(ent) ;
		break;
	case RUNE_HOLOGRAM:
		Rune_Hologram_Use(ent);
		break;
	case RUNE_WEIRDNESS:
		Rune_Weird_Use(ent);
		break;
	case RUNE_FIRE:
		Rune_Fire_Use(ent);
		break;
	case RUNE_SPRINT:
		Rune_Sprint_Use(ent);
		break;
	case RUNE_EXCLUSION:
		Rune_Exclusion_Use(ent);
		break;
	case RUNE_TRANSFERENCE:
		Rune_Transference_Use(ent);
		break;


	case RUNE_PLAGUE:
		Rune_Plague_Use(ent);
		break;
		*/
	default:
		break;
	}
}


void Cmd_Rune_Give( gentity_t *ent, int clientNum ) 
{
	int runeID;

	char	buffer[MAX_TOKEN_CHARS];
	if ( trap_Argc() != 2 ) 
	{
		trap_SendServerCommand( clientNum, va("print \"usage: /rune give RUNE_SHORT_NAME\n\""));
		return;
	}

/*
	if (!g_AllowRuneCheats.integer)
	{
		trap_SendServerCommand( clientNum, va("print \"Rune cheats are not enabled\n\""));
		return;
	}
*/
	trap_Argv( 1, buffer, sizeof( buffer ) );
	runeID = getRuneIDFromName(buffer);

	if (!runeID)
	{
		trap_SendServerCommand( clientNum, va("print \"Invalid rune name: %s\n\"",buffer));
		return;
	}

	if (isBanned(runeID))
	{
		trap_SendServerCommand( clientNum, va("print \"That rune is banned on this level\n\""));
		return;
	}



	Cmd_Rune_Drop(ent, qtrue );
	Rune_Initialize(ent, runeID);
	//Cmd_Rune_Tell(ent);

	G_LogPrintf( "%s gave himself a rune: %s\n", ent->client->pers.netname,buffer );
}

void Cmd_Rune_Throw( gentity_t *ent, qboolean immediate ) 
{
	gentity_t *runedrop;
/*
	if (ent->client->ps.powerups[RUNE_POWERUP_SLOT]==RUNE_PACK_RAT && ent->runevar>0)
	{
		Rune_Pack_Rat_Drop(ent,qtrue,qfalse);
		return;
	}
*/
	runedrop = Rune_Spawn(ent->r.currentOrigin, ent->client->ps.powerups[RUNE_POWERUP_SLOT],ent,qfalse);
	runedrop->enemy = ent->enemy;

	Rune_Delete(ent,qfalse);
}

void Rune_SpawnAll(int numspawn)
{
	int counter, runetype;
	gentity_t *temp;

	counter = 0;
	while (counter < numspawn)
	{
		temp = SelectRuneSpawnPoint (counter);
		//temp = SelectRandomDeathmatchSpawnPoint ();
		
		do
		{
			runetype = ((int)(random()*RUNE_TOTAL))%RUNE_TOTAL;
			runetype += 1;
		} while (!spawnable(runetype));

		if (runeTotal < g_RuneNumber.integer)
			Rune_Spawn(temp->r.currentOrigin, runetype, NULL, qtrue);

		counter = counter + 1;
	}

}

void Rune_Spawner_Think(gentity_t *ent)
{
	int count=0;
	gentity_t *runespawn=&g_entities[MAX_CLIENTS];

	if (g_RuneNumber.integer-runeTotal>=1)
	{
		Rune_SpawnAll(1);
	}

	ent->nextthink = level.time + 3000; // was 5000
}


void Rune_Spawner(void)
{
	gentity_t	*it_ent,*temp;
	gitem_t *quadItem,*runeItem1,*runeItem2,*runeItem3,*runeItem4,*runeItem5,*runeItem6,*ice;

	//ice = BG_FindItem("Ice Trap");
	//RegisterItem(ice);

	quadItem = BG_FindItem("Quad Damage");
	RegisterItem(quadItem);

	// Register the rune models
	runeItem1 = BG_FindItem("Rune1");
	RegisterItem(runeItem1);
	runeItem2 = BG_FindItem("Rune2");
	RegisterItem(runeItem2);
	runeItem3 = BG_FindItem("Rune3");
	RegisterItem(runeItem3);
	runeItem4 = BG_FindItem("Rune4");
	RegisterItem(runeItem4);
	runeItem5 = BG_FindItem("Rune5");
	RegisterItem(runeItem5);
	runeItem6 = BG_FindItem("Rune6");
	RegisterItem(runeItem6);

	it_ent = G_Spawn();

	it_ent->classname = "rune_spawner";

	G_LogPrintf("Creating Rune Spawner\n");

	VectorSet( it_ent->r.mins, -ITEM_RADIUS, -ITEM_RADIUS, -ITEM_RADIUS );
	VectorSet( it_ent->r.maxs, ITEM_RADIUS, ITEM_RADIUS, ITEM_RADIUS );

	it_ent->r.contents = CONTENTS_TRIGGER;
	it_ent->r.ownerNum = ENTITYNUM_NONE;

	it_ent->s.eType = ET_INVISIBLE;
	it_ent->s.weapon = WP_GAUNTLET;
	it_ent->s.pos.trType = TR_STATIONARY;
	it_ent->s.pos.trTime = level.time-1;
	VectorSet( it_ent->s.pos.trDelta,0,0,0 );

	it_ent->think = Rune_Spawner_Think;
	it_ent->nextthink = level.time + 100;

	it_ent->neverFree = qtrue;				// will never be freed, but can be unlinked

	runeTotal=0;
	bigCountTime = level.time+1000;
	setSpawnerTime(level.time+60000);

	temp = SelectRandomDeathmatchSpawnPoint();
	VectorCopy (temp->r.currentOrigin, it_ent->r.currentOrigin);
	VectorCopy (temp->r.currentOrigin, it_ent->s.pos.trBase);
	VectorCopy (temp->r.currentOrigin, it_ent->s.origin);

	// check for gametype
	//  if its not a team game, disable the teamplay runes
	if (g_gametype.integer < GT_TEAM)
		MarkTeamRunes(qfalse);
	else
		MarkTeamRunes(qtrue);

	trap_LinkEntity (it_ent);
}

void Rune_CheckSpawner()
{
	gentity_t *theSpawner;
	if (!(G_Find (NULL, FOFS(classname),"rune_spawner")))
	{
		Rune_Spawner();
		G_LogPrintf("Rune Spawner gone, re-spawning\n");
	}
	else
	{
		theSpawner=G_Find (NULL, FOFS(classname),"rune_spawner");
		trap_LinkEntity(theSpawner);
	}
}



void Player_Rune_Think(gentity_t *ent)
{
	vec3_t	boltangles,boltstart,boltend;
	qboolean flag;
	int zaps,t;
	gentity_t *tent;

	// RQ3:  force the runes to refresh their SFX needs
	ent->client->ps.generic1 = 0;

	if (ent->client->ps.powerups[RUNE_POWERUP_SLOT]==RUNE_NONE)
		return;

	//RUNE: delete rune if requested
	if (ent->runeDropDelay < 0 && level.time >= (0 - ent->runeDropDelay))
	{
		Rune_Delete(ent,qfalse);
		return;
	}

	switch (ent->client->ps.powerups[RUNE_POWERUP_SLOT])
	{
	case RUNE_STRENGTH:
		// RQ3:  renew your sound
		ent->client->ps.generic1 |= (1 << SFX_SOUND_QUAD);
		break;
	case RUNE_BERSERK:
		// RQ3:  renew your shell and sound
		ent->client->ps.generic1 |= (1 << SFX_SHELL_BERSERK);
		ent->client->ps.generic1 |= (1 << SFX_SOUND_QUAD);
		break;
	case RUNE_RESISTANCE:
		if (ent->runevar-level.time>0)
			ent->client->ps.generic1 |= (1 << SFX_SHELL_SHIELD);
		break;
	case RUNE_HASTE:
		ent->client->ps.powerups[PW_HASTE]=level.time+1000000;
		break;
	case RUNE_REGENERATION:
		if(ent->runetime > level.time)
			return;

		flag = qfalse;

		if ( ent->health < MaxHealth(&ent->client->ps,qfalse)) 
		{
			flag=qtrue;
			ent->health += RUNE_REGEN_HEALTH_INCREASE;
			if ( ent->health > MaxHealth(&ent->client->ps,qfalse) ) 
				ent->health = MaxHealth(&ent->client->ps,qfalse);
		} 

		// armor
		if ( ent->client->ps.stats[STAT_ARMOR] < MaxArmor(&ent->client->ps,qfalse) && ent->client->ps.stats[STAT_ARMOR] > 0 ) 
		{
			flag=qtrue;
			ent->client->ps.stats[STAT_ARMOR]+=RUNE_REGEN_ARMOR_INCREASE;
			if ( ent->client->ps.stats[STAT_ARMOR] > MaxArmor(&ent->client->ps,qfalse) ) 
				ent->client->ps.stats[STAT_ARMOR] = MaxArmor(&ent->client->ps,qfalse);	
		}

		if (flag)
		{
			G_AddEvent( ent, EV_POWERUP_REGEN, 0 );
		}

		ent->runetime = level.time+1000;
		break;
	case RUNE_ACTION_MOVIE:
		if(ent->runetime > level.time)
			return;

		if (ent->runevar == 1)
			ent->runetime = Rune_ActionMovie_Think(ent, qfalse);
		else
			ent->runetime = Rune_ActionMovie_Think(ent, qtrue);
		break;
	case RUNE_FLIGHT:
		Rune_Flight_Think(ent);
		break;
	case RUNE_SHIELD:
		if (ent->runevar==1 && ent->runetime<level.time)
			Rune_Shield_Use(ent);
		if (ent->runetime-level.time >0)
			ent->client->ps.stats[STAT_RUNE_COUNTER]=ent->runetime-level.time;
		else
			ent->client->ps.stats[STAT_RUNE_COUNTER]=0;
		break;
	case RUNE_SPRINT:
		if (ent->runevar==1 && ent->runetime<level.time)
			Rune_Sprint_Use(ent);
		if (ent->runetime-level.time >0)
			ent->client->ps.stats[STAT_RUNE_COUNTER]=ent->runetime-level.time;
		else
			ent->client->ps.stats[STAT_RUNE_COUNTER]=0;
		break;
	case RUNE_REFLECTION:
		ent->client->ps.generic1 |= (1 << SFX_SHELL_REFLECTION);
		break;
	case RUNE_ATHLETICS:
		//Rune_Athletics_Think(ent);
		break;
	case RUNE_FLASH:
		if (ent->runevar==1 && ent->runetime<level.time)
			Rune_Flash_Use(ent);
		if (ent->runetime-level.time >0)
			ent->client->ps.stats[STAT_RUNE_COUNTER]=ent->runetime-level.time;
		else
			ent->client->ps.stats[STAT_RUNE_COUNTER]=0;
		break;
	case RUNE_DISARMAMENT:
		if (ent->runevar==1 && ent->runetime<level.time)
			Rune_Disarm_Use(ent);
		if (ent->runetime-level.time >0)
			ent->client->ps.stats[STAT_RUNE_COUNTER]=ent->runetime-level.time;
		else
			ent->client->ps.stats[STAT_RUNE_COUNTER]=0;
		break;

/*
	case RUNE_CLOAKING:
		if (ent->runevar < 1 && ent->runetime < level.time)
		{
			trap_SendServerCommand(ent->s.clientNum, "playsound sound/runes/cloak.wav");
			ent->client->ps.powerups[PW_CLOAK]=level.time+10000000;
			trap_SendServerCommand( ent->s.clientNum, va("print \"Cloaked\n\""));
			ent->runevar = 1;
		}

		if (ent->runevar > 0 && ent->runetime > level.time)
		{
			trap_SendServerCommand(ent->s.clientNum, "playsound sound/runes/decloak.wav");
			ent->client->ps.powerups[PW_CLOAK]=level.time;
			trap_SendServerCommand( ent->s.clientNum, va("print \"Uncloaked\n\""));
			ent->runevar = 0;
		}
		break;

	case RUNE_LIGHTNING:
		if(ent->runetime > level.time || ent->runevar == 1)
			return;

		if (ent->waterlevel) 
		{
		   zaps = ent->client->ps.ammo[WP_LIGHTNING];      // determines size/power of discharge
		   if (zaps)
		   {
			   zaps++;         // pmove does an ammo[gun]--, so we must compensate

			   tent = G_TempEntity (ent->r.currentOrigin, EV_LIGHTNING_DISCHARGE);
			   tent->s.eventParm = zaps;                               // duration / size of explosion graphic

			   ent->client->ps.ammo[WP_LIGHTNING] = 0;         // drain ent's lightning count
			   if (G_WaterRadiusDamage (ent->r.currentOrigin, ent, 8 * zaps,(8 * zaps) + 16, NULL, MOD_RUNE_LIGHTNING_DISCHARGE))
					   g_entities[ent->r.ownerNum].client->ps.persistant[PERS_ACCURACY_HITS]++;
		   }
		}


		// initialize boltstart and boltend
		VectorCopy(ent->r.currentOrigin,boltstart);
		VectorCopy(ent->r.currentOrigin,boltend);

		// randomly determine the angle that the bolt is going.  Normalize it.
		//   then scale it and combine it with currentOrigin to get the other end of the bolt
		boltangles[0] = crandom()*360;
		boltangles[1] = crandom()*360;
		boltangles[2] = crandom()*360;
		VectorNormalize(boltangles);

		boltend[0]=ent->r.currentOrigin[0]+(boltangles[0]*50);
		boltend[1]=ent->r.currentOrigin[1]+(boltangles[1]*50);
		boltend[2]=ent->r.currentOrigin[2]+20+(boltangles[2]*50);
		
		// bolt start is on the other side of the player from end, thus it is negative (relatively)
		boltstart[0]=ent->r.currentOrigin[0]+(boltangles[0]*-50);
		boltstart[1]=ent->r.currentOrigin[1]+(boltangles[1]*-50);
		boltstart[2]=ent->r.currentOrigin[2]+20+(boltangles[2]*-50);

		tent = G_TempEntity( boltend, EV_LIGHTNINGBOLT );
		VectorCopy( boltstart, tent->s.origin2 );
		tent->s.frame = 80; // length of time bolt is visible

		tent->s.eventParm = 255; // don't make the explosion at the end

		// remember who controls the bolt
		tent->s.clientNum = ent->s.clientNum;
		ent->runetime = level.time+300;
		break;
	case RUNE_SHIELD:
		if (ent->runevar==1 && ent->runetime<level.time)
			Rune_Shield_Use(ent);
		if (ent->runetime-level.time >0)
			ent->client->ps.stats[STAT_RUNE_COUNTER]=ent->runetime-level.time;
		else
			ent->client->ps.stats[STAT_RUNE_COUNTER]=0;
		break;
	case RUNE_ICE_TRAPS:
		ent->client->ps.stats[STAT_RUNE_COUNTER]=ent->runevar;
		break;
	case RUNE_DEATH_SPOTS:
		ent->client->ps.stats[STAT_RUNE_COUNTER]=ent->runevar;
		break;
	case RUNE_BLINK:
		if (ent->runevar<level.time)
		{
			ent->runevar = level.time+1000;
			tent = G_TempEntity (ent->r.currentOrigin, EV_BLINK_BUBBLE);
		}
		break;
	case RUNE_RADIOACTIVITY:
		ent->client->ps.stats[STAT_RUNE_COUNTER]=ent->runevar;
		break;
	case RUNE_QUAD_DAMAGE:
		if (ent->runevar==1 && ent->runetime<level.time)
			Rune_Quad_Damage_Use(ent);
		if (ent->runetime-level.time >0)
			ent->client->ps.stats[STAT_RUNE_COUNTER]=ent->runetime-level.time;
		else
			ent->client->ps.stats[STAT_RUNE_COUNTER]=0;
		break;
	case RUNE_PHOENIX:
		ent->client->ps.stats[STAT_RUNE_COUNTER]=ent->runevar;
		break;
	case RUNE_DIVINE_WIND:
		Rune_Divine_Wind_Think(ent);
		break;
	case RUNE_JUMPING:
		Rune_Jumping_Think(ent);
		break;

	case RUNE_REPULSION:
		if(ent->runetime > level.time)
			return;

		ent->runetime = level.time+RUNE_REPULSION_TIMING;
		Rune_Repulsion_Think(ent);
		break;
	case RUNE_HOLOGRAM:
		ent->client->ps.stats[STAT_RUNE_COUNTER]=ent->runevar;
		break;
	case RUNE_WEIRDNESS:
		Rune_Weird_SpawnThink(ent);
		break;
	case RUNE_FIRE:
		ent->client->ps.stats[STAT_RUNE_COUNTER]=ent->runevar;
		break;
	case RUNE_PACK_RAT:
		t = (int)floor(ent->runevar/(float)RUNE_PACK_RAT_STEP)+1;
		if (t>RUNE_PACK_RAT_MAX)
			t=RUNE_PACK_RAT_MAX;

		ent->client->ps.stats[STAT_RUNE_COUNTER]=t;
		break;
	case RUNE_SPRINT:
		if (ent->runevar==1 && ent->runetime<level.time)
			Rune_Sprint_Use(ent);
		if (ent->runetime-level.time >0)
			ent->client->ps.stats[STAT_RUNE_COUNTER]=ent->runetime-level.time;
		else
			ent->client->ps.stats[STAT_RUNE_COUNTER]=0;
		break;
	case RUNE_EXCLUSION:
		if (ent->runevar==1 && ent->runetime<level.time)
			Rune_Exclusion_Use(ent);
		if (ent->runetime-level.time >0)
			ent->client->ps.stats[STAT_RUNE_COUNTER]=ent->runetime-level.time;
		else
			ent->client->ps.stats[STAT_RUNE_COUNTER]=0;
		break;

	case RUNE_MEDIC:
		if(ent->runetime > level.time)
			return;

		Rune_Medic_Think(ent);
		ent->runetime = level.time+1000;
		break;
	case RUNE_PLAGUE:
		ent->client->ps.stats[STAT_RUNE_COUNTER]=ent->runevar;
		break;
		*/
	default:
		break;
	}
}


void ApplyShellToEnt(gentity_t *ent, int runeType)
{
	if (runeType == RUNE_STRENGTH)
	{
		ent->s.generic1 |= (1 << SFX_SHELL_QUAD);
	}
	else if (runeType == RUNE_BERSERK)
	{
		ent->s.generic1 |= (1 << SFX_SHELL_BERSERK);
	}
}

void HealPlayer(gentity_t *targ,int amount,qboolean includeOverMax)
{
	int maxamount;
	targ->health+=amount;

	maxamount = MaxHealth(&targ->client->ps,includeOverMax);
	if (targ->health > maxamount)
		targ->health = maxamount;

}

void Svcmd_BanRune( qboolean ban ) 
{
	char		s[MAX_TOKEN_CHARS];
	trap_Argv( 1, s, sizeof( s ) );

	if (ban)
		banRune(getRuneIDFromName(s));
	else
		unbanRune(getRuneIDFromName(s));
}

void Svcmd_AddWeapon( void ) 
{
	char		s[MAX_TOKEN_CHARS];
	char		t[MAX_TOKEN_CHARS];
	int			weaponNum=1,ammoCount=0;

	if ( trap_Argc() != 3 ) 
	{
		G_Printf("usage: /addweapon WEAPON_SHORT_NAME ammo_amount\n\"");
		return;
	}

	trap_Argv( 1, s, sizeof( s ) );
	trap_Argv( 2, t, sizeof( t ) );
	ammoCount = atoi(t);

	weaponNum = getWeaponIDFromName(s);

	if (weaponNum == WP_NONE)
	{
		return;
	}
	else
	{
		addWeapon(weaponNum,ammoCount);
	}
}

void Svcmd_ReplaceWeapon( void ) 
{
	char		s[MAX_TOKEN_CHARS];
	char		t[MAX_TOKEN_CHARS];
	char		v[MAX_TOKEN_CHARS];
	int			weapon1Num=1,weapon2Num=1,swapNum=0,counter;
	gentity_t	*ent;
	gitem_t		*item;
	gentity_t	*te;

	if ( trap_Argc() != 4 ) 
	{
		G_Printf("usage: /replaceweapon WEAPON1 WEAPON2 count\n\"");
		return;
	}

	trap_Argv( 1, s, sizeof( s ) );
	trap_Argv( 2, t, sizeof( t ) );
	trap_Argv( 3, v, sizeof( v ) );

	weapon1Num = getWeaponIDFromName(s);
	weapon2Num = getWeaponIDFromName(t);
	swapNum = atoi(v);

	if (weapon1Num == WP_NONE || weapon2Num == WP_NONE)
	{
		return;
	}
	else
	{
		counter = swapNum;
		while ((ent = G_Find (NULL, FOFS(classname),(const char *)getClassnameFromWeaponNum(weapon1Num))) && counter>0)
		{
			// find the item struc for the new weapon and spawn the new weapon in place of the old
			for ( item=bg_itemlist+1 ; item->classname ; item++ ) {
				if ( !Q_stricmp(item->classname, (char *)getClassnameFromWeaponNum(weapon2Num)) ) 
				{
					if( item->giType == IT_TEAM && g_gametype.integer != GT_CTF ) {
						break;
					}
					G_SpawnItem( ent, item );
					strcpy(ent->classname,(char *)getClassnameFromWeaponNum(weapon2Num));

					te = G_TempEntity( ent->s.pos.trBase, EV_REGISTER_ITEM );
					te->s.eventParm = item - bg_itemlist;
					te->r.svFlags |= SVF_BROADCAST;
					counter--;
					break;
				}
			}
		}

		if (!ent)
		{
			// if we used up all instances of the weapon, then make sure to get all the ammo too
			swapNum = 1000;
		}

		while ((ent = G_Find (NULL, FOFS(classname),(const char *)getAmmoClassnameFromWeaponNum(weapon1Num))) && swapNum>0)
		{
			// find the item struc for the new weapon and spawn the new weapon in place of the old
			for ( item=bg_itemlist+1 ; item->classname ; item++ ) {
				if ( !Q_stricmp(item->classname, (char *)getAmmoClassnameFromWeaponNum(weapon2Num)) ) 
				{
					if( item->giType == IT_TEAM && g_gametype.integer != GT_CTF ) {
						break;
					}
					G_SpawnItem( ent, item );
					strcpy(ent->classname,(char *)getAmmoClassnameFromWeaponNum(weapon2Num));

					te = G_TempEntity( ent->s.pos.trBase, EV_REGISTER_ITEM );
					te->s.eventParm = item - bg_itemlist;
					te->r.svFlags |= SVF_BROADCAST;
					swapNum--;
					break;
				}
			}
		}


	}
}

void Svcmd_RemoveWeapon( void ) 
{
	char		s[MAX_TOKEN_CHARS];
	int			weaponNum=1;

	if ( trap_Argc() != 2 ) 
	{
		G_Printf("usage: /removeweapon WEAPON_SHORT_NAME\n\"");
		return;
	}

	trap_Argv( 1, s, sizeof( s ) );

	weaponNum = getWeaponIDFromName(s);

	removeWeapon(weaponNum);
}

void Svcmd_BanWeapon( void ) 
{
	char		s[MAX_TOKEN_CHARS];
	int			weaponNum=1;

	if ( trap_Argc() != 2 ) 
	{
		G_Printf("usage: /banweapon WEAPON_SHORT_NAME\n\"");
		return;
	}

	trap_Argv( 1, s, sizeof( s ) );

	weaponNum = getWeaponIDFromName(s);

	banWeapon(weaponNum);

}


void SwapPlayerPositions(gentity_t *player1, gentity_t *player2)
{
	int player1Flags=0,player2Flags=0;
	vec3_t end;

	// switch positions with the target
	//	flip both player's teleport bits so that they don't try to interpolate this sudden movement
	player1Flags = player1->client->ps.eFlags & EF_TELEPORT_BIT;
	player1Flags ^= EF_TELEPORT_BIT;

	player2Flags = player2->client->ps.eFlags & EF_TELEPORT_BIT;
	player2Flags ^= EF_TELEPORT_BIT;

	player1->client->ps.eFlags = player1Flags;
	player2->client->ps.eFlags = player2Flags;

	VectorCopy(player1->client->ps.origin,end);
	VectorCopy(player2->client->ps.origin,player1->client->ps.origin);
	VectorCopy(end,player2->client->ps.origin);

	BG_PlayerStateToEntityState( &player1->client->ps, &player1->s, qtrue );
	BG_PlayerStateToEntityState( &player2->client->ps, &player2->s, qtrue );
}


qboolean Can_Affect_Player(gentity_t *ent, gentity_t *other)
{
	if ( ent != other && OnSameTeam (ent, other)  ) 
	{
		if ( !g_friendlyFire.integer ) 
		{
				return qfalse;
		}
	}

	return qtrue;
}

/*
============
G_WaterRadiusDamage for Lightning Discharge
============
*/
qboolean G_WaterRadiusDamage (vec3_t origin, gentity_t *attacker, float damage, float radius, gentity_t *ignore, int mod)
{
       float           points, dist;
       gentity_t       *ent;
       int             entityList[MAX_GENTITIES];
       int             numListedEntities;
       vec3_t          mins, maxs;
       vec3_t          v;
       vec3_t          dir;
       int             i, e;
       qboolean        hitClient = qfalse;

		// if discharging is off, damage only the person discharging and then return
		if (!g_Discharge.integer)
		{
			G_Damage (attacker, NULL, attacker, NULL, NULL, (int)damage, DAMAGE_RADIUS, mod);
			return qfalse;
		}

       if (radius < 1) radius = 1;

       for (i = 0 ; i < 3 ; i++)
       {
           mins[i] = origin[i] - radius;
           maxs[i] = origin[i] + radius;
       }

       numListedEntities = trap_EntitiesInBox (mins, maxs, entityList, MAX_GENTITIES);

       for (e = 0 ; e < numListedEntities ; e++)
       {
           ent = &g_entities[entityList[e]];

           if (ent == ignore)                      
			   continue;

           if (!ent->takedamage)           
			   continue;

           // find the distance from the edge of the bounding box
           for (i = 0 ; i < 3 ; i++)
           {
                        if (origin[i] < ent->r.absmin[i]) v[i] = ent->r.absmin[i] - origin[i];
                   else if (origin[i] > ent->r.absmax[i]) v[i] = origin[i] - ent->r.absmax[i];
                   else v[i] = 0;
           }

           dist = VectorLength(v);
           if (dist >= radius)                     
			   continue;

           points = damage * (1.0 - dist / radius);

           if (ent->waterlevel && ent->client->ps.powerups[RUNE_POWERUP_SLOT]!=RUNE_ENVIRO)         // must be in the water, somehow!
           {
				if (LogAccuracyHit (ent, attacker)) hitClient = qtrue;
					VectorSubtract (ent->r.currentOrigin, origin, dir);

				// push the center of mass higher than the origin so players
				// get knocked into the air more
				dir[2] += 24;
				G_Damage (ent, NULL, attacker, dir, origin, (int)points, DAMAGE_RADIUS, mod);
           }
       }

       return hitClient;
}


void player_touch( gentity_t *self, gentity_t *other, trace_t *trace )
{
	int selfRune=0, otherRune=0;
	vec3_t start,end,dir;
	gentity_t *tent;

	if (!Can_Affect_Player(self, other))
		return;
/*
	if (!Q_stricmp(self->classname,"weirdness_bubble"))
	{
		Rune_Weird_Touch(self,other,trace);
		return;
	}

	if (!Q_stricmp(other->classname,"weirdness_bubble"))
	{
		Rune_Weird_Touch(other,self,trace);
		return;
	}
*/

	if ((!other->client)||(!self->client))
		return;

	if ((!other->takedamage)||(!self->takedamage))
		return;

	selfRune = self->client->ps.powerups[RUNE_POWERUP_SLOT];
	otherRune = other->client->ps.powerups[RUNE_POWERUP_SLOT];

	if (otherRune==RUNE_IMPACT)
	{
		if (other->runetime>level.time)
			return;

		other->runetime = level.time + RUNE_IMPACT_RECHARGE;

		// put target position in start
		VectorCopy(self->r.currentOrigin, start);
		
		// put attacker position in end
		VectorCopy(other->r.currentOrigin, end);
		
		// subtract start from end to get directional vector
		VectorSubtract(start, end, dir); 
		dir[2]+=5;

		//VectorNormalize(dir);

		VectorSet(end,0,0,0);
		if (other->client->ps.powerups[PW_QUAD])
			G_Damage(self,NULL,other,dir,end,RUNE_IMPACT_BODYCHECK_DAMAGE*g_quadfactor.value,0,MOD_RUNE_IMPACT);
		else
			G_Damage(self,NULL,other,dir,end,RUNE_IMPACT_BODYCHECK_DAMAGE,0,MOD_RUNE_IMPACT);

		tent = G_TempEntity (self->client->ps.origin, EV_DYNAMIC_SOUND);
		tent->s.eventParm = DYN_SOUND_IMPACT;
	}
	
	if (selfRune==RUNE_IMPACT)
	{
		if (self->runetime>level.time)
			return;

		self->runetime = level.time + RUNE_IMPACT_RECHARGE;

		// put target position in start
		VectorCopy(other->r.currentOrigin, start);
		
		// put attacker position in end
		VectorCopy(self->r.currentOrigin, end);
		
		// subtract start from end to get directional vector
		VectorSubtract(start, end, dir); 
		dir[2]+=5;					// kick em into the air a little

		//VectorNormalize(dir);

		VectorSet(end,0,0,0);

		if (self->client->ps.powerups[PW_QUAD])
			G_Damage(other,NULL,self,dir,end,RUNE_IMPACT_BODYCHECK_DAMAGE*g_quadfactor.value,0,MOD_RUNE_IMPACT);
		else
			G_Damage(other,NULL,self,dir,end,RUNE_IMPACT_BODYCHECK_DAMAGE,0,MOD_RUNE_IMPACT);

		tent = G_TempEntity (other->client->ps.origin, EV_DYNAMIC_SOUND);
		tent->s.eventParm = DYN_SOUND_IMPACT;
	}
/*
	if (otherRune==RUNE_FIRE)
	{
		if (other->runetime>level.time)
			return;

		other->runetime = level.time + RUNE_FIRE_RECHARGE;

		Ignite_Player(self,other,RUNE_FIRE_TOUCH_CHANCE,RUNE_FIRE_TOUCH_DURATION);
	}
	else if (other->client->ps.powerups[PW_BURNING])
	{
		if (other->burnDebounce < level.time)
		{
			other->burnDebounce = level.time + RUNE_FIRE_RECHARGE;
			Ignite_Player(self,other->burnattacker,RUNE_BURNING_TOUCH_CHANCE,RUNE_BURNING_TOUCH_DURATION);
		}
	}
	
	if (selfRune==RUNE_FIRE)
	{
		if (self->runetime>level.time)
			return;

		self->runetime = level.time + RUNE_FIRE_RECHARGE;

		Ignite_Player(other,self,RUNE_FIRE_TOUCH_CHANCE,RUNE_FIRE_TOUCH_DURATION);
	}
	else if (self->client->ps.powerups[PW_BURNING])
	{
		if (self->burnDebounce < level.time)
		{
			self->burnDebounce = level.time + RUNE_FIRE_RECHARGE;
			Ignite_Player(other,self->burnattacker,RUNE_BURNING_TOUCH_CHANCE,RUNE_BURNING_TOUCH_DURATION);
		}
	}


	if (otherRune==RUNE_PLAGUE)
	{
		if (other->runetime>level.time)
			return;

		other->runetime = level.time + RUNE_PLAGUE_RECHARGE;

		Infect_Player(self,other,RUNE_PLAGUE_TOUCH_CHANCE,RUNE_PLAGUE_TOUCH_DURATION);
	}
	else if (other->client->ps.powerups[PW_INFECTED])
	{
		if (other->infectDebounce < level.time)
		{
			other->infectDebounce = level.time + RUNE_PLAGUE_RECHARGE;
			Infect_Player(self,other->infectattacker,RUNE_INFECTED_TOUCH_CHANCE,RUNE_INFECTED_TOUCH_DURATION);
		}
	}
	
	if (selfRune==RUNE_PLAGUE)
	{
		if (self->runetime>level.time)
			return;

		self->runetime = level.time + RUNE_PLAGUE_RECHARGE;

		Infect_Player(other,self,RUNE_PLAGUE_TOUCH_CHANCE,RUNE_PLAGUE_TOUCH_DURATION);
	}
	else if (self->client->ps.powerups[PW_INFECTED])
	{
		if (self->infectDebounce < level.time)
		{
			self->infectDebounce = level.time + RUNE_PLAGUE_RECHARGE;
			Infect_Player(other,self->infectattacker,RUNE_INFECTED_TOUCH_CHANCE,RUNE_INFECTED_TOUCH_DURATION);
		}
	}
	*/
	trap_LinkEntity(self);
}



/*
================
resurrect
================
*/
void resurrect( gentity_t *ent ) 
{
	gentity_t	*tent,*tent2;
	int		index;
	gclient_t	*client;
	int		i;
	int		flags;

	vec3_t	rplayerMins = {-15, -15, -24};
	vec3_t	rplayerMaxs = {15, 15, 32};

	CopyToBodyQue (ent);

	index = ent - g_entities;
	client = ent->client;

	client->pers.teamState.state = TEAM_ACTIVE;
	//client->ps.pm_type == PM_NORMAL;

	// toggle the teleport bit so the client knows to not lerp
	flags = ent->client->ps.eFlags & EF_TELEPORT_BIT;
	flags ^= EF_TELEPORT_BIT;

	// increment the spawncount so the client will detect the respawn
	client->ps.persistant[PERS_SPAWN_COUNT]++;
	client->ps.persistant[PERS_TEAM] = client->sess.sessionTeam;

	client->airOutTime = level.time + 12000;

	// clear entity values
	client->ps.stats[STAT_MAX_HEALTH] = client->pers.maxHealth;
	client->ps.eFlags = flags;

	ent->s.groundEntityNum = ENTITYNUM_NONE;
	ent->client = &level.clients[index];
	ent->takedamage = qtrue;
	ent->inuse = qtrue;
	ent->classname = "player";
	ent->r.contents = CONTENTS_BODY;
	ent->clipmask = MASK_PLAYERSOLID;
	ent->die = player_die;
	ent->touch = player_touch;

	ent->waterlevel = 0;
	ent->watertype = 0;
	ent->flags = 0;
	ent->runetime = level.time;
	trap_SendServerCommand(ent->s.clientNum,"weirdness clear");
	
	VectorCopy (rplayerMins, ent->r.mins);
	VectorCopy (rplayerMaxs, ent->r.maxs);

	client->ps.clientNum = index;

	// health will count down towards max_health
	ent->health = client->ps.stats[STAT_HEALTH] = client->ps.stats[STAT_MAX_HEALTH] * 1.25;

	G_SetOrigin( ent, ent->runevector );
	VectorCopy( ent->runevector, client->ps.origin );

	// the respawned flag will be cleared after the attack and jump keys come up
	client->ps.pm_flags |= PMF_RESPAWNED;

	trap_GetUsercmd( client - level.clients, &ent->client->pers.cmd );
//	SetClientViewAngle( ent, spawn_angles );

	if ( ent->client->sess.sessionTeam == TEAM_SPECTATOR ) {

	} else {
		G_KillBox( ent );
		trap_LinkEntity (ent);

		// force the base weapon up
		client->ps.weapon = WP_MACHINEGUN;
		client->ps.weaponstate = WEAPON_READY;

	}

	// don't allow full run speed for a bit
	client->ps.pm_flags |= PMF_TIME_KNOCKBACK;
	client->ps.pm_time = 100;

	client->respawnTime = level.time;
	client->inactivityTime = level.time + g_inactivity.integer * 1000;
	client->latched_buttons = 0;

	// set default animations
	client->ps.torsoAnim = TORSO_STAND;
	client->ps.legsAnim = LEGS_IDLE;

	if ( level.intermissiontime ) 
	{
		MoveClientToIntermission( ent );
	} 
	else 
	{
		client->ps.weapon = ent->burntime;

		if (client->ps.ammo[client->ps.weapon]<=0)
		{
			// select the highest weapon number available, after any
			// spawn given items have fired
			client->ps.weapon = 1;
			for ( i = WP_NUM_WEAPONS - 1 ; i > 0 ; i-- ) {
				if ( client->ps.stats[STAT_WEAPONS] & ( 1 << i ) && client->ps.ammo[i]>0) 
				{
					client->ps.weapon = i;
					break;
				}
			}
		}
	}

	// run a client frame to drop exactly to the floor,
	// initialize animations and other things
	client->ps.commandTime = level.time - 100;
	ent->client->pers.cmd.serverTime = level.time;
	ClientThink( ent-g_entities );

	// positively link the client, even if the command times are weird
	if ( ent->client->sess.sessionTeam != TEAM_SPECTATOR ) {
		BG_PlayerStateToEntityState( &client->ps, &ent->s, qtrue );
		VectorCopy( ent->client->ps.origin, ent->r.currentOrigin );
		trap_LinkEntity( ent );
	}

	// run the presend to set anything else
	ClientEndFrame( ent );

	// clear entity state values
	BG_PlayerStateToEntityState( &client->ps, &ent->s, qtrue );

	SetClientViewAngle( ent, ent->runevector2 );

	// add a teleportation effect
	tent = G_TempEntity( ent->client->ps.origin, EV_PLAYER_TELEPORT_IN );
	tent->s.clientNum = ent->s.clientNum;

/*	if (ent->client->ps.powerups[RUNE_POWERUP_SLOT]==RUNE_PHOENIX)
	{
		ent->runevar--;
		ent->runetime = level.time;
		client->ps.powerups[PW_QUAD] = level.time+RUNE_PHOENIX_QUAD_DURATION;
		// launch some gibs
		tent2 = G_TempEntity( ent->client->ps.origin, EV_LAUNCH_GIB );
		tent2->s.clientNum = ent->s.clientNum;

		if (ent->runevar<=0)
			Rune_Delete(ent,qfalse);
		else
		{
			//RUNE: re-enable this for "classic" rq interface
			//if (ent->runevar>1)
			//	trap_SendServerCommand( ent->s.clientNum, va("print \"%i resurrections left\n\"",ent->runevar));
			//else
			//	trap_SendServerCommand( ent->s.clientNum, va("print \"%i resurrection left\n\"",ent->runevar));
				
		}
	}
	else if (ent->client->ps.powerups[RUNE_POWERUP_SLOT]==RUNE_VAMPIRE)
	{
		trap_SendServerCommand( ent->s.clientNum, va("print \"Came back to life!!\n\""));
	}
	*/
}
