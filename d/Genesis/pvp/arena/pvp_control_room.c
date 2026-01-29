/*
 *  /d/Genesis/pvp/arena/arena_room.c
 *
 *  This is the base file for rooms in the raid arena area for pvp in
 *  Genesis. It interprets a text-drawn map to create rooms based on what
 *  has been set for a given tile in a given position.
 *
 *  Created May 2014, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/room";
#include "../defs.h"


/* Global Variables */
public int         Silence_Moves = 0;
public int         Monster_Count = 0;

/* Prototypes */
public void        create_room();
public int         query_monster_count() { return Monster_Count; }


/*
 * Function name:        create_room
 * Description  :        set up the room
 */
public void
create_room()
{
    set_short("the pvp arena control room");
    set_long(capitalize(short()) + ".\n");
} /* create_room */


/*
 * Function name:        arena_alert
 * Description  :        send an arena alert to the pvp control room
 * Arguments    :        string alert_type: the type of alert,
 *                       string message   : the alert message
 */
public void
arena_alert(string alert_type, string message)
{
    switch (alert_type)
    {
        case "moves":
            if (Silence_Moves)
            {
                return;
            }
            break;
        default:
            break;
    }

    tell_room(this_object(), "ARENA: " + message + "\n");
} /* arena_alert */


public int
get_monster_number()
{
    Monster_Count++;
    return Monster_Count;
} /* get_monster_number */
