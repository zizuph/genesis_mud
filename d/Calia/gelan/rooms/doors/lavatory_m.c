/* 	this is a door of the town Gelan

    coder(s):   Merlin

    history:    8/11/97     typos fixed                     Maniac
                21. 2.93    path system                     Merlin
                14. 1.93    towndoors.h -> door.h           Merlin
                22.12.92    continued                       Merlin
                21.12.92    created                         Merlin

    purpose:	door to close male cabin
    exits:      male to male cabin, leave back to lavatory.

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/


inherit "/std/door";
#include "door.h"
#include <stdproperties.h>

create_door() {

  ::create_door();                              /* get defaults */

  set_door_id("men_door");                      /* id, must be unique in room */
  set_door_name(({"blue door marked <men>","blue door","men door"}));   /* name(s) for the door, first
                                                   string is std desc */

  /* commands */

  set_pass_command(({ "men", "blue" })); /* command(s) to pass the door */
  set_open_mess(({"@@open_mess_here",           /* msg when opening in this room */
                "@@open_mess_there"}));         /* msg in the other room */

  set_other_room(GELAN_ROOMS + "lavatory_male");        /* room on the other side */

  /* lock */
  set_lock_name("blue lock");                   /* name(s) of the lock */
  set_lock_command("");                         /* command to open lock */
  set_unlock_command("");                       /* command(s) to unlock the lock */
  set_lock_desc("@@exa_blue_lock");             /* desc of lock */

  /* state */

  set_open(0);                                  /* 1 for open, 0 for closed, std 1 */
  set_locked(0);                                /* 0 for unlocked, 1 for locked, std 1 */

  /* descs */

  set_door_desc(BS("The door was recently painted with a strong blue. On "
          + "the door is written with big, bright white letters 'MEN'. "
          + "There is also a lock on the door.\n"));                       /* description of the door */

  /* properties */

}

/*
 * Function name: open_mess_here
 * Description:   message when opening door
 * Arguments:     none
 * Returns:       none
 */

string
open_mess_here()
{

    if((GELAN_ROOMS + "lavatory_male")->query_occupied())
    {
        tell_object(this_player(),"As you open the door, you see that "
          + "there is already someone in the cabin. You'd better close the "
          + "door again.\n");
        return "opens the door and blushes on realizing that the cabin "
          + "is already occupied.\n";
    }
    else
    {
        return  "opens the blue door.\n";
    }
}

/*
 * Function name: open_mess_there
 * Description:   message when opening door
 * Arguments:     none
 * Returns:       none
 */

string
open_mess_there()
{

    if((GELAN_ROOMS + "lavatory_male")->query_occupied())
    {
        return "Suddenly the door opens and someone looks in. You'd better "
          + "lock the door next time.\n";
    }
    else
    {
        return  "The blue door opens.\n";
    }
}

/*
 * Function name: exa_lock
 * Description:   string when looking at door
 * Arguments:     none
 * Returns:       string desc of lock
 */

string
exa_lock()
{
    string str;

    str = "Well, it's not really a lock, just a sign showing if the cabin "
          + "is occupied. You can't unlock the door from this side. ";

    if(lock_status)
        return BS(str + "The sign says 'OCCUPIED', with red letters.\n");
    else
        return BS(str + "The sign says 'FREE', with green letters.\n");
}

