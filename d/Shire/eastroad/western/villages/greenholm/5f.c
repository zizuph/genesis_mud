inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


#include "../local.h"

#define EXIT1 ER_BASE_DIR + "village/greenholm/5d","north",0,1

void
create_room()
{
   
   areaname  = "Greenholm";		/*Name of village*/
   land          = "the Shire";		/*Name of land   */
   roomtype  = 10;				/*Type of room in the smial   */
   areatype   = "hamlet";			/*Type of village*/
   smialsize   = "large";			/*Size of the house*/
   
   extraline = "The shelves are filled with sacks of flour and grains.";
   add_item("shelves",
	"The hobbits store their food here.\n");
   add_item("sacks",
	"These sacks are full of flour and rice and other wonderful "
	+"things. You don't think you can scarf down a whole bag of "+
   "dry grains though.\n");
    add_item("food",
	"Your mouth waters at the sight of all this food. However, "
	+"you decide to leave it alone.\n");
 
   add_exit(EXIT1);

   make_the_room();
}


