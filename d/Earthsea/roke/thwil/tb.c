#include "defs.h"
inherit THWIL_BASE_ROOM;

int no_pass()
{
  write("An invisible barrier has been erected by the Wizards of Roke. " +
	"It looks like there's some construction going on there. " +
	"Maybe you should try back later.\n");
  return 1;
}

void create_thwil_room()
{
   set_short("Street");
   set_long("This is an ordinary street in Thwil. "+
      "The air is cold and damp. To the north you spot "+
      "a post office. The town continues to the east and west.\n");
   
   add_exit(THWIL + "post_office" , "north", 0);
   add_exit(THWIL + "t5" , "east", 0);
   add_exit(THWIL + "place_holder", "west", &no_pass());
   
   STREET;
}
