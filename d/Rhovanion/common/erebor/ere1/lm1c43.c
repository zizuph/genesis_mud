inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere1/"

create_cave()
{
  
  object door;
  
  set_rock_type("cold grey granite");
  set_cave_name("the Lonely Mountain");
  set_region("northern");
  set_cave("Erebor");
  set_cave_type(1);
  set_long(" "
         + " "
         + " "
         + " "
         + " "
         + " "
         + " "
         + " ");
  
  add_item("wall", "There is a shiny spot just big enough to fit your hand "
       + "upon, on the wall.\nSeems like someone must have pushed the wall "
       + "there many times.\n");
  
  door = clone_object(CAVE_DIR + "door_lm1c43.c");
  door->move(TO);
  
  add_exit(CAVE_DIR + "lm1c45","south",0,1);
 
  
}

void
init()
{
  ::init(); 
  add_action("push_wall", "push");
}

int
push_wall(string str)
{
  NF("Push what?\n");
  if((str != "walls") && (str != "wall")) return 0;
  tell_room(CAVE_DIR+"lm1c41", QCTNAME(TP)+" arrives from behind the wall east.\n");
  TP->catch_msg("You push the wall slightly making it able for you to enter the other side.\n");
  TP->move_living("M", CAVE_DIR+"lm1c41", 1);
  tell_room(TO, QCTNAME(TP)+" pushes the wall and tumbles into another room.\n");
  return 1;
}
