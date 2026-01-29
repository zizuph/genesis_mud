inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"

create_room()
{
   set_short("A dark cellar in a house.");
   set_long("This dark cellar is full of scattered objects and debris. "+
      "You suppose the human living upstairs has been stealing "+
      "from his fellow Bree-landers. It is rather dark here, and "+
      "you wonder if there is not something living down here.\n");


   add_item(({"objects","object","debris","cellar"}), "You see "+
   "all kinds of things here, pipes, knives, tools, and just plain "+
   "trash.\n");

   add_prop(ROOM_I_INSIDE,1);
   add_prop(ROOM_I_LIGHT,0);

   add_exit(BREE_DIR + "hhouse1","up",0,5);
}
