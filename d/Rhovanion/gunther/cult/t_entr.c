inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"
#include <macros.h>
#include "cult.h"

init()
{
    ::init();
    add_action("rever_morgoth", "rever");
    add_action("rever_morgoth", "kneel");
}

create_room()
{
    set_short("Cult temple entrance.\n");
    set_long("You stand before a majestic underground temple. This hall seems"+
	     " to be the entrance chamber. The room is cut from the mountain"+
	     " itself, and the walls are lined with ore in places. A vague"+
	     " luminescence hangs in the air casting shadows in every direc"+
	     "tion. The room is dominated by a huge dark"+
	     " looming figure. You can sense the power of the figure clearly."+
	     " It's massive husk barely fits into the room even though the "+
	     "ceiling seems to hang high above. It seems to be alive yet"+
	     " somehow you feel that it is not. To the northwest you can see "+
	     "a small unholy shrine behind the figure, and to the northeast "+
	     "a corridor seems to lead further into the temple.\n");
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    
    add_item(({"walls", "wall", "ceiling", "floor"}),
	     "The room is cut from the mountain itself, yet the surfaces seem"+
	     " flat and unbroken. You wonder who, or perhaps what, could have"+
	     " performed such a feat.\n");
    add_item(({"figure", "morgoth", "statue"}),
	     "Studying the figure you see that it closely resembles Morgoth,"+
	     " Master of Evil and once one of the Valar. It seems almost alive"
	     +" but not quite. You feel it's presence commanding you, forcing"+
	     " you to submit to it and rever it.\n");
    add_item("shrine", "Something unholy flows out of the shrine in an ever-"+
	     "lasting stream of evil. You cannot see into it and tell what"+
	     " is in there however.");
    add_item("corridor", "Wafts of luminescence fill the corridor but it is"+
	     " still too difficult to tell where it leads or what awaits " +
	     "there. It, too, seems cut from the mountain itself.\n");
    
    add_exit(CULT_DIR + "t_cor1", "northeast", "@@chk_corr");
    add_exit(CULT_DIR + "t_shrine", "northwest", "@@chk_rever");
    add_exit(RHUN_DIR + "mountain/outside_temple", "south", "@@rem_rev");
}

chk_rever()
{
  if(!TP->query_prop("_worshipped_morgoth_"))
  {
    write("You sense that the figure will not let you in there until you have"+
     " given it what it wants.\n");
    return 1;
  }

  return 0;
}

chk_corr()
{
  if(chk_rever()) return 1;
  
  if(!TP->query_guild_member("Cult of Morgoth"))
  {
     write("You haven't dedicated yourself enough to Morgoth to be allowed in"+
	" there.\n");
     return 1;
  }
  return 0;
}

rem_rev()
{
  TP->remove_prop("_worshipped_morgoth_");
  return 1;
}

rever_morgoth(string str)
{
  NF("Rever what or whom?\n");
  if(str != "morgoth" && str != "Morgoth" && str != "figure" 
     && str != "statue") return 0;

  TP->catch_msg("You fall down on your knees in reverence of Morgoth.\n");
  tell_room(TO, QCTNAME(TP) + " falls down on " + HIS(TP) + " knees in"
	    + " reverence in front of the figure.\n", TP);

  TP->add_prop("_worshipped_morgoth_", 1);
  return 1;
}

