inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#include "../local.h"

#define EXIT1 ER_BASE_DIR + "village/ut/5b","north",0,1
#define EXIT2 ER_BASE_DIR + "village/ut/5d","south",0,1

void
create_room()
{
   
   areaname  = "Undertowers";		/*Name of village*/
   land          = "Westmarch";		/*Name of land   */
   roomtype  = 3;				/*Type of room in the smial   */
   areatype   = "hamlet";			/*Type of village*/
   smialsize   = "small";			/*Size of the house*/
   
   extraline = "A small unused looking fireplace is mounted on the "+
   "west wall, and the east wall features a large round window. "+
   "North is the kitchen and south is a drawing room.";

   add_item(({"small fireplace","unused fireplace","fireplace","fire place"}),
   "This small fireplace looks as if it is meant for a back-up cooking "+
   "location to the kitchen, rather than a source of heat.\n");

   add_item("window","Looking through the window, you can "
      +"see the "+areatype+" of "+areaname+".\n");
  
   add_exit(EXIT1);
   add_exit(EXIT2);


   make_the_room();
}
