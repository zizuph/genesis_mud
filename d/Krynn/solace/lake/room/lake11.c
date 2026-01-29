/* created by Splunge, modified by Aridor, modified by Cherek, Feb 2007 */

#include "../local.h"

inherit VILLAGE_BASE_OUT;

object wildlife;

void
create_toron_room() 
{
    set_short("A small clearing");
    set_long("You are in a small clearing with dense foliage all " +
             "around you. Some trees have been chopped down to create an " +
             "open space in the middle. There is a path leading off to " +
             "the east from here.\n");

    add_item("clearing",
             "It is a natural clearing, however it seems like someone " +
             "has chopped down trees to make it wider. \n");
             
    add_item(({"foliage","trees"}),
              "The forest around you is dense and dark.\n");

    add_item(({"space", "open space", "middle"}),
              "There is nothing there. Just open space. \n");
              
    add_item("path",
             "The path looks like it has been used recently, especially " +
             "towards the east.\n");

    add_exit(ROOM + "lake8","east",0,3);

    reset_room();
}
