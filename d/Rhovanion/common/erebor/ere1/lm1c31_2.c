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
  set_cave_type(3);
  set_long("This room is filled with small kegs and large barrels of beer "
         + "everywhere you look you can see nothing but barrels with beer. "
         + "Some shelves have been put up on the walls to support storage of "
         + "bottles, food and merchandise alike. There is a small doorway "
         + "leading west back into the Inn.");

   add_item("shelves", "Simple strong wooden shelves, put up on the walls.\n");
   add_item(({"walls","wall"}), "The walls have been clad with wooden panels, "
         + "to keep out moisture.\n");
         
   add_item(({"panel","panels"}), "Hmm, one of the panels seem rather strange, "
         + "as if it was recently pushed it aside. Maybe you should try "
         + "to push it also?.\n");
   
   add_exit(CAVE_DIR + "lm1c31","west",0,1);
  
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
  tell_room(CAVE_DIR+"lm1c46", QCTNAME(TP)+" arrives from behind the wall "
      + "east.\n");
  TP->catch_msg("You push the panel slightly making it possible for you to"
      + "enter the other side.\n");
  TP->move_living("M", CAVE_DIR+"lm1c46", 1);
  tell_room(TO, QCTNAME(TP)+" pushes the panel and tumbles into another "
      + "room.\n");
  return 1;
}
