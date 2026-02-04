

inherit "/std/room";
#include "/d/Terel/common/terel_defs.h";
#include <macros.h>
#include <stdproperties.h>

#define BS(s)	(break_string(s, 70))
#define TP	this_player()

#define EAST_EXIT  MANSION + "second/front_stairs"
#define SOUTH_EXIT MANSION + "colors/col_15"
/*
#define NORTH_EXIT MANSION + "second/landing_n1"
*/

create_room()
{
    set_short("Landing");
    set_long(BS(
	"You are standing on the landing of the second floor.  Here, " +
	"the uneven floor appears very unsafe.  Dust seems to linger " +
        "in the air here.  You can see it settling on a huge grandfather " +
	"clock, which stands neatly against the west wall.\n"));

    add_exit(EAST_EXIT,  "east", 0);
    add_exit(SOUTH_EXIT, "south", 0);
/*
    add_exit(NORTH_EXIT, "north", 0);
*/

    add_prop(ROOM_I_INSIDE, 1);

    add_item(({"floor", "boards", "floorboards"}),
	"Despite the uneven surface to these floor boards, they " +
	"are quite firm.\n");

    add_item(({"clock", "grandfather clock", "grandfather"}), BS(
	"This magnificent clock is made from pure oak.  Despite a " +
	"loud ticking sound eminating from the clock, the hands " +
	"appear to remain still.\n"));

    add_cmd_item(({"clock", "grandfather clock", "grandfather"}), "enter",
	"The door to the clock is closed.\n");

    add_cmd_item(({"clock", "grandfather clock", "grandfather"}), "open",
   "The door to the clock is locked!\n");

    add_cmd_item(({"clock", "grandfather clock", "grandfather"}), "unlock",
   "It seems impossible to unlock!\n");

    add_item(({"hands", "face", "clock face", "clock hands"}),
       "The hands state the time as two minutes before twelve.\n");
}
    
