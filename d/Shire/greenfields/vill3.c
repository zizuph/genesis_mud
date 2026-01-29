inherit "/d/Shire/eastroad/std/vill_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 GREEN_DIR + "vill2","south",0,1
#define EXIT2 GREEN_DIR + "burrow/2","east",0,1


void
create_village_room()
{
   areaname = "Greenfields";
   land = "the Shire";
   areatype = 2;
   areadesc = "twisty path";
 
   extraline = "The gravel path makes a sudden stop here as the center of the "+
   "hamlet of Greenfields seems to be to the south.  The hills around form a "+
   "natural barrier against all other ways of exit, and most are too steep for hobbit "+
   "burrows to be built from, except to the east.";

   add_item(({"path","gravel path"}),
   "The gravel path ends here.\n");

   add_item(({"center","hamlet","greenfields"}),
   "The center of the hamlet Greenfields is to the south.\n");

   add_item(({"hills","hill","barrier"}),
   "The hills here form a three-sided box preventing egress to all directions "+
   "but south.\n");

   add_exit(EXIT1);
   add_exit(EXIT2);
}
