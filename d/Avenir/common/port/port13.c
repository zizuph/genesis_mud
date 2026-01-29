#pragma strict_types
// file name:        port13.c
// creator(s):       Ilyian
// purpose:          ANSALON SHIP DOCKS HERE
// revision history:
//		     Denis, Sep'96: Changes due to the port inheritance recode.
// Ship cancelled until further notice, Tapakah, 05/2009
// Pier now used for Pan-Donut Circle line, Tapakah, 31/05/2009
//
//           Lucius May 2009: Cleaned up after Tapakah.
//           Lilith, Sep 2021: Added fishing prop.
//
#include "/d/Avenir/common/port/port.h"

inherit PORT_ROOM;
inherit "/d/Genesis/gsl_ships/lib/pier";

#define SIGN     "/d/Sparkle/area/sparkle/gsl_ships/circle-line/objs/sign"

public string
exa_block(void)
{ 
    return "This is a large granite block with these words "+
	"carved into it:\n    'The Donut Way' of Grosso lands here.\n";
} 

public void
create_port_room(void)
{
	add_prop(ROOM_I_TYPE, ROOM_BEACH);
	add_prop("_live_i_can_fish", "saltwater");

    set_short("Circle Line berth at the Port of Sybarus");
    set_long("You are on a wide ledge between a cavern wall to " +
             "the north and the churning waters of a lake to the south. " +
             "Mist seems to cling everywhere, making your footing " +
             "unsteady. The ledge narrows to the west, and continues " +
             "east toward some buildings which mark the port facilities "+
			 "of Sybarus. A granite block with some "+
             "words carved into it inform that passage on the "+
             "Circle Shipline is possible from here.\n");

    IN; LIGHT;

    add_exit("port12", "east");
    add_exit("port14", "west");

    add_rift_item();
    add_wall_item();
    add_no_swim_cmditems();

    add_item(({"block", "granite block"}), "@@exa_block@@");
    add_cmd_item(({"block", "granite block"}), "read", "@@exa_block@@");
    add_tell("The roar from the great rift increases to a thunderous " +
             "climax, and then recedes again.\n");

#if 0
    object ship = clone_object(SHIP + "ansalon/ship");
    ship->move(this_object(),1);
    ship->start_ship();
#endif

    sign = clone_object(SIGN);
    sign->move(TO);

    add_pier_entry(PORT + "port13", "Sybarus", "Pan-Donut Circle");
    initialize_pier();
}
