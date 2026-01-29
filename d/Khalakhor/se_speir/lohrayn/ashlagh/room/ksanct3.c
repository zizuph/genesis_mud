// in the village kirk
#include "defs.h"
inherit  ROOM+"ksanct";
 
void create_khalakhor_room()
{
   extra="You are in the southeastern corner of the sanctuary.";
   create_ksanct();
   add_item("seventh window",
      "It is a stained glass window set in the arched wall to the "+
      "northeast. "+wd[6]+"\n");
   add_item("eighth window",
      "It is a stained glass window set in the arched wall to the "+
      "east. "+wd[7]+"\n");
   add_item("ninth window",
      "It is a stained glass window set in the arched wall to the "+
      "east. "+wd[8]+"\n");
   add_item(({"tapestry","first tapestry","left tapestry"}),
      "The first tapestry which hangs to the left of the entrance "+
      "is made of colored wool threaded to portray nine unique "+
      "figures sitting in a circle in a stone house. Their faces are "+
      "filled with surprise as a tall glowing angel appears in their "+
      "midst.\n");
   add_exit("ksanct2","west");
   add_exit("ksanct4","northwest");
}
 
