/****************************************/
/*   Staff Bathroom of Icewall Castle*/
/*       Coded by Steve*/
/****************************************/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>

inherit ICEINROOM;

create_icewall_room()
{
   set_short("Staff Bathroom");
   set_long("\nYou are in a small bathroom which is amazingly "
      + "free of any dirt.  You notice a small washbasin with a pitcher "
      + "of fresh water nearby and a small door built into the floor ("
      + "probably better to leave closed).\n");
   
   add_item(({"washbasin","basin"}),"The basin is made of steel "
      + "and is used primarily for cleaning oneself.\n");
   add_cmd_item("pitcher",({"use","pour","get"}),"It is a medium-sized "
      + "pitcher.  Judging that the water is clean you pour it "
      +" into the basin and wash yourself thoroughly.\n");
   add_cmd_item("door","open","\nPHHHHHHHEEEEEEEEEEEEEWWWWWWWWWW!!!!!!!\n"
      + "\nSo now you know what the door is really for.  It is best to "
      + "not open it again.\n");
   add_item("pitcher","It holds water for pouring into the basin.\n");
   add_item("door","Well, what else do you think it would be for?\n");
   
   
   add_exit(ICE_CAST1_R + "west_corner.c", "south");
}
