/*
 * coded by Amelia 3/16/97
 * old forest room north of Ten Alders
 * specials:  room_tell.c and search for herbs
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/gont/tenalders/std/base_forest_room";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Earthsea/herbs/herb_sets/forest_herbs.h"

#define PASSAGE_DESC if(find_exit) return "The briars have been " + \
    "moved back, creating a small hole that could be entered.\n"

private int find_exit = 0;

public void
remove_it()
{
    if(find_exit == 1)
    {
        tell_room(this_object(), "The branches gradually move back over the " +
            "passageway hiding it from view.\n");
        remove_exit("enter");
        find_exit = 0;
    }

    return;
}

public void
create_forest_room()
{
    set_short("An ancient evergreen forest");
    set_long("Tall trees of the ancient evergreen forest " +
        "stand around you, scenting the crisp mountain air " +
        "with fresh pine. The forest floor is covered with dense " +
        "tangled briars and bushes. A rugged path, carpeted with " +
        "pine needles, ascends the mountain, winding among the " +
        "vegetation and rocks.\n");
    add_item((({"briars", "briar patch"})),
        "The briar patch is a thick tangle of thorns, however, " +
        "you notice a patch of fur on one of the vines.\n");
    add_item((({"floor", "forest floor"})),
        "The forest floor is fairly steep, and it is " +
        "difficult to walk here.\n");
    add_item("path",
        "The rugged path winds among large rocks and bushes.\n");
    add_item("passage", "@@passage_desc");
    add_item("passageway", "@@passageway_desc");
    add_item("hole", "@@hole_desc");
    set_up_herbs(select_herb_files(FOREST_HERBS),
        FOREST_LOCATIONS, 3);
    reset_room();
    add_prop(OBJ_S_SEARCH_FUN, "find_briars");
    add_prop(OBJ_I_SEARCH_TIME, 5);
    add_exit("n7", "northeast");
    add_exit("n5", "south");
}

public string
find_briars(object player, string str)
{
    object tp = this_player();
    int hp = MAX(-150, tp->query_max_hp() / 5 * -1);

    if(str == "briars" || str == "briar patch")
    {
        if(!find_exit)
        {
            add_exit("briars", "enter");
            tp->heal_hp(hp);
            tp->catch_tell("Ouch! you poke your finger on a thorn.\n");
            find_exit = 1;
            set_alarm(30.0, 0.0, remove_it);
            return "You break a hole through the briars, revealing a " +
                "small passage!\n";
        }

        return "You search the briars and see that there is " +
            "a small passage you may enter.\n";
    }

    return herb_search(player, str);
}

public string
passage_desc()
{
    PASSAGE_DESC;
    return "You find no passage.\n";
}

public string
passageway_desc()
{
    PASSAGE_DESC;
    return "You find no passageway.\n";
}

public string
hole_desc()
{
    PASSAGE_DESC;
    return "You find no hole.\n";
}
