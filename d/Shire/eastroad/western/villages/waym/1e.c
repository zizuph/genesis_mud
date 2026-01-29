#include "../local.h"

inherit SMIAL;

void
create_smial()
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
  
   add_exit(WAYMET_DIR + "1g","north");
   add_exit(WAYMET_DIR + "1f","east");
   add_exit(WAYMET_DIR + "1c","south");
}





