/* oldgarden3.c */
/* janus 920929 */
/*
    Modified: 30 Apr 2003, by Bleys
        - fixed a typo
*/

inherit "/d/Terel/common/town/mansion/grd/ogrd_std_room";
#include "/d/Terel/common/terel_defs.h"

#define ITEMS    ({"gem", "mortar", "dagger", 20})

void
create_ogrd_room()
{
    set_short("overgrown shed");
    set_long("Around you see the overgrown remains of a small shed, "+
        "maybe a gardeners shed. "+
        "The air is cold, humid, and permeated by a smell of rotting "+
        "plants and flesh. The rotting, and decaying shed is covered by a "+
        "thin layer of frost and entwined vines. "+
        "The garden of appears to continue to the north, and "+
        "east. To the south you can see the old mansion. The way to the east "+
        "is blocked by a rusty barbed iron fence. "+
        " Thorn bushes and small deformed trees have grown totally"+
        " out of control, almost blocking the paths. "+
        "\n");
    add_exit(MANSION + "grd/ogrd31.c", "north","@@gogo",3);
    add_item(({"fireplace","old fireplace"}), "It's surprising that the "+
               " fireplace is still standing considering its condition.\n");
    add_exit(MANSION + "grd/ogrd1.c", "west","@@gogo",3);
    add_item(({"shed","overgrown shed","ruins"}),
               "Not much is left of the shed, only the fireplace and some "+
               " planks are left. Scraps of old gardening tools are lying "+
               " among the debris of the shed.\n");
}

mixed *
setup_search()
{
    return ITEMS;
}
