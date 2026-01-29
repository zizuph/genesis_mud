// ROOM:  base_interior.c

    /*  Calia Domain

    HISTORY

    [99-06-29] created by Uhclem from
    [D:\CALIA\CENTRAL\BOG\INNER\GROUND\BASE_INT.DOC].

    PURPOSE

    This is the base for interior rooms (not against the outer wall) inside the
    Sanctimonian fortress.  The fortress is octagonal; there are 8 rooms at the
    corners, 8 at the sides, and 21 in the interior at this level.

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

// Function:  create_interior(location, *adjacent_rooms)

/*

Purpose:  Create the room description and add standard attributes.

Arguments:  string containing the filename of this room, string array
containing filenames of adjacent rooms.

Returns:  nothing.

*/

void
create_interior(string location, string *adjacent_rooms)

{

    int control_code = query_control_code();
    object drudge;
    object building;

    This_Location = location;

    /*
     *  "uid" settings required for cloning objects.    
     */

    setuid();
    seteuid(getuid());

    /*
     *  EXITS AND DESCRIPTION    
     */

    if (adjacent_rooms[0]) add_exit(adjacent_rooms[0], "north", 0, 1);
    if (adjacent_rooms[2]) add_exit(adjacent_rooms[2], "east", 0, 1);
    if (adjacent_rooms[4]) add_exit(adjacent_rooms[4], "south", 0, 1);
    if (adjacent_rooms[6]) add_exit(adjacent_rooms[6], "west", 0, 1);

    /*
     *  If I create a room at This_Location in the BUILDING directory, the 
     *  following routine will automatically incorporate it into the exits and
     *  descriptions in this room.  The BUILDING room must have these special
     *  functions:

     *  query_outside_short() gives this room its short description.
     *  query_outside_long() adds text to this room's long description.
     *  query_outside_item() provides text for 'structure' item in this room.

     *  All of these functions take no argument and return a string.    
     */

    if (file_size(BUILDING + This_Location + ".c") > 0)

    {

        add_exit(BUILDING + This_Location, "in", 0, 1);
        drudge = clone_object(DRUDGE);
        drudge->move(BUILDING + This_Location);
        building = environment(drudge);
        drudge->remove_object();

        set_short(building->query_outside_short());

        set_long("You are in the interior of a great log" +
            " fortress. Under your feet is a floor of broad" +
            " wooden planks that covers the entire ground" +
            " within the fortress walls. Upon these planks" +
            " are built some wooden structures that divide the" +
            " space into narrow corridors." +
            building->query_outside_long() + "\n");

        add_item(({"structures", "wooden structures"}),
            "The wooden structures resemble small houses, each painted" +
            " white and looking like the others.\n");

        add_item(({"structure", "wooden structure"}),
            building->query_outside_item());

    }

    else

    {

        set_short("Fortress interior");

        set_long("You are in the interior of a great log" +
            " fortress. Under your feet is a floor of broad" +
            " wooden planks that covers the entire ground" +
            " within the fortress walls. Upon these planks" +
            " are built some wooden structures that divide the" +
            " space into narrow corridors.\n");

        add_item(({"structures", "wooden structures",
            "structure", "wooden structure"}),
            "The wooden structures resemble small houses, each painted" +
            " white and looking like all the others. SPECIFIC" +
            " STRUCTURES WILL BE ADDED LATER.\n");

    }

    add_item(({"corridors", "narrow corridors",
        "corridor", "narrow corridor"}),
        "There's enough room for you to walk between the structures" +
        " here on the fortress floor, or several people to walk" +
        " abreast if they proceed in a straight line.\n");

    add_item(({"fortress", "log fortress", "interior"}),
        "The fortress walls rise all around you in an" +
        " octagonal formation. Not far over your head is an" +
        " open balcony that rings the interior, and the" +
        " upper levels are supported by pillars made" +
        " of stout logs.\n");

    add_item(({"pillars", "pillar", "levels", "upper levels"}),
        "The fortress interior seems to be divided" +
        " into several distinct levels, starting with the floor" +
        " upon which you stand and rising up the walls. Pillars" +
        " made of stout logs provide solid support" +
        " for all the construction.\n");

    add_item(({"construction", "logs", "stout logs",
        "log", "stout log", "balcony", "open balcony",
        "wall", "walls", "fortress wall", "fortress walls"}),
        "The fortress is an impressive feat of log construction," +
        " with logs that interlock and support each other." +
        " You feel certain that this structure could" +
        " withstand any assault, well, any other than fire.\n");

    add_item(({"floor", "fortress floor", "planks", "wooden planks",
        "plank", "wooden plank", "ground", "surface", "level surface"}),
        "The planks cover the ground perfectly, leaving no gaps" +
        " and providing a smooth, level surface for walking.\n");

    /*
     *  PROPERTIES    
     */

    add_prop(ROOM_I_HIDE, 50);  /*  Some hiding places. */
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
