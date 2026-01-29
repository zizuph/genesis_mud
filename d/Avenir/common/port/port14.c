// file name:        port14.c
// creator(s):       Ilyian
// revision history: Lilith, 21 Feb 2014  Tweaked room desc
//           Lilith, Sep 2021: Added fishing prop.
// purpose:
// note:
// bug(s):
// to-do:
// Ship cancelled until further notice - Tapakah, 05/2009
//
#pragma strict_types

#include "/d/Avenir/common/port/port.h"
//#include "/d/Avenir/common/ships/ship.h"

inherit PORT_ROOM;

private static object ship;

public string
exa_block(void)
{ 
    return "Scenes depicting humans and dwarves have been carved "+
           "into the four sides of this jasper obelisk.\nThe base has been "+ 
           "inscribed with the words:\n"+
           "    The G.S. Luminous no longer sails to the lands of Faerun.\n";
} 

static void
create_port_room()
{
	add_prop(ROOM_I_TYPE, ROOM_BEACH);
	add_prop("_live_i_can_fish", "saltwater");

    set_short("Northern ledge in Sybarus Port, west of the shiplines");
    set_long("You are on a wide ledge between the cavern wall to " +
             "the north and the churning waters of a lake to the south. " +
             "Mist seems to cling everywhere, making your footing " +
             "unsteady. The ledge narrows to the west, and continues " +
             "east toward the buildings of the Port of Sybarus. "+			
/*
			 "A carved jasper obelisk marks "+
             "this as the former berth for the G.S. Luminous, which "+
	         "used to sail from here to Faerun."+
*/
			 "\n");

    IN
    LIGHT

    add_exit("port13", "east");
    add_exit("port15", "west"); 

    add_rift_item();
    add_wall_item();
    add_no_swim_cmditems();

/*
    add_item(({"scene", "scenes"}), "They are simple scenes, seeming to "+
        "indicate dwarves and humans living and working in together in "+
        "the same city.\n");

    add_item(({"sign", "obelisk", "jasper", "base"}), "@@exa_block@@");
    add_cmd_item(({"sign","base", "obelisk"}), "read", "@@exa_block@@");
*/
    add_tell("The roar from the great rift increases to a thunderous " +
             "climax, and then recedes again.\n");

    add_prop(ROOM_I_NO_CLEANUP, 1);

#if 0
    ship = clone_object(FRUN_DIR + "ship");
    ship->move(this_object(), 1);
    ship->start_ship();
#endif
}
