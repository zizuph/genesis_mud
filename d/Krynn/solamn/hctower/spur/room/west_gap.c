/* created by Aridor 06/21/93 (for H. C. Tower)
 * modified by Grace 05/31/94 (for Knight Spur)
 *   Knight Spur west_gap   */

inherit "/std/room";

#include "../local.h"


create_room()
{
   set_short("Between the walls of the Knight Spur");
     set_long(BS("You are standing in a narrow courtyard which extends in "
          +   "an east-west direction within the walls of the Knights' Spur."
          +   " A narrow slice of blue sky can be seen between the "
         +   "walls of the fortress rising high above your head. To the "
         +   "east you can hear water running. West there is a monstrous "
        +   "pair of doors standing in the shadow of the High Clerist "
         +   "Tower.",SL));


    add_exit(ROOM + "bridge", "east",0);

    add_item("sky", "It is very blue.\n");
    add_item(({"tower","fortress", "high clerist tower"}),BS("You look up "
         +   "to the tower but you can barely make out its top. The base "
         +   "of the tower is really a solid fortress, standing like a "
         +   "silent guardian watching its surroundings.",SL));
    add_item(({"mountains", "pass"}), BS("The mountains look fierce and  "
         +   "impassible except for the place where the fortress was built "
         +   "here to guard the only pass through the mountains.",SL));
    add_item(({"spur","knight spur","knights spur","knights' spur","wall"}),
          BS("This wall rises twenty man-lengths above you, the same "
         +   "height as the curtain wall of the High Clerist Tower. "
         +   "You can see very little past the battlements.",SL));
    add_item(({"curtain wall", "curtain"}), BS("This wall is the height "
         +   "of 20 men and level with the wall of the Knight Spur. "
         +   "The Tower rises impossibly high above the battlements.",SL));
    add_item(({"battlement", "battlements", "fortification", "parapets"}),
         BS("The parapets of this fortification have regularly spaced "
         +   "merlons and crenels interrupting their walls.",SL));
   add_item("water","You can't see anything, but you can hear it.\n");
   add_item(({"doors","door", "hinges"}),BS("They are made from the wood of "
         +   "vallenwood trees, with huge iron hinges. Their construction "
         +   "would suggest they are barred from the other side.",SL));
   add_cmd_item("water",({"listen to","hear"}),BS("The sound of running "
         +   "water seems to echo in this narrow courtyard. You can't "
         +   "decide whether the sound is abrasive or soothing to your "
         +   "ears.",SL));
    add_cmd_item(({"doors","door"}),({"open","break","push"}),"It is "
         +   "impossible to do that right now.\n");
}
