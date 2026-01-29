/*
 *	/d/Gondor/anorien/nimrais/cave/back.c
 *
 *	December 1995, Olorin
 */
#pragma strict_types

inherit "/d/Gondor/common/room.c";

#include <language.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_room()
{
    set_short("the back of a damp cave");
    set_long(BSN("The roof of the cave is so low that you can only crawl "
      + "here. To the south, the roof is higher, and one can see the light "
      + "from the cave entrance there."));

    add_item(({"ground", "floor", }), BSN("The rock floor is wet here, as "
      + "from rain. There must be water dripping onto it from somewhere "
      + "above."));
    add_item(({"roof", "ceiling", }), BSN("The roof is so low that you can "
      + "only crawl here. There is water dripping to the ground from it, "
      + "but you cannot see where the water comes from."));
    add_item(({"water", }), "@@exa_water@@");
    add_item(({"entrance", "exit", }), BSN("All you can see of the entrance "
      + "into the cave is a distant circle of light which does not admit "
      + "enough light to penetrate the shadows here in the back of the cave."));
    add_item(({"hole", "tunnel", }), BSN("The hole in the roof is leading "
      + "out of the cave into a tunnel above the cave. From down here, it "
      + "is impossible to see more of the tunnel, but it seems to be climbing "
      + "at a steep angle."));

    add_cmd_item(({"hole", "tunnel", "into hole", "into tunnel", "through hole", }),
        ({ "climb", "enter", }), "@@enter_tunnel@@");
    add_exit(ANO_DIR + "nimrais/cave/entrance", "south", "@@south_msg@@", 1);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT,  0);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(OBJ_I_SEARCH_TIME, 5);
}

public string
do_search(object tp, string str)
{
    object  obj;

    if (!objectp(tp) || !present(tp, TO))
        return 0;
    if (!strlen(str))
        return 0;

    str = LOW(str);
    switch (str)
    {
    case "water":
    case "roof":
    case "ceiling":
        return BSN("Wondering where the water that is dripping from "
          + "the roof comes from, you grope at the rock above you. "
          + "You notice that there is a narrow hole in the black "
          + "rock leading upwards. You might be able to climb up "
          + "into that tunnel.");
        break;
    default:
        return 0;
        break;
    }
}

public string
exa_water()
{
    string  result = do_search(TP, "water");

    if (!strlen(result))
        return "The water is dropping from the rock roof down onto the "
          + "floor of the cave.\n";
    return result;
}

public int
south_msg()
{
    write("You crawl back south into the main part of the cave, "
      + "where you stand up again.\n");
    return 0;
}

public int
enter_tunnel()
{
    switch ( (ANO_DIR + "nimrais/cave/tunnel2")->query_heap_state() )
    {
    case 0:
        write("You climb through the hole in the roof of the cave.\n");
        set_dircmd("tunnel");
        TP->move_living("up", (ANO_DIR + "nimrais/cave/tunnel1"));
        break;
    case 1:
    case 2:
        write("Judging from the tremendous roar and dust coming from above "
          + "there is a rock avalanche coming down a tunnel above the hole.\n"
          + "Better run instead of climbing into that tunnel!\n");
        break;
    case 3:
    default:
        write("You try to enter the hole in the roof, but you "
          + "find that it is completely blocked by rocks.\n");
        break;
    }
    return 1;
}

public void
clean_up()
{
    FILTER_DEAD(all_inventory(TO))->remove_object();
}

public void
cavein()
{
    int     sl,
            i;
    object *liv;

    tell_room(TO, "A large number of rocks and stones comes "
      + "falling down from above.\n");
    tell_room(ANO_DIR + "nimrais/cave/entrance",
        "A tremendous roar and a dense could of dust comes from the "
      + "back of the cave.\n"
      + "It sounds as if an avalanche of rocks and stones has gone "
      + "down there, burying everything in that part of the cave.\n");

    liv = FILTER_LIVE(all_inventory(TO));

    for (i = 0, sl = sizeof(liv); i < sl; i++)
        if (random(liv[i]->query_stat(SS_DIS)) < liv[i]->query_whimpy())
            liv[i]->run_away("south");

    tell_room(TO, "You are buried beneath the rocks.\n");
    liv = FILTER_LIVE(all_inventory(TO));
    for (i = 0, sl = sizeof(liv); i < sl; i++)
    {
        liv[i]->heal_hp(- (liv[i]->query_max_hp() + 1));
        liv[i]->do_die(TO);
        if (interactive(liv[i]))
            log_file("traps", liv[i]->query_name() + " killed by rock "
              + "avalanche in "+file_name(TO)+" at "+ctime(time())+".\n");
    }

    set_alarm(1.0, 0.0, clean_up);
}

