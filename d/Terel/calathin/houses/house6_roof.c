/*  This is a house.  Coded by Vader on 7/22/92 for the town of Calathin.

    This basic house will be standard for all in the northeast region
    of town (see ~common/town/town_map_draft3)

*/
#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <macros.h>
#include <stdproperties.h>

public void
create_room()
{
    set_short("A loft of a house");
    set_long("This loft must have been used by the children to "+
                 "sleep. Small blankets and mats lay on the floor "+
                 "and a small indentation can be seen at the edge "+
                 "where a ladder use to lead up. There doesn't seem "+
                 "to be anything of interest up here.\n");

    add_item(({"floor"}), "Several blankets and mats lay there.\n");

    add_item(({"ceiling"}), "It is made of wood, and leaks water in " +
          "several places.\n");

    add_item(({"beds", "bed", "hay", "straw"}), "Several blankets and " +
           "mats were used for beds, but are now scattered.\n");
    add_item("window", "A small window looks back to the main "+
                   "town of Calathin.\n");
    add_cmd_item("down","climb","@@climb");
}
 
int
climb()
{
    write("You climb down out the window to the path below.\n");
    TP->move_living("down", CALATHIN_DIR + "paths/path_n04");

    return 1;
}
