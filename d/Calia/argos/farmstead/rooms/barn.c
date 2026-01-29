/* /d/Calia/argos/farmstead/rooms/barn.c
**   Barn in the farmyard outside of Argos
**   It contains some items necessary to complete the farmstead quest
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
int skull_taken;
int gravel_searched;
string *remains_strings = ({ "skeleton", "remains", "skeletal remains" });
string *pile_strings = ({
    "pile", "gravel", "gravel pile", "pile of gravel", "rock", "rock pile",
    "gravel rock", "pile of gravel rock", "pile of gravel rocks", "rocks"
});

void
create_room()
{
    seteuid(getuid());

    set_short("Inside a ruined barn");

    set_long(
        "This is the inside of a ruined barn - although considering "
        + "most of the roof is collapsed and one of the walls has fallen "
        + "over, calling it inside might be a bit of a stretch. Small pens "
        + "and troughs line the walls, but no livestock appears to have set "
        + "trotter here for some time. In one of the corners is a pile of "
        + "gravel rock, and in another corner lies what appears to be the "
        + "skeletal remains of a human.\n"
    );

    add_prop(OBJ_S_SEARCH_FUN, "search");

    add_item(
     remains_strings,
        "These are the skeletal remains of a human. They lie in a hunched "
        + "over position, and appear to have been smashed quite badly from "
        + "a wooden beam collapsing atop them. @@skeleton_desc"
    );

    add_item(
        ({ "beam", "wooden beam" }),
        "A wooden beam has fallen down, apparently ending the life of some "
        + "poor soul as they did.\n"
    );

    add_item(
        pile_strings,
        "A large pile of finely crushed gravel rock. @@gravel_desc"
    );

    add_item(
        ({ "barn", "ruined barn" }), long()
    );

    add_item(
        ({
            "roof", "straw roof", "thatched straw", "straw", "thatched straw "
            + "roof", "ceiling"
        }),
        "It is a thatched straw roof, half of which seems to have collapsed "
        + "or disappeared with the wind.\n"
    );

    add_item(
        ({ "wall", "walls", "south wall" }),
        "The south wall has tipped over, but the other walls are still "
        + "standing. If barely...\n"
    );

    add_item(
        ({ "corner", "corners" }),
        "In one of the corners is a pile of gravel rock, and in another "
        + "corner lies what appears to be the skeletal remains of a human.\n"
    );

    add_item(
        ({
            "pen", "pens", "barrier", "wooden barrier", "barriers", "wooden "
            + "barriers"
        }),
        "Simple wooden barriers form pens along the walls.\n"
    );

    add_item(
        ({ "trough", "troughs", "wooden trough", "wooden troughs" }),
        "Sturdy, wooden troughs line the walls in the pens.\n"
    );

    add_item(
        ({ "stool", "broken stool" }),
        "A wooden three-legged stool. The wood is rotten and one leg is "
        + "broken clean off.\n"
    );

    add_item(
        "wood",
        "The wood compromising the stool is grey and rotten.\n"
    );

    add_item(
        ({ "leg", "legs", "broken leg" }),
        "The stool is missing one leg.\n"
    );

    add_exit(ROOM_DIR + "farmyard", "out");

    reset_room();
}

void
reset_room()
{
    skull_taken = 0;
    gravel_searched = 0;
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
    if (member_array(search_term, remains_strings) != -1 && !skull_taken)
    {
        skull_taken = 1;
        object skull = clone_object(OBJ_DIR + "skull");
        skull->move(TP, 1);
        return "You find a "+ skull->short() + "!\n";
    }

    if (member_array(search_term, pile_strings) != -1 && !gravel_searched)
    {
        gravel_searched = 1;
        object pebbles = clone_object(OBJ_DIR + "pebbles");
        pebbles->move(TP, 1);
        return "You find a " + pebbles->short() + "!\n";
    }

    return "";
}

/*
 * Function name: skeleton_desc
 * Description  : Display information to the examining player based on whether
 *                the skull of the remains has been removed since last room
 *                reset or not.
 * Returns      : The string to be displayed to the player
 */
string
skeleton_desc()
{
    return skull_taken
        ? "It seems that someone has very recently removed the skull.\n"
        : "Maybe you should search them?\n";
}

/*
 * Function name: gravel_desc
 * Description  : Display information to the examining player based on whether
 *                the pile of gravel has been searched since last room reset
 * Returns      : The string to be displayed to the player
 */
string
gravel_desc()
{
    return gravel_searched
        ? "It seems to have been searched very recently.\n"
        : "Maybe you should search it?\n";
}
