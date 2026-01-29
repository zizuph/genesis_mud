/* A door in the Solace Graveyard
 * zd_mound_i.c
 * Dorak 07-04-95
 * a small round door leading into zmound_entr.c
 */


inherit "/std/door";
#include "../zlocal.h"

create_door()
{
    ::create_door();

    set_other_room(TDIR + "zmound_entr");
    set_door_id("m_door_i");
    set_door_desc("@@look_door");
    set_door_name(({"small round iron door", "round iron door", "iron door", 
		"door", "small door", "round door", "small round door", 
		"small iron door"}));
    set_open(0);
    set_open_desc("@@door_open");
    set_close_desc("There is a small round tightly closed door set into " +
		   " the mound here.");
    set_pass_command(({"enter", "enter mound"}));
    set_fail_pass("You bash your head on the closed door. You are dazed" +
		  " but not hurt.");
    set_open_command(({"pull door open", "pull the door open", 
		  "pull round door open", "pull the round door open",
		  "pull small round door open", 
		  "pull the small round door open"}));
    set_open_mess(({"@@open_mess1", "@@open_mess2"})); /* here, other rm */
    set_fail_open(({"@@fail_mess1", "@@fail_mess2"})); /* open, locked */
    set_close_command(({"push door closed", "push the door closed", 
		  "push round door closed", "push the round door closed",
		  "push small round door closed", 
		  "push the small round door closed"}));
    set_close_mess(({"@@close_mess1", "@@close_mess2"})); /* here, other rm */
    set_fail_close("You are surprised to find the door already closed");
    set_lock(1);
    set_lock_name(({"lock", "small lock", "small key hole", "key hole"}));
    set_lock_desc("There is a small key hole under the door's pull ring.");
    set_lock_command(({"lock", "lock the"}));
    set_unlock_command(({"unlock", "unlock the);
    set_pick(100);
}

look_door()
{
  write("This is a small round iron door.  It is set into the mound just" +
	"a bit.  There is an iron ring on its right side.  There is a " +
	" small key hole just under the ring.  It is otherwise quite " +
	"plain.  It has a large flat stone as a door step.\n");
  say(QCTNAME(TP) + " looks at the burial mound.\n");
  return "";
}
door_open()
{
  write("You see the back of a small round iron door.  The door " +
	"is wide open, swung outward against the burial mound " +
	"into which it is set.\n");
  say(QCTNAME(TP) + " looks at the burial mound.\n");
  return "";
}

string
open_mess1() 
   { return "pulls the " + door_name[0] + " wide open.\n"; }

string
open_mess2() 
   { return "Light floods in as the " + door_name[0] + " opens outward.\n"; }

string
fail_mess1() 
   { return "You reach for the " + door_name[0] + " and realize its " +
       "already open.\n"; }

string
fail_mess2() 
   { return "The " + door_name[0] + " does not budge. You notice a " +
       "rather small key hole.\n"; }

string
close_mess1() 
   { return "pushes the " + door_name[0] + " closed with a slam.\n"; }

string
close_mess2() 
   { return "You hear the " + door_name[0] + " slam shut. Its darker now.\n"; }

string
standard_lock_mess1() { return "is fussing with the " door_name[0] + 
			  ". You here a faint click.\n"; }

string
standard_fail_lock2() {
  set_lock(1);
  return "You here a soft click in the lock of the open " + door_name[0] + ".";
}

string
standart_unlock_mess1() { return "messes with the " + door_name[0] +
			    ". You here a faint click.\n";}
