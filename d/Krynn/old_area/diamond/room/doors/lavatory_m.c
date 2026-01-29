/*
   Diamond 

    lavatory_m.c
    ------------

    Coded ........: May 1997
    By ...........: Kentari

    Latest update : May 1997
    By ...........: Kentari

	Taken from the doors in Gelan lavatory
*/


inherit "/std/door";
#include "/d/Krynn/common/defs.h"
#include "../../local.h"
#include <stdproperties.h>

create_door() {

  ::create_door();                              /* get defaults */

  set_door_id("men_door");                      /* id, must be unique in room */
  set_door_name(({"blue door","men","men door"}));   /* name(s) for the door, first
                                                   string is std desc */

  /* commands */

  set_pass_command("men");                      /* command(s) to pass the door */
  set_open_mess(({"@@open_mess_here",           /* msg when opening in this room */
                "@@open_mess_there"}));         /* msg in the other room */

  set_other_room(DIROOM + "lavatory_male");        /* room on the other side */

  /* lock */
  set_lock_name("blue lock");                   /* name(s) of the lock */
  set_lock_command("");                         /* command to open lock */
  set_unlock_command("");                       /* command(s) to unlock the lock */
  set_lock_desc("@@exa_blue_lock");             /* desc of lock */

  /* state */

  set_open(0);                                  /* 1 for open, 0 for closed, std 1 */
  set_locked(0);                                /* 0 for unlocked, 1 for locked, std 1 */

  /* descs */

  set_door_desc("The door was recently painted with a strong blue. On "
          + "the door is written with big, bright white letters 'MEN'. "
          + "There is also a lock on the door.\n");                  
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

    if((DIROOM + "lavatory_male")->query_occupied())
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

    if((DIROOM + "lavatory_male")->query_occupied())
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
        return (str + "The sign says 'OCCUPIED', with red letters.\n");
    else
        return (str + "The sign says 'VACANT', with green letters.\n");
}
