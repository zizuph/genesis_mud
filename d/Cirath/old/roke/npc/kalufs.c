/*
 * kalufs.c
 *
 * Used in nyreese/cadu_inn.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* Tika in the Inn of last homes */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/monster";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

void
create_monster()
{
    int i;

    add_prop(LIVE_I_ALWAYSKNOWN, 1);

    set_living_name("kalufs");
    set_name("kalufs");
    add_name("bartender");
    
    set_long("He is leaning against the bar.\n");
    set_race_name("human");
    set_gender(0);

    set_skill(SS_UNARM_COMBAT, 100);

    set_gender(0);
    for (i = 0; i < 6; i++)
        set_base_stat(i, 130);
    set_alignment(170);
}

void
thank(object ob, object giver)
{
    if (objectp(giver) && present(giver, E(TO)))
        command("smile " + OB_NAME(giver));
    else
        command("smile");

    if (objectp(ob))
        command("drink " + OB_NAME(ob));
    else
        command("drink all");
}

void
enter_inv(object ob, object from)
{
    object giver;
    ::enter_inv(ob, from);

    giver = from;
    if (!objectp(giver))
        giver = this_player();

    if (function_exists("create_drink", ob))
        set_alarm(1.0, 0.0, &thank(ob, giver));
}
