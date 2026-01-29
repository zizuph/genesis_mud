/*
 *  /d/Sparkle/area/orc_temple/doors/2_cell_door.c
 *
 *  This is one of the doors for the prison cells on the 2nd level of
 *  the dunegeon beneath the Orc Temple in Sparkle.
 *
 *  Created October 2010, by Cooper Sherry (Gorboth)
 *
 *  Modified by: Maelstrom, 2017/04
 *
 *  /d/Krynn/gnome/gnome_mine/rooms/mine_instance_actions/mine_instance_dungeon_door.c
 *
 *  Repurposed for the door at dungeons inside mines.
 *
 */

inherit "/std/door";

#include <macros.h>
#include "../../defs.h"



/* Prototypes */
nomask void        create_door();
public void        create_dungeon_door();
public void        configure_door(string s, string id);


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
 * Function name: pass_door
 * Description:   Pass the door. Wizards can pass the door by giving the
 *                command with an exclamation point.
 * Arguments:     arg - arguments given
 *
 * We mask this file to allow us to control passage if guards happen
 * to be standing in the way, and it is the sort of room we want to
 * do that in.
 */
    /*
int
pass_door(string arg)
{
    object  room  = environment(this_object()),
            guard = present(ORC_TEMPLE_NPC, room);

    if (this_player()->id(ORC_TEMPLE_NPC))
    {
        return ::pass_door(arg);
    }

    if (room->query_prop(DOOR_BLOCK_ROOM) && guard)
    {
        if (this_player()->check_seen(guard))
        {
            tell_room(room, QCTNAME(guard) + " shoves " 
              + QTNAME(this_player()) + " away from the door shouting:"
              + " Not think so!\n", this_player());
            this_player()->catch_tell(guard->query_The_name(this_player())
              + " shoves you away from the door shouting: Not think so!\n");

            return 1;
        }

        write("The guards don't seem to notice you heading for the door.\n");  
    }

    return ::pass_door(arg);
} *//* pass_door */


/*
 * Function name:        create_dungeon_door
 * Description  :        constructor for the door object
 */
public void
create_dungeon_door()
{
    /* set some dummy values just so the thing will load */
    set_door_id("dungeon_door");

    set_pass_command( ({ "north" }) );
    set_door_name( ({ "door" }) );

    set_open_desc("An open door that is not configured.\n");
    set_closed_desc("A closed door that is not configured.\n");
    set_door_desc("This door is not yet configured.\n");
    /* Good. now the real stuff. */

    set_fail_pass("The heavy stone door is closed.\n");
    set_open_mess( ({ "opens the heavy stone door.\n",
                      "The heavy stone door opens.\n" }) );
    set_close_mess( ({ "closes the heavy stone door.\n",
                       "The heavy stone door closes.\n" }) );

    add_item( ({ "lock" }),
        "The casing surrounding the lock looks very old. A rectangular keyhole is" +
        " located right in the center.\n");
    add_item( ({ "keyhole", "rectangular keyhole" }),
        "It looks pretty standard.\n");
    add_item( ({ "handle", "door handle" }),
        "The door doesn't really seem to have a handle. Probably," +
        " anyone wanting to open it would just" +
        " tug or shove in the right direction.\n");

    set_other_room("/d/Nowhere/no_room");

    set_lock_command("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(1);
    set_key("_dungeon_mines_key");
    set_str(100);
} /* create_dungeon_door */


/*
 * Function name:        configure_door
 * Description  :        set up the door, allowing us to tell the
 *                       door which direction it is leading.
 * Arguments    :        string s - the direction the door leads
 *                                  default: "north"
 */
public void
configure_door(string s, string id)
{
    set_door_id(id);

    set_pass_command( ({ s[0..0] ,s }) );
    set_door_name( ({ "door", "heavy stone door", 
                      "doorway",
                      s + " door", s + "ern door",
                      s + " doorway", s + "ern doorway",
                      "door to the " + s, "doorway to the " + s }) );

    set_open_desc("There is an open heavy stone door leading " + s + ".\n");
    set_closed_desc("There is a closed heavy stone door leading " + s + ".\n");

    set_door_desc("A heavy stone door which has been set in the " + s + "ern wall." +
                  " Stone engravings surround what seems to be a keyhole.\n");
} /* configure_door */



/*
 * Function name: do_pick_lock
 * Description:   Here we pick the lock, redefine this function if you want
 *      something to happen, like a trap or something.
 * Arguments:   skill - randomized picking skill of player
 *      pick  - how difficult to pick the lock
 */
    
/*  Function name: do_lockpick
  Description: 

  TODO: should work like a real lockpick, using the lockpick skill to check the difficulty and 
  giving real/false tips and how much to pull a pin.
  
  ex: you start lockpicking, you need to move the lockpick inside/outside/up/down. and hold the torque to the side.
    your instict tells you....
    your expertice as a XXXXX makes you suspect the best would be....
*/
void
do_pick_lock(int skill, int pick)
{
    if (skill > pick)
    {
  if (no_pick)
  {
      write("You failed to pick the lock. It seems unpickable to you.\n");
      return;
  }

  write("You get very satisfied when you hear a soft 'klick' from " +
      "the lock.\n");
  say("You hear a soft 'klick' from the lock.\n");
  do_unlock_door("");
  other_door->do_unlock_door(check_call(unlock_mess[1]));
    } else if (skill < (pick - 50))
  write("You failed to pick the lock. It seems unpickable to you.\n");
    else
  write("You failed to pick the lock.\n");
}