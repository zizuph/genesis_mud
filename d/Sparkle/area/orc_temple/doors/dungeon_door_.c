/*
 *  /d/Sparkle/area/orc_temple/doors/dungeon_door.c
 *
 *  Doors in the dungeon can inherit this file to give them the ability
 *  to prevent passage if orcs are present.
 *
 *  Created November 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/door";

#include <macros.h>
#include "../defs.h"



/* Prototypes */
nomask void        create_door();
public void        create_dungeon_door();


/*
 * Function name:        create_door
 * Description  :        constructor for the door object
 */
nomask void
create_door()
{
    ::create_door();

    create_dungeon_door();
} /* create_door */


/*
 * Function name:        create_dungeon_door
 * Description  :        dummy routine to be used by inheriting files
 */
public void
create_dungeon_door()
{
} /* create_dungeon_door */


/*
 * Function name: pass_door
 * Description:   Pass the door. Wizards can pass the door by giving the
 *                command with an exclamation point.
 * Arguments:     arg - arguments given
 *
 * We mask this file to allow us to control passage if guards happen
 * to be standing in the way, and it is the sort of room we want to
 * do that in.
 */
int
pass_door(string arg)
{
    object  room  = environment(this_object()),
            guard = present(ORC_TEMPLE_NPC, room);

    if (room->id(DOOR_BLOCK_ROOM) && guard)
    {
        tell_room(room, QCTNAME(guard) + " shoves " + QTNAME(this_player())
          + " away from the door shouting: Not think so!\n", this_player());
        this_player()->catch_tell(QCTNAME(guard) + " shoves you"
          + " away from the door shouting: Not think so!\n");

        return 1;
    }

    ::pass_door(arg);
} /* pass_door */