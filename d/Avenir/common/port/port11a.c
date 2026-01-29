// file name:        port11a.c
// creator(s):       This is a dummy room made by Lilith Feb 2022
//                   because this was once a room that had a shipline
//                   and it is still in the database and if this room
//                   isn't here there is an error in the /lplog at reboot.

#pragma strict_types
#include "/d/Avenir/common/port/port.h"
inherit PORT_ROOM;

static void
create_port_room()
{
 	
    set_short("Dummy room");
    set_long("This room exists to resolve an error in the /lplog at reboot. "+
        "There was once a shipline to this room but there was a big shipline "+
        "purge back in 2009 or so when Keeper Gorboth decided to push all "+
        "traffic through Sparkle. It looks like the shipline/this room wasn't "+
        "removed from the shipline database properly so its been producing "+
        "errors in the lplog for a dozen years. Hopefully this room now "+
        "existing will prevent that 'File not found' error from continuing. "+
        "--Lilith.\n");
}
