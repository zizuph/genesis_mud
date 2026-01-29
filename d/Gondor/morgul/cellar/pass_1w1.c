/*
 * /d/Gondor/morgul/cellar/pass_1w1.c
 * A passage on the first floor of dungeons below the Morgul Tower
 *
 * Olorin, 05-nov-1995
 */
#pragma strict_types

inherit "/d/Gondor/morgul/cellar/cellar.c";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/cellar/cellar_defs.h"

void    reset_room();

object  mage;

void
create_morgul_cellar_room()
{
    set_level(1);
    set_room_type("dark narrow passage");
    set_extra_long("To the east, this passage ends in front of a large "
      + "steel gate, while to the west, it leads into a large dark room.");

    add_ceiling();
    add_floor();
    add_walls();

    add_exit(CELLAR_DIR + "cellar_1c",   "west",  0, 1);

    clone_object(CELLAR_DIR + "doors/cellar_in")->move(TO);

    reset_room();
    add_prop(ROOM_I_NO_CLEANUP, 1); // To prevent gate from relocking
}

void
reset_room()
{
    if (!objectp(mage))
    {
        mage = clone_object(MAGES_DIR + "newnpc/pharazon");
        mage->arm_me();
        mage->move_living("down", TO);
    }
}

