#define PATH "/d/Terel/common/road"

#include "/d/Terel/include/Terel.h"

inherit STDROOM;


create_room()
{
    object door;

    set_short("Road");
    set_long(
	"This is a small road, it leads out across a great moor. The " +
	"air is cold, the wind filled with ice. Patches of snow are " +
	"on the ground, spread out across the rocky grass lands. " +
	"A massive arch of stone is here, guarding the way out " +
	"with its silver gates.\n");

    door = clone_object(PATH + "/sgate2");
    door->move(this_object());
	add_prop(ROOM_S_MAP_FILE, "town_last.txt");

    add_exit(PATH + "/road2", "west", 0);    
    add_item(({"stone arch","arch"}),
	     "It is a massive arch of many stones, under which is a " +
	     "silver gate.\n");
}
