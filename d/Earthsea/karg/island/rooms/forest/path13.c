#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "../../std/defs.h"

inherit ISL_DIR+"/std/room";

void create_island_room()
{
 set_short("Clearing");
 set_long("You come out of the forest to the clearing. "+
   "All the trees were chopped down here and further "+
   "to the east, so you have a clear view of rocky "+
   "hills starting to rise at some distance from here. "+
   "Finally you can make out the source of smells and "+
   "noises that bothered you whilst in the forest - "+
   "there are two army tents and a campfire between "+
   "them. The path passes the camp and starts climbing "+
   "to the east.\n\n");

 add_exit(FROOMS+"/path14","east");
 add_exit(FROOMS+"/path12","west");

 add_item(({"forest"}),
   "The forest is left to the west, here all the trees "+
   "were chopped down.\n\n");
  add_item(({"tent","tents","camp"}),
   "After a close examination you decide that this "+
   "some sort of lookout camp. The tents are not large, "+
   "made of well-worn canvas, you assume that only a "+
   "small party camps here in order to alarm the main "+
   "forces in case of a threat from within the forest. "+
   "Between the tents there is a campfire.\n\n");

 add_item(({"campfire","fire"}),
   "A small fire is set between the tents, there is "+
   "a rusty pot with something brewing in it. "+
   "Considering the smell, there must be no good cook "+
   "for miles and miles around. Few blankets are "+
   "thrown on the ground around the fire.\n\n");

 add_item("second tent","Second tent is larger then first one , it "+
   "looks like someone important may be in there.\n");
}

void init()
{
 ::init();
 add_action("enter_tent","enter");
}

int enter_tent(string s)
{
 NF("Enter what?\n");
 if(!s) return 0;

 if(s=="tent" || s=="first tent")
  {
   say(QCTNAME(TP)+" disappears into the tent.\n\n");
   TP->move_living("M",FROOMS+"/tent1");
   say(QCTNAME(TP)+" enters the tent.\n\n");
   return 1;
  }
 if (s=="second tent")
  {
   say(QCTNAME(TP)+" disappears into the tent.\n\n");
   TP->move_living("M",FROOMS+"/tent2");
   say(QCTNAME(TP)+" enters the tent.\n\n");
   return 1;
  }

 NF("You put your head inside "+s+" but your body is stuck"+
   ". No way you are going to get inside...\n\n");
 return 0;
}

