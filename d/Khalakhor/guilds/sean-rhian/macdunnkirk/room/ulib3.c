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
   create_library("north","",1);
 
   add_exit("ulib5", "south");
   add_exit("ulib2", "west");
   shelf->add_books(({
      SR_BOOK+"canticles"
      }));
}
