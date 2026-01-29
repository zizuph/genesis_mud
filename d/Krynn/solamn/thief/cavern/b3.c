/* created by Aridor 02/09/94 */

#include "../local.h"

inherit ROOM_BASE

#include <cmdparse.h>
#define THIS_ROOMS_VALUE   8

object *unlocked = ({ });

void
create_thief_room()
{
    set_short("In a hall.\nThere is one obvious exit: south");
    set_long("This is the end of a hallway. The walls, floor and ceiling " +
	     "are smooth stone, and the hallway continues to the south.\n" +
	     "There is a stone door leading north.\n"+
	     "There is one obvious exit: south.\n");
    
    set_noshow_obvious(1);
    add_exit(CAVERN + "b5","south");
    add_exit(CAVERN + "b3","north","@@door_closed");
    
    DARK;

    add_item("door",
	     "It is a sturdy stone door. You notice the door has a " +
	     "keyhole. The door is set into the wall and fits perfectly.\n");
    add_item("keyhole",
	     "It looks like a key would fit there.\n");
    add_cmd_item(({"door","lock"}),({"pull","open"}),"@@solved_this");
    add_cmd_item(({"door","lock"}),({"close","shut"}),"The door is already closed.\n");
    add_cmd_item(({"door","lock"}),"unlock","@@unlock_door");
    add_cmd_item(({"door","lock"}),"lock","@@lock_door");
}

string
solved_this()
{
    if (member_array(TP,unlocked) != -1)
      {
	  write("You pull hard, but it seems like the door doesn't want " +
		"to be opened. All you hear is " +
		"a remote click, but the door won't budge.\n");
	  SAY(" tries to open the door, but only makes a lot of noise.\n");
	  if (!sizeof(TP->query_team_others()))
	    TP->add_prop(THIEF_I_CAN_ENTER, 
			 TP->query_prop(THIEF_I_CAN_ENTER) | THIS_ROOMS_VALUE);
	  return "";
      }
    else
      {
	  write("You pull hard, but it seems like the door doesn't want " +
		"to be opened. The door just won't budge. Maybe it's locked?\n");
	  SAY(" tries to open the door, but only makes a lot of noise.");
	  return "";
      }
}

string
lock_door()
{
    if (!sizeof(FIND_STR_IN_OBJECT("key",TP)))
      return "You don't seem to have a key that fits.\n";
    SAY(" fumbles with the door.");
    if (member_array(TP,unlocked) != -1)
      {
	  unlocked -= ({ TP });
	  return "You lock the door with a key you found in your inventory.\n";
      }
    return "The door seems locked already.";
}

string
unlock_door()
{
    if (!sizeof(FIND_STR_IN_OBJECT("key",TP)))
      return "You don't seem to have a key that fits.\n";
    SAY(" fumbles with the door.");
    if (member_array(TP,unlocked) == -1)
      {
	  unlocked += ({ TP });
	  return "You unlock the door with a key you found in your inventory.\n";
      }
    return "The doors seems unlocked already.\n";
}

int
door_closed()
{
    write("The door is closed.\n");
    return 1;
}

