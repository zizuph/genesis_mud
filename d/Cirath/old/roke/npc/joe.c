/*
 * joe.c
 *
 * Used in nyreese/red_pub.c
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

void
create_monster()
{
    int i;

    add_prop(LIVE_I_ALWAYSKNOWN, 1);

    set_living_name("joe");
    set_name("joe");

    set_long("This is a really sloppy bartender. You notice a small name " +
             "tag on his dirty shirt, which tells you that his name is Joe.\n");

    set_race_name("human");
    set_gender(0);

    set_skill(SS_UNARM_COMBAT, 100);

    set_gender(0);
    for (i = 0; i < 6; i++)
        set_base_stat(i, 60);
    set_alignment(-210);

    ::create_monster();
}
