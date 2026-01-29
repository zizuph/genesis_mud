
/* 
 *    A millepede for the caverns in Eldoral. 
 *
 *    Coded by Maniac, 29/6/97. 
 */ 

inherit "/std/creature"; 
inherit "/std/act/domove"; 
inherit "/std/combat/unarmed";
inherit "/std/act/action";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <const.h>
#include "defs.h"

#define A_BITE  0

#define H_BODY 1

void
create_creature()
{
    string *mtype = ({ "black", "brown", "red", "long", "creepy" });

    set_name("millipede");
    set_race_name("millipede");

    set_adj(({mtype[random(sizeof(mtype))], "crawling"}));

    set_long(capitalize(LANG_ADDART(query_nonmet_name())) + ".\n"); 

    set_gender(G_NEUTER);  
    set_stats(({10, 10, 10, 10, 10, 10})); 
    set_hp(query_max_hp()); 
    set_skill(SS_UNARM_COMBAT, 5); 
    set_skill(SS_DEFENCE,5);

    set_attack_unarmed(A_BITE,10,10, W_IMPALE, 100, "bite");
    set_hitloc_unarmed(H_BODY, ({3,3,3,3}), 100, "body");

    add_prop(LIVE_I_NEVERKNOWN, 1); 
    add_prop(NPC_I_NO_LOOKS, 1); 
    add_prop(CONT_I_VOLUME, 1000); 
    add_prop(CONT_I_WEIGHT, 1000); 
    add_prop(CONT_I_HEIGHT, 50); 
    add_act("emote twitches its feelers."); 
    add_act("emote crawls slowly up the wall."); 
    add_act("emote crawls quickly across the floor."); 
    set_act_time(10);  
    set_m_in("crawls in"); 
    set_m_out("crawls"); 
    set_random_move(10); 
    set_restrain_path(CAVERNS);
}

