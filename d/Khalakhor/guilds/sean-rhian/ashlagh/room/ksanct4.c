// in the village kirk
#include "defs.h"
inherit  ROOM+"ksanct";
 
void create_khalakhor_room()
{
   extra="You are at the north end of the sanctuary.";
   create_ksanct();
   add_item("fourth window",
      "It is a stained glass window set in the arched wall to the "+
      "northwest. "+wd[3]+"\n");
   add_item("fifth window",
      "It is a stained glass window set in the arched wall to the "+
      "north. "+wd[4]+"\n");
   add_item("sixth window",
      "It is a stained glass window set in the arched wall to the "+
      "northeast. "+wd[5]+"\n");
   add_item(({"statue","perch","angel"}),
      "There is a statue of an angel standing on a perch, sort of a "+
      "pedestal set on the wall above the fifth window in the north "+
      "apex of the sanctuary. The angel holds a book in one hand and "+
      "a trumpet in the other. His wings span high above his head.\n");
 
   add_exit("ksanct1","southwest");
   add_exit("ksanct2","south");
   add_exit("ksanct3","southeast");
}
