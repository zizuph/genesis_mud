/* A small mouse used in human starting location.
   Styles, 920322.
*/

#pragma save_binary
#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";

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

public void
create_creature()
{
    if (!IS_CLONE)
	return;
    set_name("mouse");
    set_race_name("mouse"); 
    set_pshort("mice"); 
    set_adj("small");
    add_adj("white");

    set_long("Aww... What a cute little mouse.\n");

    set_gender(G_NEUTER);
    set_random_move(40);
    set_stats(({ 1, 2, 1, 1, 2, 2})); /* str, dex, con, int, wis, dis */

    set_skill(SS_SWIM, 45);

    add_prop(CONT_I_WEIGHT, 300);
    add_prop(CONT_I_HEIGHT, 60);
    add_prop(CONT_I_VOLUME, 220);

    add_prop(OBJ_I_NO_INS, 1);

    /* Wep_type,   to_hit,   pen,   Dam_type,   %usage,   attack_desc */
    set_attack_unarmed(A_BITE,   6, 7, W_IMPALE, 80, "small teeth");
    set_attack_unarmed(A_LCLAW, 12,  3, W_SLASH,  10, "left paw");
    set_attack_unarmed(A_RCLAW, 12,  3, W_SLASH,  10, "right paw");

    /* Hit_loc,   *Ac (im/sl/bl/ma),   %hit,   hit_desc */
    set_hitloc_unarmed(H_HEAD, ({ 5, 7, 3, 2 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 2, 4, 8, 0 }), 80, "body");
}
