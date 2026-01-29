/* created by Aridor 06/21/93 (for H. C. Tower)
 * modified by Grace 05/31/94 (for Knight Spur)
 *   Knight Spur Bridge   */

inherit "/std/room";

#include "../local.h"


create_room()
{
    set_short("On a bridge between the walls of the Knight Spur");
    set_long("You are standing on a bridge spanning the aquaduct. "
         +   "A narrow courtyard can be seen extending on either side "
         +   "in an east-west direction. The fortress walls rise high "
         +   "above you, with the High Clerist Tower casting its "
         +   "shadow over the bridge.\n");


    add_exit(ROOM + "east_gap","east",0);
    add_exit(ROOM + "west_gap", "west",0);

    add_item("sky", "It is very blue.\n");
    add_item(({"tower","fortress", "high clerist tower"}), "You look up "
         +   "to the tower but you can barely "
         +   "make out its top. The base of the tower is really "
         +   "a solid fortress, like a silent guardian watching its "
         +   "surroundings.\n");
    add_item(({"mountains", "pass"}), "The mountains look fierce and  "
         +   "impassible except for the place where the fortress was built "
         +   "here to guard the only pass through the mountains.\n");
    add_item(({"spur","knight spur","knights spur","knights' spur","wall"}),
             "This wall rises twenty man-lengths above you, the same "
         +   "height as the curtain wall of the High Clerist Tower. "
         +   "You can see very little past the battlements.\n");
    add_item(({"curtain wall", "curtain"}), "This wall is the height "
         +   "of 20 men and level with the wall of the Knight Spur. "
         +   "The Tower rises impossibly high above the battlements.\n");
    add_item(({"battlement", "battlements", "fortification", "parapets"}),
             "The parapets of this fortification have regularly spaced "
         +   "merlons and crenels interrupting their walls.\n");
    add_item("aquaduct", "Roughly two man-lengths in width, it is "
         +   "barred by portcullises to prevent enemy entrance into "
         +   "the fortress.\n");
    add_item(({"portcullis","portcullises"}),"They are made of steel "
        +   "and look to be very sturdy.\n");
    add_item("bridge", "It is sturdy and made of stone.\n");
    add_item("water","It rushes thru the aquaduct.\n");
    add_item("courtyard","It looks like a narrow courtyard.\n");

    add_cmd_item("water",({"listen to","hear"}), "The sound of running "
         +   "water seems to echo in this narrow courtyard. You can't "
         +   "decide whether the sound is abrasive or soothing to your "
         +   "ears.\n");
    add_cmd_item(({"stream", "aquaduct", "water"}),({"enter", "swim", "cross"}),
             "The water flows too quickly for you to do that here.\n");
    add_cmd_item("portcullis",({"lift","raise","open"}),
              "You can't do that from here.\n");
}
