// stair5
// grace sept 1994

#include "../local.h"
inherit SPURRM;

create_spur_room()
{
   SHORT("Southwest stair, level one");  
   LONG("You stand at the base of a stair leading up to the central " 
      + "hall on the second level of the Knights' Spur.\n");

   INSIDE;
   LIGHT;

    add_exit(ROOM + "stair6", "up",0);
    clone_object(SOBJ + "l1d1b")->move(TO); 

    add_item("water","You can't see anything, but you can hear it.\n");
    add_cmd_item("water",({"listen to","hear"}),BS("The sound of running "
         +   "water seems to echo in this narrow courtyard. You can't "
         +   "decide whether the sound is abrasive or soothing to your "
         +   "ears.",SL));

}                


