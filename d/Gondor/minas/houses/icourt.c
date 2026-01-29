inherit "/d/Gondor/common/room";
#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include <macros.h>

object door;

void create_room()
{
     set_short("A courtyard of a house");
     set_long(BSN("This is a courtyard infront of a beautiful house, no " +
              "doubt the owner is a noble. Cobblestones fitted neatly " +
              "together make a breath taking pattern on the ground, the " +
              "image of a great eagle. The front door of the house is a " +
              "few feet to the north and heading west will lead you back " +
              "on to the main street. A plaque can be seen on a stone " +
              "by the entrance to the street."));
     add_item("stone",BSN("A fairly big white-stone rock nearly three feet high. The rock has a plaque on it."));
     add_item("plaque",BSN("The plaque is made of steel and apparantly " +
              "something written on it."));
     add_item(({"eagle","image","cobblestones","cobblestone","ground"}),
              BSN("The cobblestones are colored, some white, some brown. " +
                  "The colors form a perfect image of an eagle, wings " +
                  "outstretched and soaring above the mountains."));
     add_exit(MINAS_DIR +"e3crc3","west",0);
     door = clone_object(MINAS_DIR + "obj/i_front_door");
     door->move(this_object());
     
}

void init()
{
    ::init();
    add_action("read_plaque", "read");
}

read_plaque(str)
{
    if(!str)
        {
	NFN0("Read what?\n");
	}
    if(str == "plaque")
	{
	write("The plaque has one word. It reads: Imrazor.\n");
        return 1;
        }
    return 0;
}


