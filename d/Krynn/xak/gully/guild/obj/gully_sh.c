
/*  
     Gully Dwarf Shadow - Karath@Genesis - Andrew Smith Oct 1997

     Based on code by Maniac@Genesis, March 1997    
     Copyright (C) Miguel Leith 1997 
 */


#pragma save_binary

inherit "/std/guild/guild_race_sh";
#include <stdproperties.h>
#include <ss_types.h>
#include <const.h>
#include <macros.h>
#include <formulas.h>
#include <wa_types.h>

#include "gully.h"

/* global variables */ 

string query_guild_style_race() { return GULLY_GUILD_STYLE; }
string query_guild_name_race() { return GULLY_GUILD_NAME; }

int 
query_guild_tax_race() 
{ 
    return GULLY_GUILD_TAX; 
}


/* 
 * Return 1 if they try to join another race guild.
 */ 
int
query_guild_not_allow_join_race(object player, string type, 
                               string style, string name) 
{
    if ((type == "race") && !player->query_wiz_level()) { 
         notify_fail("How can you be Aghar an' another race? You "+
                     "confused!\n"); 
         return 1;
    } 

    return ::query_guild_not_allow_join_race(player, type, style, name);
}

void
init_race_shadow(string str)
{
    ::init_race_shadow();

    gully_init_title(); 
}

void
attack_object(object victim)
{
    shadow_who->command("gulp nervously");
    shadow_who->attack_object(victim); 
}

string
query_guild_title_race()
{
    return GULLY_BASE_TITLE;
}


string
query_guild_trainer_race()
{
    return GULLY_TRAINROOM;
}
