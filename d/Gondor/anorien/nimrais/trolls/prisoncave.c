/*
 * /d/Gondor/anorien/nimrais/trolls/prisoncave
 *
 * Coder: Unknown
 *
 * Modification log:
 * Gwyneth, 10/02/02: Cleaned up, changed inheritance
 *
 * -- Toby, 10th-Sept-2007: Fixed a typo
 */
inherit "/d/Gondor/std/room";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public int blocked();

public void
create_gondor()
{
    set_short("the prison-cave in the hill-troll lair");
    set_long("This is the dark and gloomy cave where the hill-trolls keep " +
        "their captives. Chains and shackles are hanging from the walls, " +
        "and bones and skulls litter the floor, indicating the demise of " +
        "a poor adventurer. There is a tunnel leading west, and another " +
        "leading north.\n");

    remove_prop(ROOM_I_LIGHT);
    add_prop(ROOM_I_INSIDE, 1);

    add_exit(NIMRAIS_DIR + "trolls/livcave", "north", &blocked());
    add_exit(NIMRAIS_DIR + "trolls/foodcave", "west");
    add_item(({ "bones", "skulls", "bone", "skull" }),
        "The bones and skulls littered about the floor are the remains " +
        "of unlucky adventurers seeking their fortune near the " +
        "hill-trolls lair. The large number of bones indicate that the " +
        "trolls have been well-fed lately.\n");
    add_item(({ "chains", "shackles" }),
        "There are chains and shackles here, fastened to the cave. " +
        "They were probably used to hold the hill-trolls' future " +
        "meals while they were fed and fattened to make good meals " +
        "for the trolls.\n");
    add_item(({ "ground", "floor" }),
        "The ground is littered with gnawed bones and skulls. A thin " +
        "stream of water disappears in the darkness of the back of the " +
        "cave.\n");
    add_item( ({ "water", "stream" }),
        "The thin stream of water comes trickling into the cave from the " +
        "west and disappears into the shadows in the back of the cave.\n");
    add_item(({ "back", "shadows", "darkness" }),
        "The shadows in the back of the cave are impenetrable. The " +
        "roof of the cave is hanging low there so it is impossible to " +
        "enter the back of the cave.\n");
}

public int
do_crawl(string str)
{
    if (!strlen(str))
    {
        notify_fail("Crawl where?\n");
        return 0;
    }

    str = LOW(str);

    if (!parse_command(str, ({}),
      "[further] [in] [into] [the] [back] [of] [the] 'cave' / 'darkness' / 'shadows'"))
    {
        notify_fail("Crawl where?\n");
        return 0;
    }

    write("You crawl into the back part of the cave.\n");
    TP->move_living("crawling into the back of the cave",
        NIMRAIS_DIR + "trolls/tunnel");
    return 1;
}

public int
blocked()
{
    object troll = present("troll", TO);

    if (objectp(troll) && CAN_SEE(troll, TP)  && !TP->query_npc())
    {
        write("The " + troll->query_nonmet_name() + " stops you!\n");
        return 1;
    }

    return 0;
}

public void
init()
{
    ::init();

    add_action(do_crawl, "crawl");
}
