/* oldgarden21.c */
/* janus 921021 */
/*
    Modified: 6 May 2003, by Bleys
        - Modified the ITEMS array to use full paths.

*/

inherit "/d/Terel/common/town/mansion/grd/ogrd_std_room";
#include "/d/Terel/common/terel_defs.h"

#define ITEM_DIR    MANSION + "grd/"
// #define ITEMS    ({"sword", "helmet", "dagger", 30})
#define ITEMS   ({ \
                    ITEM_DIR + "sword", \
                    ITEM_DIR + "helmet", \
                    ITEM_DIR + "dagger", \
                    30 \
                 })

void
create_ogrd_room()
{
    set_short("overgrown pond");
    set_long("Mostly covered by vines a growing bushes you see a pond. "+
        "The air is cold, humid, and permeated by a smell of rotting "+
        "plants and flesh. There is a thin layer of ice covering the "+
        "foulsmelling water. "+
        "To the west and north you can see the rusty and barbed iron fence "+
        "that surrounds this garden."+
        " Thorn bushes and small deformed trees have grown totally"+
        " out of control, almost blocking the paths. "+
        "\n");
    add_exit("/d/Terel/common/town/mansion/grd/ogrd2.c", "south","@@gogo",3);
    add_exit("/d/Terel/common/town/mansion/grd/ogrd11.c", "east","@@gogo",3);
    add_item(({"pond"}),
               "There seems to be nothing special about the pond. "+
                  "A small statue is standing in the middle of it.\n");
    add_item(({"statue"}),
               "A small stone statue portraying a water nymph.\n");
}

mixed *
setup_search()
{
    return ITEMS;
}
