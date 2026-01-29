/*
 *	/d/Gondor/common/quest/enchant_seed/garden.c
 *
 *	Coded 1992 by Elessar.
 *
 *	Modification log:
 *	29-Jan-1997, Olorin:	General revision.
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/herbsearch.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
enter_hut()
{
    write("You decide to visit the person who lives in the hut.\n");
    return 0;
}

public void
create_gondor()
{
    set_short("a small garden outside a hut");
    set_long(BSN("In the middle of the forest, there is a green "
        + "and well kept garden here, surrounding a little wooden "
	+ "hut. Plants and flowers grow in the garden. On the wall "
        + "next to the open door, a couple of new-caught rabbits "
        + "have been salted and hung up to dry. Around the hut the "
	+ "dark Druedain Forest looms. A path leads west into the "
        + "forest."));

    set_up_herbs( ({ HERB_DIR + "lothore", HERB_DIR + "redweed" }),
		  ({ "garden", }), 2);
    add_item("ground", BSN("Plants and flowers and vegetables are "
        + "growing on the ground - the person who lives here has "
        + "kept his garden nicely."));
    add_item("garden","The garden is not really big, only about 10 x 10 meters.\n"+
    "There are plants and flowers growing here, along with vegetables of\n"+
    "various kinds. The garden is surrounded by the forest.\n");
    add_item("flowers","There are nice flowers of several colors growing here, and the\n"+
    "scent of them is refreshening.\n");
    add_item("plants", BSN("There are several plants growing here, "
        + "both vegetables and other kinds, even some that look like herbs."));
    add_item("herbs", BSN("It is hard to see which of the plants are "
        + "herbs and which are not. You will have to search the garden "
        + "for them."));    
    add_item("rabbits","The rabbits look freshly killed, you guess they will be the\n"+
	     "dinner for the hut-occupant tonight.\n");
    add_item("hut","The hut is made of latched lumber, not very big, but solid.\n"+
    "The only entrance is the door on the front side, and it is open.\n");
    add_item("vegetables","These vegetables will probably be a nice addition to the\n"+
    "rabbits for the hut-occupants dinner tonight.\n");

    add_cmd_item( ({ "vegetables", "herbs", "flowers", "rabbits", "plants", }),
		  ({ "get", "take", }), 
		  "You are about to take it when you suddenly feel very "
		+ "ashamed and decide not to take anything.\n");

    set_noshow_obvious(1);

    add_exit(DRUEDAIN_DIR + "forest12",             "north",         0, 1);
    add_exit(DRUEDAIN_DIR + "forest13",             "east",          0, 1);
    add_exit(DRUEDAIN_DIR + "forest11",             "south",         0, 1);
    add_exit(DRUEDAIN_DIR + "forest9",              "west",          0, 1);
    add_exit(COMMON_DIR + "quest/enchant_seed/hut", "enter", enter_hut, 0);
}
