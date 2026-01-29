/*
 * /d/Gondor/morgul/cellar/dung_2e3.c
 * A dungeon on the second floor of dungeons below the Morgul Tower
 *
 * Olorin, 13-jan-1996
 *
 * since immortal quest was removed at teth's request, use
 * normal olog and normal exit blocks.
 * gnadnar, 02-sep-1998
 */
#pragma strict_types
inherit "/d/Gondor/morgul/cellar/cellar.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/cellar/cellar_defs.h"

void    reset_room();

object *olog = allocate(4);

void
create_morgul_cellar_room()
{
    set_level(2);
    set_room_type("gloomy dungeon");
    set_extra_long("A passage is leading south through an archway out "
      + "of this is a large stone chamber. Inside another narrow archway "
      + "a flight of stairs is leading up.");

    add_walls();
    add_floor();
    add_ceiling();
    add_passage("north");
    add_up_archway();

    add_exit(CELLAR_DIR + "pass_2e4", "south", "@@block_exit@@", 1);
    add_exit(CELLAR_DIR + "dung_1e3", "up",    "@@block_npc@@", 1);

    reset_room();
}

void
add_olog()
{
    int     i,
            s;

    for (i = 0, s = sizeof(olog); i < s; i++)
        if (!objectp(olog[i]))
            break;

    if (i == s)
        return;

    olog[i] = clone_object(MORGUL_DIR + "npc/ithil_olog");
    olog[i]->arm_me();
    olog[i]->move_living("down", TO);

    set_alarm(1.0, 0.0, add_olog);
}

void
reset_room()
{
   set_alarm(0.0, 0.0, add_olog);
}

int
do_sneak(string s)
{
    if (s == "s" || s == "south")
        return block_exit();
    return 0;
}

void
init()
{
    add_action(do_sneak, "sneak");
    ::init();
}

