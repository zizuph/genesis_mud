#include "defs.h"
inherit THWIL_BASE_ROOM;

object sheep;
void create_thwil_room()
{
   set_short("Street");
   set_long("The hill is quite steep here and you feel tired. "+
      "To the left and right you see houses with sharp "+
      "slate roofs. Some of the roofs have waist high "+
      "grass swaying on them. "+
      "To the west you see an intersection. "+
      "To the east, the hill slopes away towards the harbour.\n");
   
   add_exit(THWIL + "t3" , "west" , 0, 2);
   add_exit(THWIL + "t1" , "east" , 0, 2);
   
   STREET;
}

void
reset_room()
{
   if (!objectp(sheep))
      {
      sheep->clone_object(THWIL + "monster/sheep");
      sheep->move_living("arrives", this_object());
   }
}
