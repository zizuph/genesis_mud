inherit "/std/room";
#include "/d/Cirath/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Cirath/tyr/tyr.h"
#include "defs.h"

 
create_room()
 {
  set_short("End of Hall");
  set_long("The hallway ends here rather abruptly.  The northeastern wall "
	+"has a large painting on it that reaches from floor to ceiling "
	+"and covers the entire wall.  Other than that there is nothing "
	+"else here except the familiar globes that light the house.\n");
  add_item(({"globe","globes"}),"They are roughly six inches in diameter "
	+"and provide light equivalent to that of a torch.\n");
  add_item(({"painting","picture"}),"This is a large portrait of Lord "
	+"Minthor.  It depicts him standing in long purple robes, under "
	+"which a gleaming suit of fine chainmail can be seen.  He also "
	+"has some sort of scepter in one hand and a long spear in the "
	+"other.  The frame of the picture is made out of some strange "
	+"material that you can't quite identify from this distance.\n");
  add_item(({"wall","walls"}),"The walls stretch out around you.\n");
  add_item(({"frame","frame of the picture"}),"The frame looks to be "
	+"be crafted from some sort of crystal interwoven with metal.  "
	+"It must have cost a fortune to produce such a thing.  While "
	+"running your fingers along it, you notice a small switch "
	+"which seems to be pressable.\n");
   add_item("switch","It looks to be cannily crafted into the frame "
	+"and appears to be pressable.\n");
  add_cmd_item("switch","press","You gently depress the switch and with "
	+"a click, the painting swings inward, revealing a staircase.  "
	+"You believe you can enter the staircase.\n");
  add_cmd_item("staircase","enter","@@enter");
  INSIDE
   add_exit(TZ_MINTHOR + "mh32","southwest");
}

enter()
{
    write("You step onto the staircase.\n");
  say(QCTNAME(TP)+" steps through the picture frame into a "
	+"concealed staircase after pressing a switch on the frame.\n");
    set_dircmd("staircase");
  TP->move_living("steps onto the hidden staircase.",TYR+"minthor/stairs");
    return 1;
}

