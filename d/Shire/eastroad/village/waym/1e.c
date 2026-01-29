inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "../local.h"

#define EXIT1 ER_BASE_DIR + "village/waym/1g","north",0,1
#define EXIT2 ER_BASE_DIR + "village/waym/1f","east",0,1
#define EXIT3 ER_BASE_DIR + "village/waym/1c","south",0,1

void
create_room()
{
   
   areaname  = "Waymeet";		/*Name of village*/
   land          = "the Shire";		/*Name of land   */
   roomtype  = 4;				/*Type of room in the smial   */
   areatype   = "hamlet";			/*Type of village*/
   smialsize   = "large";			/*Size of the house*/
   
   extraline = "You can see a couple of pantries, one to the "
	+"north and one to the east.";
   add_item("pantries",
	"The hobbits store their food here.\n");
  
   add_exit(EXIT1);
   add_exit(EXIT2);
   add_exit(EXIT3);

   make_the_room();
}





