/* oldgarden1 1.c */
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
// #define ITEMS   ({"sword", "gem", "bag", 20})
#define ITEMS   ({ \
                    ITEM_DIR + "sword", \
                    GEM_DIR + "turquoise", \
                    ITEM_DIR + "bag", \
                    20 \
                 })

void
create_ogrd_room()
{
  set_short("crossroad");
  set_long("Three small paths converge here, otherwise this place "+
          "seems normal. The air is cool, humid, and has a tang of of rotting "+
          "plants and flesh. "+
          "To the west and north you can see the rusty and barbed iron fence "+
          "that surrounds this garden."+
          " Thorn bushes and small deformed trees have grown totally"+
          " out of control, almost blocking the paths. "+
          "\n");
  add_exit(MANSION + "grd/ogrd1.c", "south","@@gogo",3);
  add_exit(MANSION + "grd/ogrd21.c", "west","@@gogo",3);
  add_item(({"fence","iron fence"}),
       "A high fence surrounding the garden. Although rusted "+
          "the barbs on the fence seems very sharp.\n");
}

mixed *
setup_search()
{
    return ITEMS;
}
