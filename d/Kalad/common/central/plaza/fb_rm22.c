/*
ROOM: Fire Brigade second floor emergency sliding pole
BY:   Sebster
DATE: Aug 28, 1994
*/

inherit "/d/Kalad/room_std";

#include "/d/Kalad/defs.h"

void
create_room()
{
  ::create_room();
  hear_bell = 2;
 
  add_prop(ROOM_I_INSIDE, 1);
  
  set_short("The second floor emergency sliding pole");
  set_long(
    "This room contains the emergency sliding pole. You could probably "+
    "slide down here. There is also a window looking over the town "+
    "square, where you can see the ugly monument standing proud as "+
    "ever. @@get_gnome@@\n"
  );
  
  add_prop(ROOM_NO_TIME_DESC, 1);
  
  add_exit(CENTRAL(plaza/fb_rm21), "north", 0, 0, 0);
  
  add_item("pole", 
    "A slippery pole which lets the firemen go quickly to the disaster "+
    "area. The last time it was used by one of the firemen, the fire "+
    "brigade itself was on fire.\n"
  );
  
  add_item("window", "A small gothic window.\n");

  add_cmd_item(({"down", "down pole", "pole"}), "slide", "@@slide");
  add_cmd_item("pole", "enter", "@@slide");
}

string
slide()
{
  write("You slide down the pole to the ground floor!  Wheeeeee...\n");
  TP->move_living("down the pole", CENTRAL(plaza/fb_rm11));
  return "You stand up, the adrenalin still rushing in your blood...\n";
}

string
get_gnome()
{
  if (TIME == 23) return 
    "You a see a door opening in the base of the statue, and a "+
    "small gnome climbing out! Strange...";
  return "There is nothing interesting happening outside.";
}
