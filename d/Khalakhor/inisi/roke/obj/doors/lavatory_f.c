/*
 * Door for the female toilet at Cadu pier
 * Adapted from the Gelan code
 * Tapakah, 04/2009
 */

#include <stdproperties.h>
#include "../../roke.h";

inherit "/std/door";

create_door() {

  ::create_door();                              /* get defaults */

  set_door_id("women_door");                      /* id, must be unique in room */
  set_door_name(({"pink door marked <women>","pink door","women door"}));   /* name(s) for the door, first
                                                   string is std desc */

  /* commands */

  set_pass_command(({ "women", "pink" })); /* command(s) to pass the door */
  set_open_mess(({"@@open_mess_here",           /* msg when opening in this room */
                "@@open_mess_there"}));         /* msg in the other room */

  set_other_room(NYREESEDIR + "cadu_pier_toilet_f");        /* room on the other side */

  /* lock */
  set_lock_name("pink lock");                   /* name(s) of the lock */
  set_lock_command("");                         /* command to open lock */
  set_unlock_command("");                       /* command(s) to unlock the lock */
  set_lock_desc("@@exa_pink_lock");             /* desc of lock */

  /* state */

  set_open(0);                                  /* 1 for open, 0 for closed, std 1 */
  set_locked(0);                                /* 0 for unlocked, 1 for locked, std 1 */

  /* descs */

  set_door_desc("The door was recently painted with a gentle pink. On "
          + "the door is written with big, bright white letters 'WOMEN'. "
          + "There is also a lock on the door.\n");                       

  
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

    if((NYREESEDIR + "cadu_pier_toilet_m")->query_occupied())
    {
        tell_object(this_player(),"As you open the door, you see that "
          + "there is already someone in the cabin. You'd better close the "
          + "door again.\n");
        return "opens the door and blushes on realizing that the cabin "
          + "is already occupied.\n";
    }
    else
    {
        return  "opens the pink door.\n";
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

    if((NYREESEDIR + "cadu_pier_toilet_m")->query_occupied())
    {
        return "Suddenly the door opens and someone looks in. You'd better "
          + "lock the door next time.\n";
    }
    else
    {
        return  "The pink door opens.\n";
    }
}
