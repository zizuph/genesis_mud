/* This file is /d/Gondor/rohan/edoras/garden.c            */
/* Olorin, Jan 1993                                        */

inherit "/d/Gondor/common/lib/town";
inherit "/d/Gondor/common/lib/herbsearch";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Gondor/defs.h"

void
create_room() 
{
    set_hillside("west");
    set_height(1);
    set_road(0);
    set_density(1);
    set_extraline("This is a garden. You can see beds with flowers and herbs, "
      + "bushes and fruit trees. The garden is so full of different herbs, "
      + "flowers, and fruits that you have problems making out any one crop. "
      + "The city wall surrounds the garden on all sides but to the "
      + "southeast.");
    add_exit(EDORAS_DIR + "well","southeast",0);

    set_up_herbs(({SHIRE_HERB_DIR + "parsley",
                   SHIRE_HERB_DIR + "huckleberry",
                   SHIRE_HERB_DIR + "pawnrose",
                   SHIRE_HERB_DIR + "grass",
                   HERB_DIR + "lothore",
                   HERB_DIR + "redweed",
                   HERB_DIR + "attanar",
                   HERB_DIR + "garlic",
                   HERB_DIR + "curugwath", }),
                 ({"garden", }), 5);

    add_item("garden",BSN("The garden is full of herbs, flowers, and "
      + "fruits. Almost any crop known in Rohan seems to be grown here."));
    add_item("flowers",
        BSN("Lots of wonderful flowers. But cannot make out any kind "
      + "that you know."));
    add_item("herbs",
        BSN("All the herbs known to the Rohirrim have been planted here."));
    add_item("vegetables",
        BSN("The vegetables here are not ripe yet. Therefore, you are not "
      + "interested in them."));
    add_item("fruits",
        BSN("The fruit trees either have already been harvested or the fruit "
      + "are not ripe yet. But perhaps the bushes carry some berries."));
    add_item("bushes",
        BSN("All around the garden are all kinds of different bushes. "
      + "Probably most of them carry some kind of berries."));
    add_item(({"wall","walls","city wall"}),
        BSN("The city wall is made from big solid stones. It is well "
      + "guarded and definitely impossible to climb."));
 
    make_the_room();
}

void
reset_room()
{
    set_searched(-5);
}
