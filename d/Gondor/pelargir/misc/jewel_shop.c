/*
 * Rindul's gem shop in Pelargir
 *
 * Coded by Gwyneth, November 10, 2000
 *
 * 9/14/02 - Added an exit to the jewelry store, Gwyneth.
 */

inherit "/d/Gondor/common/lib/gem_shop";

#include "/d/Gondor/defs.h"

#define STORE_ROOM	(PELAR_DIR + "misc/jewel_store")

public void
init()
{
    ::init();
    init_shop();
}

public void
create_shop()
{
    set_short("Rindul's Gem Store");
    set_long("Not a speck of dust can be found in this little shop, " +
        "despite the many windows that have been set into the thick " +
        "walls. Gem displays have been placed around the store for " +
        "customers to browse through, and a workbench stands out " +
        "of the way against the far wall. A doorway to the west leads " +
        "to a jewelry shop.\n");
    
    set_store_room(STORE_ROOM);
    set_shop_name("Rindul's Gem Store");
    set_keeper_file(PELAR_DIR + "npc/rindul");
    setup_gem_shop();

    add_item(({"floor", "ground"}), "The floor is covered with " +
        "woven rugs.\n");
    add_item(({"rugs", "woven rugs"}), "The skill that has gone " +
        "into each rug could have only come from a master. The " +
        "colours entertwine in patterns that seem to shift under " +
        "your very gaze.\n");
    add_item(({"colours", "patterns"}), "The patterns come together " +
        "every so often, revealing pictures of famous battles, great " +
        "quests and powerful rulers.\n");
    add_item("ceiling", "The ceiling is as clean of cobwebs as the " +
        "ground is of dust.\n");
    add_item(({"workbench", "far wall"}), "The workbench is covered " +
        "with Rindul's tools.\n");
    add_item("tools", "These tools are a necessity for any jeweller.\n");
    add_item(({"window", "windows", "many windows"}), "The windows are " +
        "set to take advantage of the sunlight, in order to " +
        "make the gem displays sparkle. Bars have been set across the " +
        "openings to protect the merchandise when the owner is away.\n");
    add_item(({"walls", "thick walls", "wall"}), "The walls are " +
        "well-made, and not likely to need any repairs in the next " +
        "half-century.\n");
    add_item(({"bars", "metal"}), "The bars are made of a sturdy " +
        "black metal.\n");
    add_item(({"displays", "gem displays", "display", "gems", "gem"}), 
        "Various types of gems have been placed on cushions of velvet for " +
        "display.\n");
    add_item(({"velvet cushions", "cushions", "cushions of velvet"}),
        "Each cushion has one of Rindul's best gems resting upon it.\n");

    add_exit(PELAR_DIR+ "streets/plaza", "south", 0, 0);
    add_exit("/d/Gondor/common/jewelry/jewelry_store", "west");
}

public string
exa_poster()
{
    return "\n"
      + "Welcome to " + shop_name + "!\n"
      + "You can try these instructions: \n"
      + "    buy ruby for gold and get copper back\n"
      + "    buy ruby for gold coins\n"
      + "    sell ruby for copper coins\n"
      + "    sell all  - will let you sell all gems.\n"
      + "    list      - will list all gems in stock.\n"
      + "    value ruby - will give an estimate on the price.\n"
      + "\n";
}

