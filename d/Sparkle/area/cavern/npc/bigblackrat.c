
/*
   A big rat, modified from Styles...
   Quis, 920519
*/

/* A minor rat. Used in human starting location.
   Styles, 920317.
*/

#pragma save_binary

inherit "/std/creature";
inherit "/std/combat/unarmed";

#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>

#define A_BITE  0

#define H_HEAD 0
#define H_BODY 1

create_creature() 
{

    if (!IS_CLONE)
	return;

    set_name("rat");
    set_race_name("rat"); 
    set_adj("black");
    set_adj("big");

    set_long("The rat glares back at you.\n");

    set_gender(G_NEUTER);
    set_stats(({ 5 + random(3), 5 + random(3), 5 + random(3), 1, 1, 5})); 
                  /* str, dex, con, int, wis, dis */

    set_skill(SS_DEFENCE, 10);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_I_WEIGHT, 1500);
    add_prop(OBJ_I_VOLUME, 1200);
    add_prop(OBJ_I_NO_INS, 1);

    /* Wep_type,   to_hit,   pen,   Dam_type,   %usage,   attack_desc */
    set_attack_unarmed(A_BITE,   10, 12, W_IMPALE, 100, "jaws");

    /* Hit_loc,   *Ac (impale/slash/bludgeon),   %hit,   hit_desc */
    set_hitloc_unarmed(H_HEAD, ({ 12, 16,  8 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({  7, 10, 18 }), 80, "body");

}