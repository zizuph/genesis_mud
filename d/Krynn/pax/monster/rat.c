/*
   Pax Tharkas

   Borrowed from : A minor rat. Used in human starting location.
                   Styles, 920317.

   rat.c
   -----

   Copied an altered : 95/03/25
   By ...............: Jeremiah

   Latest update ....: 95/03/26
   By ...............: Jeremiah

   A minor rat :) .. I'll just add a few things and make them a
   little bit stronger. 

*/

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";       /* Allows rat to act  */
inherit "/std/act/domove";       /* Allows rat to move */

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
    set_short("rat");
    set_race_name("rat"); 
    set_adj("gray");
    add_adj("hairy");
    set_long("This is a dark gray rat. It is very filthy. So filthy you " +
             "can almost smell it. The rat looks at you with an " +
             "insane glow in its eyes. Rats, like this one, are known to " +
             "carry and spread diseases where ever they go.\n");
    
    set_aggressive(1);

    default_config_mobile(15);
    set_random_move(25);

    set_gender(G_NEUTER);
    set_stats(({ 2, 10, 5, 1, 6, 20})); /* str, dex, con, int, wis, dis */

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
