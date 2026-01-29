inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/attack";

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include "../default.h"

#define	A_BITE	0

#define	H_HEAD	0
#define	H_SHELL	1
#define	H_FOOT	2

void
create_creature()
{
    set_name("tortoise");
    set_race_name("tortoise");
    add_adj("large");
    add_adj("green");
    set_long("It definitely doesn't look friendly!\n");

    set_stats( ({ 50, 70, 10, 5, 5, 65 }) );

    set_skill(SS_DEFENCE, 40);
    set_skill(SS_SWIM, 100);
    
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(CONT_I_VOLUME, 11000);
    add_prop(CONT_I_WEIGHT, 11000);

    set_attack_unarmed(A_BITE, 100, 30, W_IMPALE, 55, "jaws");

    set_hitloc_unarmed(H_HEAD, ({ 25, 35, 30, 20 }), 20, "head");
    set_hitloc_unarmed(H_SHELL, ({ 45, 40, 65, 40 }), 60, "shell");
    set_hitloc_unarmed(H_FOOT, ({ 25, 35, 30, 20 }), 20, "foot");

    heal_hp(query_max_hp());
    
    set_aggressive(1);
    set_attack_chance(40);

    set_random_move(20);
    set_restrain_path(TCASTLE_DIR + "moat");
    set_monster_home(TCASTLE_DIR + "moat6");
}
