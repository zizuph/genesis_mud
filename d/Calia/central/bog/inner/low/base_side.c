// ROOM:  base_side.c

    /*  Calia Domain

    HISTORY

    [99-06-18] created by Uhclem from
    [D:\CALIA\CENTRAL\BOG\INNER\LOW\BASE_SID.DOC].

    PURPOSE

    This is the base for interior rooms on the sides at the low level of the
    Sanctimonian fortress.  The fortress is octagonal; there are eight rooms at
    the corners, eight at the sides, and twelve in the interior at this level.
    The side rooms are either storage areas or stairways up to the baths; the
    control code supplied by the central control room decides the placement of
    the two baths (men's and women's, of course).

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
code determines which two side rooms have up staircases to the baths.

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
    int room_finder = 0;

    This_Location = location;

    /*
     *  The baths are on the east and west sides of the fortress when n<2, on 
     *  the east and west when n>=2.  If the following test is true, this room
     *  has stairs leading up to a bath.    
     */

    if ((side == "north" || side == "south") && (control_code % 4) < 2 ||
        (side == "east" || side == "west") && (control_code % 4) > 1)

    {

        /*
         *  The following test makes sure that there's one men's and one 
         *  women's bath. They're nearly identical, but they're identified by
         *  signs outside so that it's reasonable to put a clear indication in
         *  the description.    
         */

        /*
         *  Note: add distinctive hook_smelled effects for each bath.    
         */

        if ((control_code % 2) && (side == "north" || side == "east") ||
            !(control_code % 2) && (side == "south" || side == "west"))

        {

            set_short("Stairs to men's bath");

            set_long("This area is conspicuously clean and free" +
                " of any clutter. Broad stairs lead upward, and" +
                " the words MEN'S BATH are neatly" +
                " written above them.\n");

        }

        else

        {

            set_short("Stairs to women's bath");

            set_long("This area is conspicuously clean and free" +
                " of any clutter. Broad stairs lead upward, and" +
                " the words WOMEN'S BATH are neatly" +
                " written above them.\n");

        }

        add_exit(BOG_INNER_MIDDLE + This_Location, "up", 0, 2);

    }

    else

    {

        set_short("Storage area inside the fortress");

        set_long("Stuff is stored here, but you can't look at" +
            " it just yet.\n");

    }

    /*
     *  The whole fortress is designed to be easy to get lost in.  Like a large 
     *  mansion or office building, it only seems like a maze if you're not
     *  familiar with the layout.  On this level, all rooms against the outer
     *  wall connect to the inner balcony and not to other outer wall rooms.
     *  To prevent these room-to-room exits in a side room, look for two rooms
     *  that are in opposite compass directions (difference in indices is 4)
     *  and the corresponding elements in adjacent_rooms to zero.    
     */

    while (room_finder < 8 &&
        (!adjacent_rooms[room_finder] ||
        !adjacent_rooms[(room_finder + 4) % 8]))

    {

        room_finder += 1;

    }

    /*
     *  As with all my other rooms that use the adjacent_rooms array to 
     *  generate exits, setting the value of any element to zero effectively
     *  makes that room "not adjacent" to this one.    
     */

    adjacent_rooms[room_finder] = 0;
    adjacent_rooms[(room_finder + 4) % 8] = 0;

    if (adjacent_rooms[0]) add_exit(adjacent_rooms[0], "north", 0, 1);
    if (adjacent_rooms[1]) add_exit(adjacent_rooms[1], "northeast", 0, 1);
    if (adjacent_rooms[2]) add_exit(adjacent_rooms[2], "east", 0, 1);
    if (adjacent_rooms[3]) add_exit(adjacent_rooms[3], "southeast", 0, 1);
    if (adjacent_rooms[4]) add_exit(adjacent_rooms[4], "south", 0, 1);
    if (adjacent_rooms[5]) add_exit(adjacent_rooms[5], "southwest", 0, 1);
    if (adjacent_rooms[6]) add_exit(adjacent_rooms[6], "west", 0, 1);
    if (adjacent_rooms[7]) add_exit(adjacent_rooms[7], "northwest", 0, 1);

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
