/* A tyrannosaurus rex (dinosaur) */
/* This monster shouldn't be killable, that's why it's stats are that high */

inherit "/std/creature";
inherit "/std/combat/unarmed";

inherit "/std/act/domove";
inherit "/std/act/action";

#include <wa_types.h>
#include <ss_types.h>

#include "monsters.h"
/*
 * Define some attack and hitloc id's
*/
#define A_BITE 0

#define H_HEAD 0
#define H_LLEG 1
#define H_RLEG 2

void 
create_creature()
{
    set_name("brutus");
    set_living_name("brutus");
    set_race_name("trex");
    set_adj("huge");
    set_long("This is one of the toughest creatures you've ever seen.\n");

    set_stats(({750,750,750,200,200,750}));
    set_hp(query_max_hp());
    set_mana(query_max_mana());
    set_fatigue(query_max_fatigue());
    set_exp_combat(50000000);

    set_skill(SS_DEFENCE, 100);
    set_skill(SS_UNARM_COMBAT, 100);

    set_attack_unarmed(A_BITE, 100, 100, W_IMPALE, 100, "jaws");

    set_hitloc_unarmed(H_HEAD, ({80,80,80,80}), 80, "head");
    set_hitloc_unarmed(H_LLEG, ({80,80,80,80}), 80, "left leg");
    set_hitloc_unarmed(H_RLEG, ({80,80,80,80}), 80, "right leg");
}

void
init_living()
{
    if (TP->query_race_name() == "triceratops") TO->attack_object(TP);
}

