inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "../local.h"

#define EXIT1 ER_BASE_DIR + "village/waym/1h","south",0,1

void
create_room()
{
   
   areaname  = "Waymeet";		/*Name of village*/
   land          = "the Shire";		/*Name of land   */
   roomtype  = 7;				/*Type of room in the smial   */
   areatype   = "hamlet";			/*Type of village*/
   smialsize   = "large";			/*Size of the house*/
    
   add_exit(EXIT1);

   make_the_room();
}




