
/* 
 *    A slime for the caverns in Eldoral. 
 *
 *    Coded by Maniac, 29/6/97
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

#define A_TOUCH  0

#define H_BODY 1

void
create_creature()
{
    string *stype = ({ "bubbling", "mouldy", "oozing", "putrid" });

    set_name("slime");
    set_race_name("slime");

    set_adj(({stype[random(sizeof(stype))], "green"}));

    set_long(capitalize(LANG_ADDART(query_nonmet_name())) + ".\n"); 

    set_gender(G_NEUTER);  
    set_stats(({10, 10, 10, 10, 10, 10})); 
    set_hp(query_max_hp()); 
    set_skill(SS_UNARM_COMBAT, 5); 
    set_skill(SS_DEFENCE,5);

    set_attack_unarmed(A_TOUCH,10,10, W_BLUDGEON, 100, "touch");
    set_hitloc_unarmed(H_BODY, ({3,3,3,3}), 100, "body");

    add_prop(LIVE_I_NEVERKNOWN, 1); 
    add_prop(NPC_I_NO_LOOKS, 1); 
    add_prop(CONT_I_VOLUME, 2000); 
    add_prop(CONT_I_WEIGHT, 2000); 
    add_prop(CONT_I_HEIGHT, 50); 
    add_act("emote bubbles briefly."); 
    add_act("emote gives off a putrid stench."); 
    add_act("emote oozes slowly over an insect on the floor, dissolving it."); 
    set_act_time(10);  
    set_m_in("oozes in"); 
    set_m_out("oozes"); 
    set_random_move(10); 
    set_restrain_path(CAVERNS);
}

