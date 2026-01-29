/* This is a room in the elemental area northeast of the
frog pond in Calia. By Bishop, 5.2.99 */

inherit "/std/room";

#include <stdproperties.h>
#include <ss_types.h>
#include <pond.h>
#include <macros.h>

public string blocked();

create_room()
{
    set_short("Path through the forest");

    set_long("You are making your way through the forest on a" +
        " narrow path, avoiding the occasional thorny bush" +
        " and stepping over the odd log. This route seems as if" +
        " it hasn't been travelled for years, yet it is clear" +
        " enough to follow. You hear a very faint rumbling from" +
        " the north.@@blocked@@\n");

    add_item(({"forest", "trees"}), "The forest consists of" +
        " maple, oak and sassafras trees. They're not too densely" +
        " packed, allowing sunlight to filter in.\n");
    add_item("sunlight", "The light feels warm on your skin.\n");
    add_item("bush", "Few of the bushes obstruct the path, but you" +
        " have to step out of the way sometimes to avoid getting" +
        " prickled by thorns.\n");
    add_item("log", "The logs you see are from fallen trees.\n");
    add_item(({"path", "route"}), "This path seems unnaturally" +
        " smooth and free of vegetation given the lush" +
        " surroundings. It looks untravelled.\n");

    add_prop(ROOM_I_HIDE, 90);
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(FPATH + "env_hot_springs", "northeast", 0, 1);
    add_exit(FPATH + "epath1", "south", 0, 1);
}

string
blocked()
{
    if (find_object(FPATH + "epath1")->query_prop(CALIA_I_PATH_BLOCKED))
    {
        return " The path south is blocked by a mass of bushes" +
            " and brambles, yet you feel you can pass.";
    }
    else
    {
        return "";
    }
}