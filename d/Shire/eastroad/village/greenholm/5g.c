inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#include "../local.h"

#define EXIT1 ER_BASE_DIR + "village/greenholm/5b","northwest",0,1
#define EXIT2 ER_BASE_DIR + "village/greenholm/5h","east",0,1

void
create_room()
{
   
   areaname  = "Greenholm";		/*Name of village*/
   land          = "the Shire";		/*Name of land   */
   roomtype  = 8;				/*Type of room in the smial   */
   areatype   = "hamlet";			/*Type of village*/
   smialsize   = "large";			/*Size of the house*/
   
   extraline = "This narrow corridor leads east to the sleeping "+
   "quarters of the smial and northwest towards the parlour.";
  
   add_exit(EXIT1);
   add_exit(EXIT2);

   make_the_room();
}



