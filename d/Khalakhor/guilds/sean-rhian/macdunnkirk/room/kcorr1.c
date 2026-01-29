// Kirk of Port City - Corridor
//
// History:
// Date        Coder       Action
//----------   ----------- ----------------------------------
// 5/25/97     Zima        Created
// 7/11/98     Zima        Door added
//
/* inherits/includes */
#include "defs.h"
#include "/d/Khalakhor/guilds/sean-rhian/lib/zdoor.h"
#define  IPATH  ROOM+"kanterm"
inherit  "/d/Khalakhor/guilds/sean-rhian/lib/zoutdoor";
inherit  ROOM+"kcorr";
 
/* room definition */
void create_khalakhor_room()
{
   extra = "There is a heavy oak door which marks an entrance to the "+
           "kirk to the east.";
   init_kcorr("north","south","east","west");
   add_exit("koffice",   "north");
   add_exit("kcorr2",    "west");
 
   setup_outdoor("east", IPATH, ({"door"}),
      "It is a heavy oak door used to secure the kirk during the private "+
      "rites performed by the manachs.",
      "heavy oak door", 0);
 
}

void init()
{
   ::init();
   add_outdoor_actions();
}
