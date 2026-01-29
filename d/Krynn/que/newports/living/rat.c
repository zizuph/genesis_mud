/* A minor rat. Used in human starting location.
   Styles, 920317.
*/

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";

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
    
    if (!IS_CLONE)
      return;
    set_name("rat");
    set_race_name("rat"); 
    set_adj("gray");
    add_adj("hairy");
    set_long("This is just another filthy little rodent.\n");
    
    set_aggressive(1);

    set_gender(G_NEUTER);
    set_stats(({ 2, 7, 3, 1, 6, 20})); /* str, dex, con, int, wis, dis */

    set_skill(SS_SWIM, 95);

    add_prop(CONT_I_WEIGHT, 4000);
    add_prop(CONT_I_VOLUME, 3700);

    add_prop(OBJ_I_NO_INS, 1);

    /* Wep_type,   to_hit,   pen,   Dam_type,   %usage,   attack_desc */
    set_attack_unarmed(A_BITE,   7,  8, W_IMPALE, 80, "jaws");
    set_attack_unarmed(A_LCLAW, 13,  5, W_SLASH,  10, "left paw");
    set_attack_unarmed(A_RCLAW, 13,  5, W_SLASH,  10, "right paw");

    /* Hit_loc,   *Ac (im/sl/bl/ma),   %hit,   hit_desc */
    set_hitloc_unarmed(H_HEAD, ({  8, 12,  5,   5 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({  4,  7, 10,   0 }), 80, "body");

}
