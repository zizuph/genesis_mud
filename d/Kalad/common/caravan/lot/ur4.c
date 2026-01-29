#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    add_prop(ROOM_I_LIGHT, 0);

    add_prop(ROOM_S_DARK_LONG, "A dark place beneath the city.\n");

    set_short("An underground intersection");
    set_long("You've reached a small intersection.\n"+
      "You can barely see inside this dark intersection. Visible "+
      "upon the ground are reeking piles of filth, while dozens of crawling "+
      "bugs are on the walls and ceiling. Dark passages lead away from here "+
      "in all the cardinal directions, save for the east.\n");

    add_item(({ "filth" }),
      "Its so disgusting that it can't be adequately described. It lies "+
      "all over this intersection in stinking piles.\n");

    add_item(({ "walls", "ceiling", "wall" }),
      "This passage is made entirely of mud, wholly unsupported by anything. "+
      "You fully expect the entire passage to collapse in upon you, causing "+
      "your slow and suffocating death as thousands of pounds of mud "+
      "slowly cover you...\n");

    add_item(({ "bugs" }),
      "Dozens of filthy and disgusting cockroaches, centipedes and other nasty "+
      "critters can be seen all over this passageway.\n");

    set_noshow_obvious(1);

    add_exit(CVAN + "lot/ur1", "west");
    add_exit(CVAN + "lot/ur3", "north");
    add_exit(CVAN + "lot/ur5", "south");
}
