/* created by Aridor 06/21/93 */

#include "../local.h"

inherit OUTSIDE_BASE;

#include <macros.h>

void
create_splains_room()
{
   set_short("Under the bridge");
   set_long("You are on a narrow ledge under the bridge crossing the " +
      "river. You realize that you are on the east side of the river " +
      "and there is a crack leading into the wall securing the river " +
      "bank to your east.\n");
   add_item("crack",
      "It's a crack, but looks just wide enough for you to enter.\n");
   add_item(({"stones","ledge"}),
      "Its a narrow ledge you are standing on made from stones. The " +
      "water is west of you and a wall is east of you.\n");
   add_item(({"wall","bank","river bank"}),
      "The wall is the base of the bridge and it is made from " +
      "stones. It also secures the river bank and there is a crack " +
      "in the stones to your east.\n");
   add_item(({"river"}),
      "It's not a very wide river, and the waterlevel is much lower " +
      "than the plains. The river is west of you.\n");
   add_cmd_item(({"in river","in the river","into river","into the river",
            "the river","river"}),
      ({"swim","enter","jump"}), "@@jump_into_the_river");
   add_prop(ROOM_I_TYPE, ROOM_BEACH);
   add_cmd_item(({"into the crack","into crack","the crack","crack"}),
      ({"enter","climb"}),"@@enter_crack");
}

string
jump_into_the_river()
{
   set_dircmd("river");
   write("You jump into the river.\n");
   TP->move_living("jumping into the river", ROOM + "in_water6",1,0);
   return "";
}

string
enter_crack()
{
   set_dircmd("crack");
   write("You climb into the crack.\n");
   TP->move_living("into the crack",ROOM + "secret1");
   return "";
}
