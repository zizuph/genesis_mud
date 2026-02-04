// updated by Lilith Dec 2021: moved from Sorgum's dir to Terel/common
//    updated to Terel std room, added fishing.

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

void
create_room()
{
    set_short("creek");
    set_long(
       "The creek forks away from the brook and gets considerably narrower " +
       "here.  It trickles down to nothing and dries up leaving a muddy " +
       "trail that leads up a hill to the west.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);	
    add_prop("_live_i_can_fish", ({"freshwater"}));

    add_exit("creek_incline", "west", 0);
    add_exit("stream02", "southeast", 0);    
}


