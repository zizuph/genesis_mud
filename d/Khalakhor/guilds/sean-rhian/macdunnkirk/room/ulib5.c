// Kirk of Port City - Abbey Library - upper level (private)
//
// History:
// Date        Coder       Action
//----------   ----------- ----------------------------------
// 7/20/98     Zima        Created
//
//
#include "defs.h"
inherit  ROOM+"ulib";
 
void create_khalakhor_room()
{
   create_library("south","",1);
 
   add_exit("ulib3", "north");
   shelf->add_books(({
      SR_BOOK+"canticles"
      }));
}
