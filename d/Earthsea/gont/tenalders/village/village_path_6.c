/*
 * coded by Amelia 6/1/97
 * path through Ten Alders
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/std/room";

#include <stdproperties.h>
#include <ss_types.h>

private int found;

public void
create_earthsea_room()
{
    set_short("Village path");
    set_long("A gravel path. The path winds among several " +
        "thatch-covered huts that comprise this small " +
        "village, situated on a somewhat more level area of " +
        "the mountain side. The path leads northeast into " +
        "the village. There is a small smoke-blackened hut " +
        "just to the east, but there is no entrance on this " +
        "side. A heap of junk is piled against the hut.\n");
    add_prop(OBJ_S_SEARCH_FUN, "find_horseshoe");
    add_prop(OBJ_I_SEARCH_TIME, 6);
    add_item((({"path", "gravel path"})),
        "The path winds among several huts in this little " +
       "village.\n");
    add_item((({"huts", "thatch-covered huts", "village"})),
        "This is but a small village set on the steep " +
        "mountainside and comprised of just a few thatch-covered " +
        "peasant huts.\n");
    add_item((({"trash", "heap", "small heap of trash",
        "metal", "junk", "junk metal", "heap of trash"})),
        "There is a small heap of junk or trash piled by the " +
        "side of the path.\n");
    add_exit("village_path_5", "northeast");
}

public void
reset_room()
{
    found = 0;
}

public string
find_horseshoe(object player, string str)
{
    object shoe;

    if(found)
    {
        return "You find nothing of interest there.\n";
    }

    if(str == "junk" || str == "trash" || str == "heap" ||
        str == "heap of trash" || str == "small heap of trash" ||
        str == "junk" || str == "junk metal")
    {
        if(player->query_skill(SS_AWARENESS) > 15)
        {
            shoe = clone_object("/d/Earthsea/gont/tenalders/obj/items/horseshoe");
            shoe->move(player);
            found = 1;
            return "You found a piece of junk iron!\n";
        }
    }

    return "You find nothing of interest.\n";
}
