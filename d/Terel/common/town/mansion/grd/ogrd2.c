/* oldgarden2.c */
/* janus 920929 */
/*
    Modified: 6 May 2003, by Bleys
        - Modified the ITEMS array to use full paths.

*/

inherit "/d/Terel/common/town/mansion/grd/ogrd_std_room";
#include "/d/Terel/common/terel_defs.h"

#define ITEM_DIR    MANSION + "grd/"
#define ITEMS    ({ITEM_DIR + "bag", 5})

void
create_ogrd_room()
{
    set_short("garden");
    set_long("You are in a overgrown part of an old decrepit garden" +
        ". The air is cold, humid, and permeated by the smell of rotting "+
        "plants and flesh. The ground is covered by a thin layer of frost "+
        "and entwined vines. A small rounded bump is all that remains of "+
        "an old earthen cellar. "+
        "The garden of despairs appears to continue to the north, and "+
        "east. To the south you can see the old mansion. The way to the west "+
        "is blocked by a rusty barbed iron fence. "+
        " Thorn bushes and small deformed trees have grown totally"+
        " out of control, almost blocking the paths. "+
        "\n");
    add_exit(MANSION + "grd/ogrd21.c", "north", "@@gogo", 3);
    add_exit(MANSION + "grd/ogrd1.c", "east", "@@gogo", 3);
    add_exit(MANSION + "grd/cellar.c", "down", "@@gogo", 3);
    add_item("fence", "Although quite rusty, the fence's barbed wire forms "+
         "an impassable barrier to the west.\n");

}

mixed *
setup_search()
{
    return ITEMS;
}
