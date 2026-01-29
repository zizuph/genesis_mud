inherit "/d/Gondor/common/lib/town";
inherit "/d/Gondor/common/lib/herbsearch";

#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"

void
create_room()
{
    set_road(0);
    set_height(1);
    set_hillside("west");
    extraline = "This is a small house with a small garden upfront. "
      + "The garden looks well kept and you can see a few flowers in "
      + "it.";
/*
    set_short("a small house");
    set_long(BSN("This is a small house with a small garden upfront. "
        + "The garden looks well kept and you can see a few flowers in "
        + "it."));
*/
    add_item(({"garden","small garden"}),BSN("There are a few flowers "
        + "growing in the garden."));
    add_item(({"flowers","flower"}),BSN("They are beatiful flowers, you "
        + "dont dare to pick any of them."));
    add_item(({"house", "small house"}),BSN("The house looks well built "
        + "and well kept. The owner must be a handy man who takes care "
        + "of his property with great concern."));

    add_exit(EDORAS_DIR + "houses/house1r1","west",0);

    set_up_herbs(({HERB_DIR + "basil",
                   HERB_DIR + "lothore",
                   HERB_DIR + "garlic",
                   HERB_DIR + "dill",
                   HERB_DIR + "chervil", }),
                 ({"garden", "flower", "flowers", }),
                 4);

    make_the_room();
}

void
reset_room()
{
    set_searched(0);
}
