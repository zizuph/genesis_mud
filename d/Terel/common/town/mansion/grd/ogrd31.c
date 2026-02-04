/* oldgarden31.c */
/* janus 920929 */
/*
    Modified: 6 May 2003, by Bleys
        - Modified the ITEMS array to use full paths.
        - Modified the ITEMS array to use standard gems.

*/

inherit "/d/Terel/common/town/mansion/grd/ogrd_std_room";
#include "/d/Terel/common/terel_defs.h"

#define ITEM_DIR    MANSION + "grd/"
#define GEM_DIR     "/d/Genesis/gems/obj/"
// #define ITEMS    ({"hgem", "hgem", "dagger", 40})
#define ITEMS ({ \
                GEM_DIR + "ruby", \
                GEM_DIR + "ruby", \
                ITEM_DIR + "dagger", \
                40 \
                })

void
reset_room()
{
    NOOFPLANTS = 3;
    NOOFTOOLS = sizeof(setup_search());
    if (skull) skull = 0;
    BIGMAMA = 1;
}

void
create_ogrd_room()
{
    set_short("dump");
    set_long("This must be the place where all refuse from all inhabitants "+
       " of the mansion is dropped. All around you see piles of refuse. "+
       "The air is warmer here but the stench from the refuse piles is almost"+
       " unbearable. The vines covering the ground here seems unusually thick."+
       " To the south you can see the ruins of an old shed and the way "+
       "to the east is blocked by a rusty barbed iron fence. "+
        "\n");
    add_exit(MANSION + "grd/ogrd3.c", "south", "@@gogo", 3);
    add_exit(MANSION + "grd/ogrd32.c", "north", "@@gogoN", 5);
    add_exit(MANSION + "grd/ogrd11.c", "west", "@@gogo", 3);
    add_item(({"fence","iron fence"}),
               "The rusted fence is about 3 meters high and has very sharp "+
                  "barbs, making it too difficult to climb it.\n");
    add_item(({"pile","refuse pile","refuse","refuse piles","piles"}),
               "The refuse piles are about two to three meters high and "+
               "about four to six meters across. You can see wisps of warm "+
               "air coming from the piles.\n");
}

mixed *
setup_search()
{
    return ITEMS;
}
