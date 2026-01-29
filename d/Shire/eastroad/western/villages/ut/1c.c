#include "../local.h"

inherit SMIAL;

void
create_smial()
{
   
   areaname  = "Undertowers";		/*Name of village*/
   land          = "Westmarch";		/*Name of land   */
   roomtype  = 4;				/*Type of room in the smial   */
   areatype   = "hamlet";			/*Type of village*/
   smialsize   = "small";			/*Size of the house*/
   
   extraline = "An opening in the wall leads south, to the dining room "+
   "with a small unused fireplace within.";
   add_item(({"dining","dining room"}),
   "The dining room must be where the eating occurs.\n");
   add_item(({"pantry"}),"The pantry is used to hold food-stores.\n");

   add_exit(UT_DIR + "1a","north");
   add_exit(UT_DIR + "1d","south");
}
