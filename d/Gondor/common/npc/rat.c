/* A minor rat. Used in human starting location.
   Styles, 920317.
*/
#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/d/Gondor/common/lib/logkill.c";

inherit "/std/act/attack";	/* aggressive attacks     */
inherit "/std/act/domove";	/* random move and follow */

#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>

#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2

#define H_HEAD 0
#define H_BODY 1

void
create_creature()
{
    set_name("rat");
    set_race_name("rat"); 
    set_adj("gray");
    add_adj("hairy");

    set_long("This is a wet and filthy rat with a long tail.\n");

    set_gender(G_NEUTER);
    set_random_move(40);
    set_stats(({ 2, 4, 3, 1, 6, 20})); /* str, dex, con, int, wis, dis */
    set_alignment(0); // neutral alignment for animals

    set_skill(SS_SWIM, 95);

    add_prop(CONT_I_WEIGHT, 2000);
    add_prop(CONT_I_VOLUME, 1500);

    add_prop(LIVE_I_SEE_DARK,4);
    add_prop(OBJ_I_NO_INS, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    /* Wep_type,   to_hit,   pen,   Dam_type,   %usage,   attack_desc */
    set_attack_unarmed(A_BITE,   8, 10, W_IMPALE, 80, "jaws");
    set_attack_unarmed(A_LCLAW, 15,  6, W_SLASH,  10, "left paw");
    set_attack_unarmed(A_RCLAW, 15,  6, W_SLASH,  10, "right paw");

    /* Hit_loc,   *Ac (im/sl/bl/ma),   %hit,   hit_desc */
    set_hitloc_unarmed(H_HEAD, ({ 10, 14,  6,   5 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({  5,  8, 16,   0 }), 80, "body");

    set_whimpy(20);
}

/* Solemnian prestige */
int query_knight_prestige() {return 20;}
