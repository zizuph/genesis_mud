
/*  
    /d/Calia/fireball/inherit/fireball_monster.c

    This is the npc humanoid inherited by fireball players. 

    Coded by Maniac@Genesis

    Copyright (C) Miguel Leith 1997

 */ 

inherit "/std/monster"; 

#include <stdproperties.h>
#include <macros.h>

int fireball_skill; 
string fireball_team; 

void
create_monster()
{
    add_prop(NPC_I_NO_LOOKS, 1); 
    add_prop(NPC_M_NO_ACCEPT_GIVE, 1); 
}

void
set_fireball_skill(int v)
{
    fireball_skill = v; 
}

int
query_fireball_skill()
{
    return fireball_skill; 
}


void
set_fireball_team(string team_name)
{
    fireball_team = team_name; 
}


string
query_fireball_team() 
{
    return fireball_team; 
}

