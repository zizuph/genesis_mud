/*
 * Door for the male toilet at Last pier
 * Adapted from the Gelan code
 * Tapakah, 04/2009
 */

#include "gs_office.h";
#include <stdproperties.h>
inherit "/std/door";

/*
 * Function name: pass_door
 * Description:   called when passed door
 * Arguments:     string with arguments
 * Returns:       0 if passed, 1 for not
 */

int
pass_door(string arg)
{
    object ob;

    ob = find_object(TOILET_F);

    if(!(open_status))
        return ::pass_door(arg);

    if(!(ob->pass_door(arg)))
        return ::pass_door(arg);

    return 1;

}

void
create_door()
{

  ::create_door();                              /* get defaults */

  set_door_id("women_door");                    /* id, must be unique in room */
  set_door_name(({"pink door","women door","door"}));   
                                        /* name(s) for the door, first
                                                   string is std desc */

  /* commands */

  set_pass_command(({ "leave", "pink", "women" }));    /* command(s) to pass the door */

  set_other_room(ENTRANCE);             /* room on the other side */

  /* state */

  set_open(0);                                  /* 1 for open, 0 for closed, std 1 */
  set_locked(0);                                /* 0 for unlocked, 1 for locked, std 1 */

  /* lock */

  set_lock_name("lock");                        /* name(s) of the lock */
  set_lock_command("lock");                     /* command to open lock */
  set_unlock_command("unlock");                 /* command(s) to unlock the lock */
  set_lock_desc("@@exa_lock");                  /* desc of lock */
  set_lock_mess(({"locks the door.\n",          /* msg when locking in this room */
                  "You hear the sound of a lock being locked.\n"}));
                                                /* msg in the other room */
  set_unlock_mess(({"unlocks the door.\n",      /* msg when unlocking in this room */
                    "You hear the sound of a lock being unlocked.\n"}));

  /* descs */

  set_door_desc("It's a freshly pink painted door.\n");
                                                /* description of the door */

  /* properties */

}

/*
 * Function name: exa_lock
 * Description:   desciption of lock
 * Arguments:     none
 * Returns:       string with desc
 */

string
exa_lock()
{

    if(lock_status)
        return "The lock is closed.\n";
    else
        return "The lock is open.\n";

}

/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */

