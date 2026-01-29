inherit "/std/room";

#include "defs.h"
#include "/sys/stdproperties.h"

/* Prototypes */
void reset_room();

void
create_room()
{
    set_short("First floor of southern tower");
    set_long(break_string(
	  "You have reached the first floor of the southern tower. "
	+ "It is quite dark here, and the air is damp. The tower "
	+ "has not been used for a very long time. Circular stairs "
	+ "lead up and down.\n", 70));

    add_item("stairs", break_string(
	  "The broad wooden staircase winds upwards to the second floor, "
	+ "and downwards to the ground level following the wall of the "
        + "tower.\n", 70));

    /* Climbing the stairs is tiresome... */
    add_exit(STAND_DIR + "tower23", "up", 0, 4);
    add_exit(STAND_DIR + "tower21", "down", 0, 4);

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);

    reset_room();
}

void
reset_room()
{
    if (!present("tendril"))
	clone_object(STAND_OBJ + "tendril")->move(this_object());
}
