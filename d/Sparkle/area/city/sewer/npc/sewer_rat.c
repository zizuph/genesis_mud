/*
 *  /w/petros/sparkle/sewer/npc/sewer_rat.c
 *
 *  A standard sewer rat that occupies the sewers of Sparkle
 *  
 *  Created by Petros, April 2008
 *  Adapted from rat created by Styles, 920317
*/

#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";

inherit "/std/act/domove";      /* random move and follow */

#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "../../defs.h"

#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2

#define H_HEAD 0
#define H_BODY 1
#define H_TAIL 2

public void
create_creature()
{
    default_config_creature(20);

    set_name("rat");
    set_race_name("sewer rat");
    add_adj( ({ "hairy", "grey" }) );
    set_short("hairy sewer rat");
    set_long("This filthy rodent occupies the sewers of Sparkle. The rats "
           + "in the sewers must feed well, because this is one of the "
           + "largest rats you have ever seen.\n");
    set_alignment(0);

    set_skill(SS_DEFENCE, 14);
    set_skill(SS_UNARM_COMBAT, 14);
    
    set_gender(G_NEUTER);

    add_prop(CONT_I_WEIGHT, 4000);
    add_prop(CONT_I_VOLUME, 3700);

    add_prop(OBJ_I_NO_INS, 1);
    add_prop(NPC_I_NO_LOOKS, 1);

    /* Wep_type,   to_hit,   pen,   Dam_type,   %usage,   attack_desc */
    set_attack_unarmed(A_BITE,   8, 10, W_IMPALE, 60, "jaws");
    set_attack_unarmed(A_LCLAW, 15,  6, W_SLASH,  20, "left claw");
    set_attack_unarmed(A_RCLAW, 15,  6, W_SLASH,  20, "right claw");

    /* Hit_loc,   *Ac (im/sl/bl/ma),   %hit,   hit_desc */
    set_hitloc_unarmed(H_HEAD, ({ 10, 14,  6,   0 }), 10, "head");
    set_hitloc_unarmed(H_BODY, ({  5,  8, 16,   0 }), 80, "body");
    set_hitloc_unarmed(H_TAIL, ({  5,  8, 16,   0 }), 10, "tail");
    
    // Add the leftovers here
    add_leftover("/std/leftover", "kidney", random(3), 0, 1, 0);
    add_leftover("/std/leftover", "tooth", random(5), 0, 1, 0);
    add_leftover("/std/leftover", "ear", random(3), 0, 1, 0);
    add_leftover("/std/leftover", "intestine", random(2), 0, 1, 0);
}
