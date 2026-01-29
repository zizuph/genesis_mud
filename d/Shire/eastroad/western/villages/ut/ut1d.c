#include "../local.h"

inherit SMIAL;

void
create_smial()
{
   
   areaname  = "Undertowers";		/*Name of village*/
   land          = "Westmarch";		/*Name of land   */
   roomtype  = 3;				/*Type of room in the smial   */
   areatype   = "hamlet";			/*Type of village*/
   smialsize   = "small";			/*Size of the house*/
   
   extraline = "A small unused looking fireplace is mounted on the "+
   "east wall, and the west wall features a large round window.";

   add_item(({"small fireplace","unused fireplace","fireplace","fire place"}),
   "This small fireplace looks as if it is meant for a back-up cooking "+
   "location to the kitchen, rather than a source of heat.\n");

   add_item("window","Looking through the window, you can "
      +"see the "+areatype+" of "+areaname+".\n");
  
   add_exit(UT_DIR + "ut1c","north");
   add_exit(UT_DIR + "ut1e","south");
}
