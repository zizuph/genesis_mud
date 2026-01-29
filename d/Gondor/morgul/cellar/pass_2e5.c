/*
 *	/d/Gondor/morgul/cellar/pass_2e5.c
 *
 *	This is the room of the dungeons where one of the
 *	pearls for the Immortal entrance quest can be found.
 *
 *	Olorin, 13-jan-1996
 *
 *      immortal quest stuff removed at teth's request
 *      gnadnar 02-sep-1998
 */
#pragma strict_types

inherit "/d/Gondor/morgul/cellar/cellar.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/cellar/cellar_defs.h"


void
create_morgul_cellar_room()
{
    set_level(2);
    set_room_type("dead end");
    set_extra_long("This seems to be a far older part of the dungeons "
      + "than the rest. The narrow tunnel comes to a dead end here. The "
      + "only exit is to the north.");

    add_walls("While they are build from the same rock, the walls in "
      + "this tunnel seem to be older than elsewhere in these dungeons.");
    add_floor("A thick layer of dust covers the floor.");
    add_ceiling();
    add_c_passage("north");

    add_exit(CELLAR_DIR + "pass_2e4", "north", "@@check_exit@@", 1, 1);
}
