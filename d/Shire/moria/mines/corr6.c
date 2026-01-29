#include "defs.h"

int washed;

CONSTRUCT_ROOM 
{
    washed = 0;
    set_short("The end of the corridor");
//    set_long("The corridor end here, due to a peculiar looking wall.\n");
    set_long("The end of the corridor. It runs west and south. The " +
        "corridor ends at the east wall at an iron gate. It is closed.\n");
    EXIT("corr5", "west");
    add_item("corridor", 
	     "It is a vast corridor. It was carved centuries ago by the dwarves.");
    add_item(({"moisture"}), 
	     "It is rivulets of water. They trickle down the walls and disappear.\n");
    add_item(({"walls","wall"}),
        "The walls are smooth, carved into the rock by dwarves centuries ago.\n");
//    add_item(({"hole","keyhole"}),"@@hole@@");
    add_item(({"gate", "iron gate"}),
        "The gate is enormous and set into the east wall. It is heavy " +
        "and forged of iron by the dwarves ages ago. The gate is closed.\n");
    SOUTH("dirthole");
}

RESET_ROOM 
{
    washed = 0;
}

init() {
    ::init();
//    add_action("my_wash","wash");
}

my_wash(arg) 
{
  if (!arg) 
  {
    notify_fail("Wash what?\n");
    return 0;
  }
  if (arg == "wall") 
  {
    write("Nah, nothing seems to happen now. (Future feature.)\n");
    return 1;
  }
}

string
wall() 
{
  if (washed)
    return "The wall seems to be newly washed. There is a keyhole in the "+
	   "wall.\n";
  else 
    return "It seems very dirty.\n";
}

string
hole() {
  if (!washed)
    return "What ?\n";
  else 
    return "You probably could put a key in it, but which key?\n";
}

#ifdef 0      

// It is not needed any more. Kept however.
//    add_item("curtain",
//	     "It is the exit out of the Mines, since it is not finnished. "+
//	     "Just enter it, and you will end up in the village.");              
//    add_action("go_home","enter");
int
go_home(string str) {
  if (!str) {
    notify_fail("Enter what?\n");
    return 0;
  }
  if (str == "curtain") 
  {
    if (random(2)) 
    {
      this_player()->move_living("X", "/d/Shire/common/hollin/f0000");
      return 1;
    } 
    else 
    {
      this_player()->move_living("X", "/d/Shire/common/hollin/f0101");
      return 1;
    }
  }
}
#endif
