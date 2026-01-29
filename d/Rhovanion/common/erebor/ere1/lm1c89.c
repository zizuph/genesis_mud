inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere1/"

create_cave()
{
  
  
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

  add_item("sign",BS(
    "The sign reads:\n"
  + "\n"
  + "Welcome visitor to the broken mug pub, may your visit be ... profitable! "
  + "\n"
  + "\n"));
    
  add_exit(CAVE_DIR + "lm1c47","east",0,1);
  
}

void
init()
{
  ::init(); 
  add_action("push_panel", "push");
}

int
push_panel(string str)
{
  NF("Push what?\n");
  if((str != "panels") && (str != "panel")) return 0;
  tell_room(CAVE_DIR+"lm1c31", QCTNAME(TP)+" arrives from behind the wall east.\n");
  TP->catch_msg("You push the wall slightly making it able for you to enter the other side.\n");
  TP->move_living("M", CAVE_DIR+"lm1c31", 1);
  tell_room(TO, QCTNAME(TP)+" pushes the panel and tumbles into another room.\n");
  return 1;
}
