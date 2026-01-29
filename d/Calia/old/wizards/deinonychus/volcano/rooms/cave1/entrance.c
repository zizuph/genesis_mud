/*  part of the cave on Indy

    coder(s):   Deinonychus

    history:    DD.MM.YY        what done                       who did
		28.02.93        created                         Deinonychus

    purpose:    none
    exits:      none

    objects:    none
    npcs:       none

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/


inherit "/std/room";
#include "cave1.h"
#include <stdproperties.h>
#include <macros.h>

/*
 * Function name: create_room()
 * Description  : Create the room.
 * Arguments:     none
 * Returns:       nothing
 */

void
create_room()
{
  set_short("Entrance");
  set_long(BS("You're at the entrance of a dark cave. Luckily there's " +
    "some light shining through the bush outside, otherwise you " +
    "wouldn't see a thing. On the floor is a doormat (obviously " +
    "someone not afraid of the dark dwells here).\n"));
  add_item(({"doormat", "mat"}), BS("It's an ordinary brown doormat " +
    "with the inscription: 'Don't be afraid of the dark. =;^)'\n"));
  add_item("floor", 0);
  add_exit(ROOM("cloak_room"), "northeast", 0);
  add_exit(ROOM("visitors_cloak_room"), "east", 0);
  add_exit(ROOM("track_08"), "west", 0);
  add_prop(ROOM_I_INSIDE, 1);
}

/*****************************************************************************/

/*
 * Function name: init
 * Description:   gives the player some new commands
 * Arguments:     none
 * Returns:       nothing
 */

void
init()
{
  add_action("clean", "clean");
  ::init();
}

/*****************************************************************************/

/*
 * Function name: clean
 * Description:   let the player clean his shoes/feet on the doormat
 * Arguments:     what to clean
 * Returns:       0/1
 */

int
clean(string what)
{
  if(sscanf(what, "shoes %s") || sscanf(what, "feet %s"))
  {
   write(BS("You clean your shoes on the doormat. You really have " +
     "good manners.\n"));
   say(QCTNAME(TP) + " cleans the shoes on the doormat.\n");
   return 1;
  }
  else
  {
   NF("Clean what?");
   return 0;
  }
}
