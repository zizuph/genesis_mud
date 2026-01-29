// ROOM:  baseroom.c

    /*  Calia Domain

    HISTORY

    [99-06-11] created by Uhclem from [D:\CALIA\CENTRAL\BOG\BASEROOM.DOC].

    PURPOSE

    This room contains a few functions required by all bog rooms.  It is
    inherited by those rooms instead of /std/room.c.

    */

// INCLUSIONS AND DEFINITIONS

inherit "/std/room";

#include "defs.h"

// GLOBAL VARIABLES

object Control_Room = find_object(BOG_CONTROL_ROOM);
int Control_Code;  /*  used to synchronize variable effects between rooms  */

// FUNCTIONS

// Function:  register_room()

/*

Purpose:  register this room with the Sanctimonian control room which contains
functions that affect the actions of npcs and effects in rooms in the bog
area.  This function should be called by the create_room functions in
individual bog rooms.

Arguments:  none.

Returns:  nothing.

*/

void
register_room()

    {

    object drudge;

    if (!Control_Room)

        {

        drudge = clone_object(DRUDGE);
        drudge->move(BOG_CONTROL_ROOM);
        Control_Room = environment(drudge);
        drudge->remove_object();

        }

    Control_Code = Control_Room->register_room(this_object());

    }

// Function:  register_player(new_player)

/*

Purpose:  register a player with the control room.

Arguments:  object representing the player to register.

Returns:  nothing.

*/

void
register_player(object new_player)

    {

    Control_Room->register_player(new_player);

    }

// Function:  query_control_code()

/*

Purpose:  gives the control code set by the Control Room.  The same number is
given to all bog rooms and is used to synchronize variable effects such as the
placement of stairs.

Arguments:  none.

Returns:  int 0-999.

*/

int
query_control_code()

    {

    return Control_Code;

    }
