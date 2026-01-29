/* A door in the Solace Graveyard
 * zd_mound_o.c
 * Dorak 07-04-95
 * a small round door leading out of zmound_entr.c
 */


inherit "/d/Krynn/solace/graves/obj/zd_mound_i";
#include "/d/Krynn/common/defs.h"
#include "../local.h"

create_door()
{
    ::create_door();

    set_other_room(TDIR + "zo_grave3");
    set_close_desc("There is a small round tightly closed door set into " +
		   " the wall here.");
    set_pass_command(({"exit", "exit mound", "leave", "leave mound", "out"}));
    set_open_command(({"push door open", "push the door open", 
		  "push round door open", "push the round door open",
		  "push small round door open", 
		  "push the small round door open"}));
    set_close_command(({"pull door closed", "pull the door closed", 
		  "pull round door closed", "pull the round door closed",
		  "pull small round door closed", 
		  "pull the small round door closed"}));
    set_lock_desc("There is a small key hole in the middle of a worn patch.");
    
}

look_door()
{
  write("This is a small round iron door.  It is set into the wall just" +
	"a bit.  There is a shiney patch on the left side.  There is a " +
	" small key hole in the middle of this patch.  It is otherwise " +
	"quite plain.\n");
  say(QCTNAME(TP) + " looks at the door.\n");
  return "";
}

door_open()
{
  write("You see an open doorway.  Natural light is streaming in. " +
	" You see the edge of the open door where its hinges are.  " +
	"The door is swung open, outward.\n");
  say(QCTNAME(TP) + " looks at the doorway.\n");
  return "";
}

string
open_mess1() 
   { return "pushes the " + door_name[0] + " wide open.\n"; }

string
close_mess1() 
   { return "pulls the " + door_name[0] + " closed with a slam.\n"; }

string
close_mess2() 
   { return "You hear the " + door_name[0] + " slam shut.\n"; }

string
standard_fail_lock2() { return "The " +  door_name[0] + " is open," +
			  " swinging outward. You can't lock it from here."; }
