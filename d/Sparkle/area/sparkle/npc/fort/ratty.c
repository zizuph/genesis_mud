/* This rat has been borrowed from Roke and changed so that */
/* it fits in here. Altered by Vladimir 8-09-94 */

#pragma strict_types

inherit "/std/creature";

#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>

#include "defs.h"

inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/domove";

void add_eat();

void
create_creature()
{
    default_config_creature(15);

    set_name("rat");
    set_race_name("rat");
    set_short("gross hairy rat");
    set_adj("hairy");

    set_long("The rat lives from leftovers.\n");

    set_alignment(0);

    set_skill(SS_DEFENCE,4);
    set_skill(SS_UNARM_COMBAT,4);

    add_act("chew");
    add_act("take all");
    add_act("eat all");
    add_act("drop all");

    set_act_time(2);

    set_attack_unarmed(0,  10, 10, W_IMPALE, 10, "jaws");
    set_hitloc_unarmed(0, ({ 90 }), 10, "head");
    set_hitloc_unarmed(0, ({ 90 }), 80, "body");

    set_fatigue(1000);
    set_hp(400);

    set_random_move(2);

    set_alarm(1.0, 0.0, add_eat);
}

int chew(string str)
{
    object lik;

    if(present("corpse",ENV(TO)))
        tell_room(ENV(TO),"The rat chews on a corpse.\n\n");
    else
        return 1;

    while(lik=present("corpse",ENV(TO)))
    {
        lik->decay_fun();
    }

    command("take all");
    command("eat all");
    command("drop all");

/* food lets you grow... */

    default_config_creature(query_average_stat()+5);

    eat_food(-5000,0); /* keep it hungry... */

    return 1;
}

void
add_eat()
{
    set_this_player(this_object());
    add_action("chew", "chew");
}

