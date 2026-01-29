/* created by Aridor 06/21/93 (for H. C. Tower)
 * modified by Grace 05/31/94 (for Knight Spur)
 *   Knight Spur east_gap    */

inherit "/std/room";

#include "../local.h"

create_room()
{
    set_short("Between the walls of the Knight Spur");
    set_long( "You are standing in a narrow courtyard which extends"
	+ 	" in an east-west direction within the walls of the Knights' "
         +   "Spur. A narrow slice of blue sky can be seen between the "
         +   "walls of the fortress rising high above your head. To the "
         +   "west you can hear water running. The tunnel continues "
         +   "northwest, into darkness.\n");


   add_exit(ROOM + "hall7","northwest",0);
   add_exit(ROOM + "frontdoor","southeast",0);   
    add_exit(ROOM + "bridge", "west",0);

    add_item(({"hallway", "tunnel"}), "The hallway extends to the northwest "
         +   "and southeast. It is too dark inside to see much else.\n");
    add_item("sky", "It is very blue.\n");
    add_item(({"tower","fortress", "high clerist tower"}), "You look up "
         +   "to the tower but you can barely "
         +   "make out its top. The base of the tower is really "
         +   "a solid fortress, like a silent guardian watching its "
         +   "surroundings.\n");
    add_item(({"mountains", "pass"}),  "The mountains look fierce and  "
         +   "impassible except for the place where the fortress was built "
         +   "here to guard the only pass through the mountains.\n");
    add_item(({"spur","knight spur","knights spur","knights' spur","wall"}),
             "This wall rises twenty man-lengths above you, the same "
         +   "height as the curtain wall of the High Clerist Tower. "
         +   "You can see very little past the battlements.\n");
    add_item(({"curtain wall", "curtain"}),  "This wall is the height "
         +   "of 20 men and level with the wall of the Knight Spur. "
         +   "The Tower rises impossibly high above the battlements.\n");
    add_item(({"battlement", "battlements", "fortification", "parapets"}),
             "The parapets of this fortification have regularly spaced "
         +   "merlons and crenels interrupting their walls.\n");
   add_item("water","You can't see anything, but you can hear it.\n");
   add_cmd_item("water",({"listen to","hear"}), "The sound of running "
         +   "water seems to echo in this narrow courtyard. You can't "
         +   "decide whether the sound is abrasive or soothing to your "
         +   "ears.\n");

    add_prop("_room_i_allow_steed", 1);
}



 
