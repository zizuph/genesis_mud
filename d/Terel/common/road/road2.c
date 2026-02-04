/* -*- C -*- */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

create_room()
{
    ::create_room();
    set_short("Road");
    set_long("This is a simple stony road that leads out across a\n" +
             "great moor. Patches of ice and snow are sprinkled out\n" +
             "upon the rocky grass. The sky is dreary, the wind cold.\n" +
	     "The road leads southwest and east.  \n");
    add_my_desc("A swamp stretches out across the moor to the northwest.\n");
	add_prop(ROOM_S_MAP_FILE, "town_last.txt");
    add_exit("/d/Terel/common/road/road1", "east",0);
    add_exit("/d/Terel/common/road/road3", "southwest",0);
    add_exit("/d/Terel/common/swamp/sw1", "northwest", 0);
}

