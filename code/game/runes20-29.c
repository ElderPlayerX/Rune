#include "g_local.h"

////////////////////////////////////////////////
//
//	Runes1-19.c
//		functions for Runes 20-29
//
//		


////////////////////////////////////////////////
//
//		Phase
//

void Rune_Phase_Use(gentity_t *ent)
{
	vec3_t oldmuzzle,muzzle,forward,right,up,end;
	trace_t trace, trace2;

	AngleVectors (ent->client->ps.viewangles, forward, right, up);
	CalcMuzzlePoint ( ent, forward, right, up, muzzle );

	if (ent->runetime<level.time)
	{
		VectorMA (muzzle, 250, forward, end);
		trap_Trace (&trace, muzzle, NULL, NULL, end, ent->s.number, MASK_SHOT );

		// we didn't hit anything, so exit
		if ( trace.fraction == 1)
			return;

		SnapVectorTowards( trace.endpos, muzzle );

        // prepare for firing through the wall
        VectorCopy (muzzle, oldmuzzle);
        VectorCopy (trace.endpos, muzzle);
        VectorMA (muzzle, 96, forward, muzzle);                

        if ( !( trap_PointContents( muzzle, -1 ) & CONTENTS_SOLID ))
        {
			// the point isn't inside a wall, so check to see if we are outside the bounds of the level
			VectorCopy(muzzle,end);
			end[2]=-10000;
			trap_Trace (&trace2, muzzle, NULL, NULL, end, ent->s.number, MASK_SHOT );

			// if we didn't hit anything after that big a trace, we are outside the level
			if (trace2.fraction==1)
				return;

			TeleportPlayer(ent,muzzle,ent->client->ps.viewangles, qtrue, qtrue);
			ent->runetime = level.time + RUNE_PHASE_RECHARGE;
        }


	}
	else
	{
		//trap_SendServerCommand( ent->s.clientNum, va("print \"Phase is recharging\n\""));
	}
}


////////////////////////////////////////////////
//
//		Athletics
//
void Rune_Athletics_Use(gentity_t *ent)
{
	if ((ent->waterlevel!=2)&&(ent->runetime < level.time)&&(ent->client->ps.groundEntityNum != ENTITYNUM_NONE))
	{
		ent->runetime = level.time+RUNE_ATHLETICS_RECHARGE;
		ent->client->ps.velocity[2] = RUNE_ATHLETICS_JUMP_HEIGHT;
		//if(!Rune_Cloak_Sound(ent->client->ps.powerups[RUNE_POWERUP_SLOT],ent->client->ps.stats[STAT_RUNE_COUNTER]))
		//	PM_AddEvent(EV_JUMP);
	}
}



////////////////////////////////////////////////
//
//		Flash
//

void Rune_Flash_Activate(gentity_t *ent)
{
	int				num, targNum[MAX_GENTITIES];
	vec3_t			mins,maxs;
	gentity_t		*target;

	mins[0] = -RUNE_FLASH_RADIUS * 1.42;
	mins[1] = -RUNE_FLASH_RADIUS * 1.42;
	mins[2] = -RUNE_FLASH_RADIUS * 1.42;
	maxs[0] = RUNE_FLASH_RADIUS * 1.42;
	maxs[1] = RUNE_FLASH_RADIUS * 1.42;
	maxs[2] = RUNE_FLASH_RADIUS * 1.42;

	VectorAdd( ent->r.currentOrigin, mins, mins );
	VectorAdd( ent->r.currentOrigin, maxs, maxs );

	// begin hopping
	num = trap_EntitiesInBox(mins,maxs,targNum,MAX_GENTITIES);
	for(num--; num > 0; num--) 
	{
		// count from num-1 down to 0
		target = &g_entities[targNum[num]];

		// target must not be the attacker
		if (target == ent) 
			continue;

		if (!(target->client))
			continue;

		if (target->health<=0 || (Q_stricmp(target->classname,"player")))
			continue;

		// target must actually be in RUNE_JUMPING_RADIUS
		if ( Distance(ent->r.currentOrigin,target->r.currentOrigin) > RUNE_FLASH_RADIUS )
			continue;

		if (!(visible(ent,target)) || !Can_Affect_Player(ent,target))
			continue;

		if ( target->client->ps.groundEntityNum == ENTITYNUM_NONE) 
			continue;


		if (target->client->ps.powerups[RUNE_POWERUP_SLOT] == RUNE_REFLECTION)
		{
			trap_SendServerCommand(ent->s.clientNum,"weirdness blind");
			//Rune_SetEffect(ent,EFFECT_REFLECTION,3);
		}
		else
		{
			trap_SendServerCommand(target->s.clientNum,"weirdness blind");
			//Rune_SetEffect(target,EFFECT_FLASH,3);
		}
	}

}


// runevar values
//	0 - has been activated and no request is pending
//	1 - request pending, as soon as it recharges, it will activate
void Rune_Flash_Use(gentity_t *ent)
{
	if (ent->runetime<level.time)
	{
		ent->runetime = level.time + RUNE_FLASH_RECHARGE;
		ent->runevar=0;
		ent->client->ps.stats[STAT_RUNE_COUNTER]=0;
		Rune_Flash_Activate(ent);
	}
	else
	{
		if (ent->runevar==0)
		{
			trap_SendServerCommand( ent->s.clientNum, va("print \"Flash is recharging\n\""));
			ent->runevar=1;
		}
		else
		{
			trap_SendServerCommand( ent->s.clientNum, va("print \"Flash activation cancelled\n\""));
			ent->runevar=0;
		}
	}
}


////////////////////////////////////////////////
//
//		Disarmament
//

void Rune_Disarm_Activate(gentity_t *ent)
{
	int				num, targNum[MAX_GENTITIES];
	vec3_t			mins,maxs;
	gentity_t		*target;

	mins[0] = -RUNE_DISARMAMENT_RADIUS * 1.42;
	mins[1] = -RUNE_DISARMAMENT_RADIUS * 1.42;
	mins[2] = -RUNE_DISARMAMENT_RADIUS * 1.42;
	maxs[0] = RUNE_DISARMAMENT_RADIUS * 1.42;
	maxs[1] = RUNE_DISARMAMENT_RADIUS * 1.42;
	maxs[2] = RUNE_DISARMAMENT_RADIUS * 1.42;

	VectorAdd( ent->r.currentOrigin, mins, mins );
	VectorAdd( ent->r.currentOrigin, maxs, maxs );

	// begin hopping
	num = trap_EntitiesInBox(mins,maxs,targNum,MAX_GENTITIES);
	for(num--; num > 0; num--) 
	{
		// count from num-1 down to 0
		target = &g_entities[targNum[num]];

		// target must not be the attacker
		if (target == ent) 
			continue;

		if (!(target->client))
			continue;

		if (target->health<=0 || (Q_stricmp(target->classname,"player")))
			continue;

		// target must actually be in RUNE_JUMPING_RADIUS
		if ( Distance(ent->r.currentOrigin,target->r.currentOrigin) > RUNE_DISARMAMENT_RADIUS )
			continue;

		if (!(visible(ent,target)) || !Can_Affect_Player(ent,target))
			continue;

		if ( target->client->ps.groundEntityNum == ENTITYNUM_NONE) 
			continue;

		if (target->client->ps.powerups[RUNE_POWERUP_SLOT] == RUNE_REFLECTION)
		{
			trap_SendServerCommand( ent->s.clientNum, va("cp \"%s reflected your disarm!\n\"",target->client->pers.netname));
			ent->client->ps.weaponTime+=RUNE_DISARMAMENT_DURATION;
		//	Rune_SetEffect(ent,EFFECT_REFLECTION,3);
		}
		else
		{
			trap_SendServerCommand( target->s.clientNum, va("cp \"You've been disarmed by %s\n\"",ent->client->pers.netname));
			target->client->ps.weaponTime+=RUNE_DISARMAMENT_DURATION;
		//	Rune_SetEffect(target,EFFECT_DISARMAMENT,3);
		}
	}
}


// runevar values
//	0 - has been activated and no request is pending
//	1 - request pending, as soon as it recharges, it will activate
void Rune_Disarm_Use(gentity_t *ent)
{
	if (ent->runetime<level.time)
	{
		ent->runetime = level.time + RUNE_DISARMAMENT_RECHARGE;
		ent->runevar=0;
		ent->client->ps.stats[STAT_RUNE_COUNTER]=0;
		Rune_Disarm_Activate(ent);
	}
	else
	{
		if (ent->runevar==0)
		{
			trap_SendServerCommand( ent->s.clientNum, va("print \"Disarm is recharging\n\""));
			ent->runevar=1;
		}
		else
		{
			trap_SendServerCommand( ent->s.clientNum, va("print \"Disarm activation cancelled\n\""));
			ent->runevar=0;
		}
	}
}
