// in the village kirk
#include "defs.h"
inherit  ROOM+"ksanct";
 
void create_khalakhor_room()
{
   extra="You are in the southwestern corner of the sanctuary.";
   create_ksanct();
   add_item("first window",
      "It is a stained glass window set in the arched wall to the "+
      "west. "+wd[9]+"\n");
   add_item("second window",
      "It is a stained glass window set in the arched wall to the "+
      "west. "+wd[1]+"\n");
   add_item("third window",
      "It is a stained glass window set in the arched wall to the "+
      "northwest. "+wd[2]+"\n");
   add_item(({"second tapestry","right tapestry","tapestry"}),
      "The second tapestry which hangs to the right of the entrance "+
      "is made of colored wool threaded to portray nine manachs "+
      "standing in a circle around a large fire. Each is tossing a "+
      "tree branch into the fire and seems to be singing. There is "+
      "an inscription woven along the top of the tapestry.\n");
   add_item("inscription",
      "It is woven along the top of the second tapestry hanging "+
      "to the right of the entrance to the south. Perhaps you could "+
      "read it.\n");
   add_cmd_item("inscription","read",
      "Invoke the cleansing fires of Ardaugh\n");
   add_exit("ksanct2","east");
   add_exit("ksanct4","northeast");
}
