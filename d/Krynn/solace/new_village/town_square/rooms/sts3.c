/*
 * STS Room 3
 * Created by Leia
 * May 30, 2005
 *
 * Last Updated By:
 * Leia
 * July 1, 2005
 * Lunatari
 * Jan 28, 2008 (typo)
*/

#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit SQUARE_BASE;

void
reset_solace_room()
{
}

void
create_solace_room()
{
    set_add_buildings();
    add_item(({"trees"}), "There are several large vallenwoods in the area. One of the vallenwoods is the most beautiful tree you have ever seen.\n");
    add_item(({"tree", "vallenwood", "vallenwood tree"}), "This vallenwood is majestically tall and larger than any of the other trees in Solace. It has aged beautifully, and seems to be the only tree not affected by the fires of the war. There is one dark spot on its trunk.\n");
    add_item(({"spot", "dark spot", "knot"}), "This dark spot seems to be a knot in the trunk. It appears to be the only imperfection on the tree. There is some sort of marking in the center of the knot.\n");
    add_item(({"marking", "carving", "markings"}), "Inspecting the marking carefully, it seems as though it has been carved into the tree with a knife of some sort. Perhaps you can read the marks.\n");
    add_cmd_item("marks", "read", "@@read_marks@@");
    add_exit(NORTHSTS3, "north");
    add_exit(ROOM5, "south");
    add_exit(EASTSTS3, "east");
    add_exit(ROOM2, "west");
    add_exit(NWSTS3, "northwest");
    add_exit(ROOM6, "southeast");
    add_exit(ROOM4, "southwest");
    reset_solace_room();
}

string read_marks(string str)
{
    return "You read the following:\n" + 
    " \n "  + 
    " ####     ####\n" + 
    " #    #   #    #\n" + 
    "#      # #      #\n" + 
    "#       #        #\n" + 
    " #  Tanis        #\n" + 
    "  #   and       #\n" + 
    "   #   Kitiara #\n" + 
    "    # Forever #\n" + 
    "     #       #\n" + 
    "      #     #\n" + 
    "       #   #\n" + 
    "        # #\n" + 
    "         #\n";
}
