/*
   Diamond

    lavatory_female.c
    -----------------

    Coded ........: May 1997
    By ...........: Kentari

    Latest update : May 1997
    By ...........: Kentari

	Taken virtually directly from the lavatory in gelan:
    coder(s):   Merlin

    history:    31.5.95     typo taken out                  Maniac
                21. 2.93    path system                     Merlin
                14. 1.93    towndoors.h -> door.h           Merlin
                26.12.92    created                         Merlin

    purpose:	door to close female cabin
    exits:      women to female cabin, leave back to lavatory.
*/


inherit "/std/door";
#include "../../local.h"
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"

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

    ob = find_object(DIROOM + "lavatory_female");

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
  set_door_name(({"pink door","women","women door","door"}));   /* name(s) for the door, first
                                                   string is std desc */

  /* commands */

  set_pass_command("leave");                    /* command(s) to pass the door */

  set_other_room(DIROOM + "bathrm");             /* room on the other
side */

  /* state */

  set_open(0);                                  /* 1 for open, 0 for closed, std 1 */
  set_locked(0);                                /* 0 for unlocked, 1 for locked, std 1 */

  /* lock */

  set_lock_name("lock");                        /* name(s) of the lock */
  set_lock_command("lock");                     /* command to open lock */
  set_unlock_command("unlock");                 /* command(s) to unlock the lock */
  set_lock_desc("@@exa_lock");                  /* desc of lock */
  set_lock_mess(({"locks the door.\n",          /* msg when locking in this room */
                ("You hear the sound of a lock being locked.\n")}));
                                                /* msg in the other room */
  set_unlock_mess(({"unlocks the door.\n",      /* msg when unlocking in this room */
                  ("You hear the sound of a lock being unlocked.\n")}));
                                                /* msg in the other room */

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
