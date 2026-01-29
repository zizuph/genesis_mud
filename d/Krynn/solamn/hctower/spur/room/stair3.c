// stair3
// grace sept 1994

#include "../local.h"
inherit SPURRM;

create_spur_room()
{
   SHORT("Stair from second floor hallway to lower level");  
   LONG("You stand on a stair halfway between the main hall on " 
      + "the second level of Knights' Spur and a well-lit room "
      + "on the first floor.  You aren't sure, but you think you "
      + "hear the sound of running water.\n");

   INSIDE;
   LIGHT;

   add_exit(ROOM + "stair4","up",0);
   add_exit(ROOM + "arch4", "down",0);
    add_item("water","You can't see anything, but you can hear it.\n");
    add_cmd_item("water",({"listen to","hear"}),BS("The sound of running "
         +   "water seems to echo in this narrow courtyard. You can't "
         +   "decide whether the sound is abrasive or soothing to your "
         +   "ears.",SL));

}                
