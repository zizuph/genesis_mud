// updated by Lilith Dec 2021: moved from Sorgum's dir to Terel/common
//    updated to Terel std room, etc

#include "/d/Terel/include/Terel.h"
inherit STDROOM;
   
void
create_room()
{
    set_short("creek");
    set_long(
       "The creek dries up here leaving a trail of frost covered mud " +
       "that leads away from the end of the creek, uphill from here.\n"
    );

    add_prop(ROOM_I_INSIDE, 0);

    add_exit("hill_top", "west", 0);
    add_exit("creek", "east", 0);
	
	add_npc("/d/Terel/silver/monster/squirrel", 2);
    reset_room();
}


