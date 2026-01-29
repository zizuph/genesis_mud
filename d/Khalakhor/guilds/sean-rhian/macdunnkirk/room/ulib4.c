// Kirk of Port City - Abbey Library - upper level (private)
//
// History:
// Date        Coder       Action
//----------   ----------- ----------------------------------
// 7/20/98     Zima        Recoded
//
//
#include "defs.h"
inherit  ROOM+"ulib";
 
void create_khalakhor_room()
{
   create_library("south","",1);
 
   add_exit("ulib2", "north");
   shelf->add_books(({
      SR_BOOK+"smith",
      SR_BOOK+"ossian",
      SR_BOOK+"keophen5",
      SR_BOOK+"keophen4",
      SR_BOOK+"keophen3",
      SR_BOOK+"keophen2",
      SR_BOOK+"keophen1"
      }));
}
