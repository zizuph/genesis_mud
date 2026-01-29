/*
 *	/d/Gondor/morgul/cellar/pass_2e4.c
 *
 *	Olorin, 13-jan-1996
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
    set_room_type("narrow tunnel");
    set_extra_long("This seems to be a far older part of the dungeons "
      + "than the rest. The narrow tunnel continues further south, while "
      + "an archway to the north is leading into a dark dungeon.");

    add_walls("While they are build from the same rock, the walls in "
      + "this tunnel seem to be older than elsewhere in these dungeons.");
    add_floor("A thick layer of dust covers the floor.");
    add_ceiling();
    add_archway("north");
    add_c_passage("south");

    add_exit(CELLAR_DIR + "dung_2e3", "north", "@@check_exit@@", 1);
    add_exit(CELLAR_DIR + "pass_2e5", "south", "@@check_exit@@", 1);
}

