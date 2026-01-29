/*
 * rat.c
 *
 * Used in nyreese/cas_a4.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 * Obliterated some code /Cotillion, Aug 2005
 */

#pragma save_binary
#pragma strict_types

inherit "/std/creature";

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>

inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/domove";

void
add_eat()
{
    set_this_player(this_object());
    add_action("chew", "chew");
}

void
default_config_npc(int i)
{
    int j;
    for (j = 0; j < 6; j++)
        set_base_stat(j, i);
}

void
create_creature()
{
    default_config_npc(15);

    set_name("rat");
    set_race_name("rat");
    set_short("black rat");
    set_adj("black");

    set_long("The rat lives from leftovers.\n");

    set_alignment(0);

    set_skill(SS_DEFENCE, 50);
    set_skill(SS_UNARM_COMBAT, 50);

    add_act("chew");
    add_act("take all");
    add_act("eat all");
    add_act("drop all");

    set_act_time(2);

    set_alarm(2.0, 0.0, add_eat);

    set_attack_unarmed(0, 100, 100, W_IMPALE, 60, "jaws");
    set_hitloc_unarmed(0, ({100}), 10, "head");
    set_hitloc_unarmed(0, ({100}), 80, "body");

    set_random_move(2);
}

int
chew(string str)
{
    object corpse;

    if (present("corpse", ENV(TO)))
        tell_room(ENV(TO), "The rat chews on a corpse.\n\n");
    else
        return 1;
    
    corpse->decay_fun();
    return 1;
}
