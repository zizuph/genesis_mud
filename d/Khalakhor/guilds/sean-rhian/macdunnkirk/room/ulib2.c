// Kirk of Port City - Abbey Library - upper level (private)
//
// History:
// Date        Coder       Action
//----------   ----------- ----------------------------------
// 7/20/98      Zima        Created
//
//
#include "defs.h"
inherit  ROOM+"ulib";
 
void create_khalakhor_room()
{
   create_library("north","",1);
 
   add_exit("ulib4", "south");
   add_exit("ulib3", "east");
   add_exit("ulib1", "west");
   shelf->add_books(({
      SR_BOOK+"novishagh",
      SR_BOOK+"searmanagh",
      SR_BOOK+"diaghin",
      SR_BOOK+"saggart",
      SR_BOOK+"presbytair"
      }));
}
