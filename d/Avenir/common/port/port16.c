// file name:        port16.c
// creator(s):       Lilith
// revision history: Lilith 21 Feb 2014 room desc update
//           Lilith, Sep 2021: Added fishing prop.
// purpose:
// note:
// bug(s):
// to-do:
#pragma strict_types

#include "/d/Avenir/common/port/port.h"
#include "/d/Avenir/common/ships/ship.h"
#include "/d/Avenir/smis/sys/statserv.h"

inherit PORT_ROOM;

static void
create_port_room(void)
{
    add_prop(ROOM_I_TYPE, ROOM_BEACH);
	add_prop("_live_i_can_fish", "saltwater");
	
    set_short("West end of the north ledge in Sybarus Port cavern");
    set_long("You are on a wide ledge between the cavern wall to " +
             "the north and the churning waters the Sybarus Rift to the south. " +
             "Mist seems to cling to every surface, glossing everything with "+
             "a thin layer of moisture. The sounds of water thundering "+
             "through the Rift seems to hammer your flesh, making your "+
             "very bones vibrate. The ledge angles northwest from here "+
			 "and continues east toward some buildings.\n");
    IN
    LIGHT

    add_exit("port15", "east");
    add_exit("port17", "northwest"); 

    add_rift_item();
    add_wall_item();
    add_no_swim_cmditems();
}
