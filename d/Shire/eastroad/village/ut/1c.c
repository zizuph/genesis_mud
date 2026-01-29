inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


#include "../local.h"

#define EXIT1 ER_BASE_DIR + "village/ut/1","north",0,1
#define EXIT2 ER_BASE_DIR + "village/ut/1d","south",0,1

void
create_room()
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

   add_exit(EXIT1);
   add_exit(EXIT2);

   make_the_room();
}
