/*
 * shepherd.c
 *
 * Used in wild/f8.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/monster";

#include "defs.h"
#include <macros.h>

object *sheep;
object doggy;

#define MAXSHEEP 5

void
resetliving()
{
    int i;

    seteuid(getuid());

    tell_room(ENV(TO),
              "The shepherd gathers all his animals around him.\n");

    for (i = 0; i < MAXSHEEP; i++)
    {
        if (!sheep[i])
        {
            sheep[i] = clone_object(ROKEDIR + "npc/sheep");
            sheep[i]->move(ENV(TO));
            team_join(sheep[i]);
        }
    }
    if (!doggy)
    {
        doggy = clone_object(ROKEDIR + "npc/shepdoggy");
        doggy->move(ENV(TO));
        team_join(doggy);
    }
}

void
create_monster()
{
    set_name("shepherd");
    set_short("old shepherd");
    set_long("This is an old shepherd, walking around with his sheep.\n");
    set_adj("old");

    default_config_npc(45);

    set_random_move(1);

    set_monster_home(WILDDIR + "f8");
    set_restrain_path(WILDDIR + "f");
    sheep = allocate(MAXSHEEP);

    set_alarm(1.0, 600.0, "resetliving");
}
