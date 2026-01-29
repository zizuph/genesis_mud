
/* 
      A snake for the caverns in Eldoral. 

      Coded by Maniac, 28/6/97
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

#define H_HEAD 0
#define H_BODY 1

void
create_creature()
{
    string *scales = ({ "black", "green", "brown", "grey" });

    set_name("snake");
    set_race_name("snake");
    set_gender(G_NEUTER); 

    set_adj(({scales[random(sizeof(scales))]+"-scaled",
             "slithering"}));

    set_long(capitalize(LANG_ADDART(query_nonmet_name())) + ".\n"); 

    set_stats(({10, 10, 10, 10, 10, 10})); 
    set_hp(query_max_hp()); 
    set_skill(SS_UNARM_COMBAT, 5); 
    set_skill(SS_DEFENCE,5);
    set_attack_unarmed(A_BITE,10,10, W_IMPALE, 100, "fangs");
    set_hitloc_unarmed(H_HEAD, ({3,3,3,3}), 20, "head");
    set_hitloc_unarmed(H_BODY, ({3,3,3,3}), 80, "body");

    add_prop(LIVE_I_NEVERKNOWN, 1); 
    add_prop(NPC_I_NO_LOOKS, 1); 
    add_prop(CONT_I_VOLUME, 2000); 
    add_prop(CONT_I_WEIGHT, 2000); 
    add_prop(CONT_I_HEIGHT, 50); 
    add_act("emote goes sssssSSSSSSssss."); 
    add_act("emote glares hatefully up at you with its slitted red eyes."); 
    add_act("emote slithers slowly around in a circle.");
    set_act_time(10);  
    set_m_in("slithers in");
    set_m_out("slithers"); 
    set_random_move(10); 
    set_restrain_path(CAVERNS);
}

