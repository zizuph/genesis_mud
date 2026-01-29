#include "outroom.h"

create_outroom()
{
  set_short("Tall white tree");
  set_long("You are standing at the foot of the tall white tree.\n"+
	   "Steep slopes prevents to the east and the north, and the plain extends "+
	   "westwards and southwards. You might also be able to climb up the tree. ");
  ADD_EXA("tree","This is a tall white tree with thick leaves.");
  ADD_EXA("leaves","Indeed, thick and green they are.");
  ADD_EXA("slopes,slope","Obviously too steep to climb.");
  ADD_EXA("plain","The plain extends west and south.");
  
  WEST("plain_n"); SOUTH("under_wall"); UP("tree");
}

init() {
  ::init();
  add_action("climb","climb");
  add_action("cut","cut");
}

climb(str) {
  if(str=="up"||str=="tree") {
    this_player()->command("up");
    return 1;
  }
  else if(str=="slope"||str=="slopes")
    notify_fail("You try, but fail.\n");
  else
    notify_fail("Climb where?\n");
  return 0;
}
	
cut(str) {
  if(str=="tree") 
    return notify_fail("Now, why would you like to do that?\n");
  else 
    return notify_fail("Cut what?\n");
}				  
