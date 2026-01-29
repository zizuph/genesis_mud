inherit "/std/room";

#include "defs.h"
#include "/sys/stdproperties.h"

/* Prototypes */
void reset_room();

void
create_room()
{
    set_short("Second floor of southern tower");
    set_long(break_string(
	  "You are standing on the second floor of the southern tower. "
	+ "It is quite dark here, and the air is damp. The tower "
	+ "has not been used for a very long time. Circular stairs "
	+ "lead up and down.\n", 70));

    add_item("stairs", break_string(
	  "The broad wooden staircase winds upwards to the top floor, "
	+ "and downwards to the first floor following the wall of the "
        + "tower.\n", 70));

    /* Climbing the stairs is tiresome... */
    add_exit(STAND_DIR + "tower24", "up", "@@up_check", 4);
    add_exit(STAND_DIR + "tower22", "down", 0, 4);

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);

    reset_room();
}

void
reset_room()
{
    if (!present("ice") && !present("gargoyle"))
	clone_object(STAND_OBJ + "tower_ice")->move(this_object());
}

int
up_check()
{
    if (present("ice"))
    {
	write("The block of ice is barring the way.\n");
	return 1;
    }

    if (present("gargoyle"))
    {
	write("The hideous gargoyle bars the way.\n");
	return 1;
    }
}
