/*
 * /d/Gondor/morgul/cellar/pass_2e3.c
 *
 * Olorin, 18-Oct-1995
 */
inherit "/d/Gondor/morgul/cellar/cellar.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/cellar/cellar_defs.h"

void    reset_room();

object  olog;

void
create_morgul_cellar_room()
{
    set_level(2);
    set_room_type("dark passage");
    set_extra_long("The dark tunnel runs south while a flight of "
      + "stairs is leading up in an archway set into the north wall.");

    add_walls();
    add_floor();
    add_c_passage("south");
    add_ceiling();
    add_up_archway();

    add_exit(CELLAR_DIR + "pass_2e2", "south", check_exit, 1);
    add_exit(CELLAR_DIR + "dung_1e5", "up",    block_npc,  1);

    // delay cloning the first troll
    set_alarm(120.0 + 240.0 * rnd(), 0.0, reset_room);
}

void
reset_room()
{
    if (objectp(olog))
        return;

    olog = clone_object(MORGUL_DIR + "npc/ithil_olog");
    olog->set_restrain_path(CELLAR_DIR);
    olog->set_random_move(4);
    olog->arm_me();
    olog->move_living("down", TO);
}

