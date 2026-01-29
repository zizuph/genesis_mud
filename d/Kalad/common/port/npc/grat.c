inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
inherit "/std/combat/unarmed";
inherit "/std/act/domove";/* random move and follow */
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>
#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2
#define H_HEAD 0
#define H_BODY 1
/* by Antharanos */
create_monster()
{
    ::create_monster();
    set_name("rat");
    set_race_name("rat"); 
    set_adj("giant");
    add_adj("black");

    set_long("A massive dock rat! It must be over a foot long!\n");

    set_gender(G_NEUTER);
    set_random_move(40);
    set_stats(({10,15,12,1,2,20}));

    set_skill(SS_SWIM, 50);

    add_prop(CONT_I_WEIGHT, 4000);
    add_prop(CONT_I_VOLUME, 4000);

    add_prop(OBJ_I_NO_INS, 1);

    set_attack_unarmed(A_BITE,   8, 10, W_IMPALE, 80, "jaws");
    set_attack_unarmed(A_LCLAW, 15,  6, W_SLASH,  10, "left paw");
    set_attack_unarmed(A_RCLAW, 15,  6, W_SLASH,  10, "right paw");

    set_hitloc_unarmed(H_HEAD, ({ 10, 14,  6,   5 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({  5,  8, 16,   0 }), 80, "body");

}
