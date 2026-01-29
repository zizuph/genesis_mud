// ROOM:  base_side.c

    /*  Calia Domain

    HISTORY

    [99-06-19] created by Uhclem from
    [D:\CALIA\CENTRAL\BOG\INNER\MIDDLE\BASE_SID.DOC].

    PURPOSE

    This is the base for interior rooms on the sides at the middle level of the
    Sanctimonian fortress.  The fortress is octagonal; there are eight rooms at
    the corners and eight at the side at this level.  The side rooms are either
    barracks or baths; the control code supplied by the central control room
    decides the placement of the two baths (men's and women's, of course).  The
    key feature of barracks rooms is that they connect to corner stairways
    going up but not to those going down; baths do not connect to corner rooms
    on this level at all but instead have their own stairs leading straight
    down.  Only two corners have staircases leading down.  The placement of
    down staircases, barracks, and baths depends upon the control code and
    varies with each rebuilding (reloading) of the fortress.

    */

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/central/bog/baseroom";

#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <language.h>
#include <filter_funs.h>
#include "defs.h"

// GLOBAL VARIABLES

string This_Location;

// FUNCTIONS

// Function:  enter_inv(object, from_object)

/*

Purpose:  register a player (or foreign npc) with the Sanctimonian control
room.

Arguments:  object entering the room, object from whence it came.

Returns:  nothing.

*/

void
enter_inv(object ob, object from)

{

    ::enter_inv(ob, from);

    if (living(ob) && !ob->sanctimonian()) register_player(ob);

}

// Function:  create_side(location, *adjacent_rooms, side)

/*

Purpose:  Create the room description and add standard attributes.  The control
code determines which two corner rooms have down staircases.  We attach exits
to all corner rooms except those two.

Arguments:  string containing the filename of this room, string array
containing filenames of adjacent rooms, string indicating which side of the
fortress this room is on.

Returns:  nothing.

*/

void
create_side(string location, string *adjacent_rooms, string side)

{

    /*
     *  The control code is a general-purpose randomly generated number from 0 
     *  to 999.  It is generated whenever the central bog control room is
     *  loaded and the same value is passed to all other bog rooms.    
     */

    int control_code = query_control_code();
    int stair_position = ((control_code % 4) * 2) + 1;

    This_Location = location;

    /*
     *  The baths are on the east and west sides of the fortress when 
     *  (control_code % 4) is 0 or 1.  Adjacent rooms exist to the north and
     *  south, but to isolate them from the staircases we prevent the addition
     *  of any north or south exits.  Similarly, when (control_code % 4) is 2
     *  or 3, baths are on the north and south sides, and we prevent east and
     *  west exits.  If the following test is true, this room is a bath, and
     *  the only exit we'll add is "down."    
     */

    if ((side == "north" || side == "south") && (control_code % 4) < 2 ||
        (side == "east" || side == "west") && (control_code % 4) > 1)

    {

        /*
         *  The following test makes sure that there's one men's and one 
         *  women's bath. They're nearly identical, but they're identified by
         *  signs outside so that it's reasonable to put a clear indication in
         *  the description.  Just to keep things interesting, we use the
         *  control_code to place the men's and women's baths.    
         */

        /*
         *  Note: add distinctive hook_smelled effects for each bath.    
         */

        if ((control_code % 2) && (side == "north" || side == "east") ||
            !(control_code % 2) && (side == "south" || side == "west"))

        {

            set_short("Men's bath");

            set_long("Cast iron tubs line a wall ventilated" +
                " with many round holes, and along the opposite" +
                " wall are a couple of small coal stoves" +
                " and shelves with kettles and jugs.\n");

            add_item(({"shelves", "opposite wall"}),
                "On the shelves you see jugs for carrying" +
                " water, kettles for heating it, neatly" +
                " folded towels, cakes of white soap," +
                " small brushes, and straight razors.\n");

            add_item(({"jugs", "kettles", "towels", "soap", "white soap",
                "cakes of white soap", "jug", "kettle", "towel",
                "folded towels", "folded towel", "cake of white soap",
                "brushes", "small brushes", "razors", "straight razors",
                "brushe", "small brush", "razor", "straight razor"}),
                "This item has not yet been coded.\n");

        }

        else

        {

            set_short("Women's bath");

            set_long("Cast iron tubs line a wall ventilated" +
                " with many round holes, and along the opposite" +
                " wall are a couple of small coal stoves" +
                " and shelves with kettles and jugs.\n");

            add_item(({"shelves", "opposite wall"}),
                "On the shelves you see jugs for carrying" +
                " water, kettles for heating it, neatly" +
                " folded towels, cakes of pink soap, and" +
                " bottles of lotion.\n");

            add_item(({"jugs", "kettles", "towels", "soap", "pink soap",
                "cakes of pink soap", "jug", "kettle", "towel",
                "folded towels", "folded towel", "cake of pink soap",
                "bottles", "bottles of lotion", "bottle", "bottle of lotion"}),
                "This item has not yet been coded.\n");

        }

        add_item(({"walls", "wall", "holes", "round holes",
            "hole", "round hole"}),
            "The walls have many round holes that provide light" +
            " and ventilation, but they are all too high for" +
            " you to see through.\n");

        add_item(({"tubs", "iron tubs", "cast iron tubs",
            "tub", "iron tub", "cast iron tub"}),
            "This item has not yet been coded.\n");

        add_exit(BOG_INNER_LOW + This_Location, "down", 0, 1);

    }

    else

    {

        set_short("Barracks room inside the fortress");

        set_long("Two long rows of hammocks, closely packed to make" +
            " maximum use of the space here, form an" +
            " unpretentious barracks room for the residents of" +
            " the fortress. One end of each hammock is attached to the" +
            " wall and the other hangs on a post sticking up from" +
            " the floor. The posts border a narrow corridor that is" +
            " the only open space for walking through the room.\n");

        add_item(({"walls", "wall", "holes", "round holes",
            "hole", "round hole"}),
            "The walls have many round holes that provide light" +
            " and ventilation, but they are all too high for" +
            " you to see through.\n");

        add_item(({"hammock", "hammocks", "mesh", "strong mesh"}),
            "The hammocks are uniform in construction, a strong mesh tied" +
            " to a post at one end and a peg driven into the wall" +
            " on the other. They are all empty.\n");

        add_item(({"post", "posts"}),
            "Much like the rest of the fortress, the posts are" +
            " all simply crafted of wood, functional and unadorned.\n");

        add_item(({"peg", "pegs"}),
            "The pegs are roughly square in shape, although little" +
            " care was taken to give them a precise fit into the walls;" +
            " their battered appearance suggests that they are" +
            " merely scraps of wood driven into place by brute force.\n");

        add_item(({"space", "open space", "corridor", "narrow corridor"}),
            "Little room has been left for walking here. Obviously the" +
            " plan was to provide sleeping quarters for as many" +
            " people as possible in this space.\n");

        /*
         *  The following diagram represents the rooms at this level, eight 
         *  corner rooms and eight side rooms.  The stair_position value will
         *  be 1, 3, 5, or 7; corners at the selected position will have stairs
         *  leading down and not connect to any side rooms.


         *       -------------
         *      / 7 |  N  | 1 \        To make sure that we don't have an exit
         *     /---------------\       from this room laterally to a corner
         *    /NW /         \ NE\      room with a down stairway, we have to
         *   /---/           \---\     check which side of the fortress this
         *  | 5 /             \ 3 |    room is on and then delete the
         *  |--|               |--|    appropriate element from the
         *  |W |               | E|    adjacent_rooms array before adding the
         *  |--|               |--|    exits.  For example, if the stairways
         *  | 3 \             / 5 |    are at the two positions labelled 1,
         *   \---\           /---/     then the north side room should not have
         *    \SW \         / SE/      an exit east, and the northeast side
         *     \---------------/       room should not have an exit northwest.
         *      \ 1 |  S  | 7 /
         *       -------------


         *  As usual, the elements in adjacent_rooms are arranged by compass
         *  position starting with north in position 0 and proceeding clockwise
         *  to northwest in position 7.    
         */

        switch (stair_position)

        {

            case 1:

            if (side == "north") adjacent_rooms[2] = 0;
            if (side == "northeast") adjacent_rooms[7] = 0;
            if (side == "south") adjacent_rooms[6] = 0;
            if (side == "southwest") adjacent_rooms[3] = 0;
            break;

            case 3:

            if (side == "northeast") adjacent_rooms[3] = 0;
            if (side == "east") adjacent_rooms[0] = 0;
            if (side == "southwest") adjacent_rooms[7] = 0;
            if (side == "west") adjacent_rooms[4] = 0;
            break;

            case 5:

            if (side == "southeast") adjacent_rooms[1] = 0;
            if (side == "east") adjacent_rooms[4] = 0;
            if (side == "northwest") adjacent_rooms[5] = 0;
            if (side == "west") adjacent_rooms[0] = 0;
            break;

            case 7:

            if (side == "north") adjacent_rooms[6] = 0;
            if (side == "northwest") adjacent_rooms[1] = 0;
            if (side == "south") adjacent_rooms[2] = 0;
            if (side == "southeast") adjacent_rooms[5] = 0;
            break;

        }

        /*
         *  There is no default case for the preceding switch.  If none of the 
         *  conditions are satisfied, then all exits are added.    
         */

        if (adjacent_rooms[0]) add_exit(adjacent_rooms[0], "north", 0, 1);
        if (adjacent_rooms[1]) add_exit(adjacent_rooms[1], "northeast", 0, 1);
        if (adjacent_rooms[2]) add_exit(adjacent_rooms[2], "east", 0, 1);
        if (adjacent_rooms[3]) add_exit(adjacent_rooms[3], "southeast", 0, 1);
        if (adjacent_rooms[4]) add_exit(adjacent_rooms[4], "south", 0, 1);
        if (adjacent_rooms[5]) add_exit(adjacent_rooms[5], "southwest", 0, 1);
        if (adjacent_rooms[6]) add_exit(adjacent_rooms[6], "west", 0, 1);
        if (adjacent_rooms[7]) add_exit(adjacent_rooms[7], "northwest", 0, 1);

    }

    /*
     *  "uid" settings required for cloning objects.    
     */

    setuid();
    seteuid(getuid());

    /*
     *  PROPERTIES    
     */

    add_prop(ROOM_I_HIDE, 80);  /*  Lots of hiding places. */
    add_prop(ROOM_I_LIGHT, 2);  /*  Moderate light. */

    /*
     *  SPECIAL FUNCTION    
     */

    /*
     *  Tell the Sanctimonian central control room that this room has been 
     *  loaded.  Function is found in /d/Calia/central/bog/baseroom.c.    
     */

    register_room();

}
