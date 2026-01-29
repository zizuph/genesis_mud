/*This is just a normal room with a fence in it(gate)*/
/* Created by Dorak*/

#include "local.h"
#include "/d/Krynn/common/defs.h"
#include "/sys/macros.h"

inherit OUTSIDE_BASE;

int hidden;

create_solace_room()
{
    set_short("An Old Fence");
    set_long("This an old weather worn wrought iron fence.  It runs from\n" +
	     "west to east.  There are brambles all around that keep you\n"+
	     "from going north.\n");
    
    add_item(({"fence", "wrought iron fence", "old fence"}),
             "This is a tall old wrought iron fence.  It is painted black,\n" +
             "but the paint is peeling and the fence is very rusty.  \n");
    add_item("brambles",
             "These brambles have very long thorns that look very sharp. \n"+
             "You couldn't possibly go into the thick of them to the north\n");
    
    add_cmd_item("fence", "climb", "@@climb_fence");
    
    add_exit(TDIR + "fence0", "west", "@@west_msg");
    add_exit(TDIR + "fence2","east", 0);     
    
    LIGHT;
    hidden = 0;
}

void
reset_solace_room() 
{
    remove_exit("south");
    hidden = 0;
}  

static string
climb_fence()
{
    if (!hidden) 
      {
	  say(QCTNAME(this_player()) + "has climbed the fence.\n");
	  this_object()->add_exit(TDIR + "a_grave0", "south", "@@jump");
	  hidden = 1;
	  this_object()->init();
	  return("From the top of the fence you can now go south .\n");
      }
    else
      return("You can't quite get yourself to jump off the fence to the\n" +
	     "south, so you climb back down on the same side\n" +
	     "that you started from.\n");
}

int
jump() 
{
    write("You jump down from the fence, sprawling face first on the\n" +
          "ground, oops north side, your ego more bruised then your body.\n");
    return 1;
}

int
west_msg()
{  
    write("Well, maybe there is more to this graveyard after all!!\n");
    return 0;
}
