/* /d/Calia/argos/farmstead/rooms/toolshed.c
**   A toolshed at the farmstead east of Argos
**   Here may be found certain items to solve the quest on the
**   farmstead.
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   2/21/20    Brine      Created
**
*/

#pragma strict_types

inherit  "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

// variables
int tools_searched;
int scrap_searched;
string* tool_strings = ({ "tool", "tools", "farming tools" });
string* scrap_strings = ({
    "scrap", "scraps", "metal", "scrap metal", "heap", "heap of scrap metal",
    "rusted scrap metal", "heap of rusted scrap metal", "heap of scrap",
    "heap of metal", "metal scraps"
});

void
create_room()
{
    seteuid(getuid());

    set_short("Inside a toolshed");

    set_long(
        "You are inside of a run-down toolshed. Looking at the rotten "
        + "wooden boards of the leaning walls, you get the impression that "
        + "you probably shouldn't sneeze too hard in here.\nSome tools "
        + "are hanging along the walls, and there is a heap of scrap metal "
        + "in one of the corners.\n"
    );

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    add_prop(OBJ_S_SEARCH_FUN, "search");

    add_item(({ "shed", "toolshed", "tool shed" }), long());

    add_item(
        ({
            "board", "boards", "wooden boards", "wood", "floorboards",
            "floor boards"
        }),
        "The wooden boards compromising the walls, roof and floor are rotten "
        + "and grey of colour. Clearly they have not been maintained in "
        + "a long time.\n"
    );

    add_item(
        ({ "corner", "corners" }),
        "There is a heap of scrap metal in one of the corners.\n"
    );

    add_item("dust", "Dust covers everything in here.\n");

    add_item(
        ({
            "wall", "walls", "roof", "leaning walls", "ceiling", "floor",
            "ground"
        }),
        "The walls, floor and roof are made of wooden boards that have seen "
        + "better days. The entire shed is leaning markedly to the west, but "
        + "it is still standing - if barely.\n"
    );

    add_item(
        ({ "shed", "toolshed", "tool shed" }),
        "@@long"
    );

    add_item(
        tool_strings,
        "They are various farming tools, and they seem to be in poor "
        + "condition. You could search them to try and find anything "
        + "that is still useful.\n"
    );

    add_item(
        scrap_strings,
        "It is a heap of rusted scrap metal, covered in dust. You could "
        + "search it to try and find anything that is still useful.\n"
    );

    add_exit(ROOM_DIR + "farmyard", "out");

    reset_room();
}

void
reset_room()
{
    tools_searched = 0;
    scrap_searched = 0;
}

/*
 * Function name: search
 * Description  : Handles custom search functionality to find quest related
 *                items in the room.
 * Arguments    : string search_term - What is searched for
 * Returns      : string msg - Message displayed to the player, or an empty
 *                string to defer handling to the standard functionality
 */
string
search(object player, string search_term)
{
    if (member_array(search_term, scrap_strings) != -1)
    {
        if (scrap_searched)
        {
            return "It appears that someone has already taken all the useful "
                + "scraps!\n";
        }
        scrap_searched = 1;
        object bucket = clone_object(OBJ_DIR + "bucket");
        bucket->move(this_player(), 1);
        return "You find a " + bucket->short() + " among the scraps!\n";
    }
    if (member_array(search_term, tool_strings) != -1)
    {
        if (tools_searched)
        {
            return "It appears that someone has already taken all the useful "
                + "tools!\n";
        }
        tools_searched = 1;
        object scythe = clone_object(WEAPON_DIR + "scythe");
        scythe->move(this_player(), 1);
        return "You find a " + scythe->short() + " among the tools!\n";
    }
    return "";
}

/*
 * Function name: do_sneeze
 * Description  : A small joke playing on the room description saying that
 *                it probably isn't safe to sneeze in here. Mask the sneeze
 *                command and tell the player that they're very brave :)
 * Returns      : int 1 - success (To stop the regular sneeze command)
 */
int
do_sneeze()
{
    write("Brave one, aren't you? Bless you!\n");
    tell_room(
        this_object(),
        QCTNAME(this_player()) + " bravely lets loose a sneeze.\n",
        this_player()
    );
    return 1;
}

void
init()
{
    ::init();
    add_action(do_sneeze, "sneeze");
}
