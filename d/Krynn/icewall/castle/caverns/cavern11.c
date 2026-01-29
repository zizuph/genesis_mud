/*Created by Stevenson*/
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;

create_icewall_room()
{
   set_short("Small Whirlpool");
   set_long(
	"You have entered what adventurers claim to be the source for "
+ "the underground lake of Icewall. Water cascades down the west wall "
+ "from above and a small whirlpool in the center of the room most "
+ "likely carries the water to the lake. "
         +"\n");
   
add_item("ceiling","It is high above you.\n");
add_item("water","It falls from the ceiling and is the source for the "
+ "underground lake.\n");
add_item("whirlpool","It is in the center of the room.\n");
add_cmd_item("whirlpool","enter",VBFC("go_pool"));

   add_exit(CAVERNS + "cavern12.c", "east");
}

string go_pool() {
   write("You dive under the water and swim down through the hole.\n");
say(QCTNAME(TP)+" pinches " + POSSESSIVE(TP) + " nose and dives into "
+ "the whirlpool.\n");
tell_room(CAVE+"cavern17",QCTNAME(TP)+" slides out of the hole and "
+ "lands in the water with a loud splash.\n");
tell_room(CAVE+"cavern_18","You hear a loud splash to the west.\n");
tell_room(CAVE+"cavern_6","You hear a loud splash to the south.\n");
TP->move_living("M",CAVE+"cavern17",1); /* don't follow */
return "";
}
