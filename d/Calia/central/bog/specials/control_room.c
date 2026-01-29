// ROOM:  control_room.c

    /*  Calia Domain

    HISTORY

    [99-06-17] created by Uhclem from
    [D:\CALIA\CENTRAL\BOG\SPECIALS\CONTROL_.DOC].

    PURPOSE

    This room contains functions that control the actions of the Sanctimonians
    and certain actions in the rooms they occupy.

                       NO MORTAL SHOULD EVER ENTER THIS ROOM!

    The controls are fully automated, so no commands are provided.

    */

// INCLUSIONS AND DEFINITIONS

inherit "/std/room";

#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <language.h>
#include <filter_funs.h>
#include "defs.h"

// GLOBAL VARIABLES

object *Rooms = ({});  /* rooms under the control of this one */
object *Players = ({});  /* players and "foreign" npc's in the bog area */
object *Guards = ({});  /* Sanctimonians defending the bog area & fortress */
object Secure_Master = find_object("/secure/master");
int Control_Code = random(1000);

// FUNCTIONS

// Function:  register_room(new_room)

/*

Purpose:  add a room to the Rooms array; called by the room being registered.

Arguments:  object representing the room to register.

Returns:  int control code 0-999.  This number is used to synchronize variable
effects (such as the placement of staircases).

*/

int
register_room(object new_room)

{

    if (member_array(new_room, Rooms) == -1) Rooms += ({new_room});
    return Control_Code;

}

// Function:  register_player(new_player)

/*

Purpose:  add a player to the Players array; called by the room a player has
just entered.

Arguments:  object representing the player to register.

Returns:  nothing.

*/

void
register_player(object new_player)

{

    if (member_array(new_player, Players) == -1) Players += ({new_player});

}

// Function:  register_guard(new_guard)

/*

Purpose:  add a guard to the Guards array; called by the room being registered.

Arguments:  object representing the guard to register.

Returns:  nothing.

*/

void
register_guard(object new_guard)

{

    if (member_array(new_guard, Guards) == -1) Guards += ({new_guard});

}

// Function:  clean_up_arrays()

/*

Purpose:  eliminate any obsolete elements from the global arrays, such as
players who have left the area, guards who have been killed, or rooms that have
been removed from memory. The function is called by this room by a repeating
alarm.

Arguments:  none.

Returns:  nothing.

*/

void
clean_up_arrays()

{

    int j;
    int k;
    Players -= ({0});
    Guards -= ({0});
    Rooms -= ({0});
    j = sizeof(Players) - 1;

    for (k = j; k >=0; k -= 1)

    {

        if (!wildmatch("/d/Calia/central/bog*",
            file_name(environment(Players[k]))) &&
            !Players[k]->query_linkdead())

        {

            Players -= ({Players[k]});

        }

    }

    /*
     *  If there are no players in the bog area, remove all guards and bog 
     *  rooms from memory and let the area rebuild itself when the next happy
     *  plunderer comes to visit.    
     */

    if (!sizeof(Players))

    {

        j = sizeof(Guards) - 1;

        for (k = 0; k < j; k += 1)

        {

            /*
             *  It's unlikely that a guard would be chased out of the bog area, 
             *  but if it does happen, we allow an AWOL guard to stay in the
             *  game.    
             */

            if (wildmatch("/d/Calia/central/bog*",
                file_name(environment(Guards[k]))))

            {

                Guards[k]->remove_object();

            }

        }

        j = sizeof(Rooms) - 1;

        for (k = 0; k < j; k += 1)

        {

            Rooms[k]->remove_object();

        }

        /*
         *  Finally, if there are no Players, Rooms, or Guards to monitor, 
         *  there's no need for a control room.    
         */

        remove_object();

    }

}

// Function:  pull_plug()

/*

Purpose:  testing purposes only; will be removed when the central forest is
opened.  Calls the clean_up_arrays function on a delay so the wizard who calls
this function has time to get out of the room before the entire bog is
unloaded.

Arguments:  none.

Returns:  nothing.

*/

void
pull_plug()

{

    object *wizards = FILTER_LIVE(all_inventory(this_object()));

    while(sizeof(wizards))

    {

        if (wizards[0])

        {

            wizards[0]->catch_msg("You are sent home!\n");

            wizards[0]->move_living("M",
                Secure_Master->wiz_home(wizards[0]->query_name()));

            wizards -= ({wizards[0]});

        }

    }

    set_alarm(0.1, 0.0, clean_up_arrays);

}

// Function:  create_room()

/*

Purpose:  Create the room description and add standard attributes.

Arguments:  none.

Returns:  nothing.

*/

void
create_room()

{

    set_short("Sanctimonian central control room");

    set_long("This is the Sanctimonian central control room." +
        " There is nothing for you to look at or do here.\n");

    /*
     *  PROPERTIES    
     */

    add_prop(ROOM_I_HIDE, 0);
    add_prop(ROOM_I_LIGHT, 3);

    /*
     *  SPECIAL FUNCTION    
     */

    set_alarm(900.0, 900.0, clean_up_arrays);

}
