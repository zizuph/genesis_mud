inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#include "../local.h"

#define EXIT1 ER_BASE_DIR + "village/greenholm/5i","north",0,1
#define EXIT2 ER_BASE_DIR + "village/greenholm/5g","west",0,1
#define EXIT3 ER_BASE_DIR + "village/greenholm/5k","south",0,1
#define EXIT4 ER_BASE_DIR + "village/greenholm/5j","east",0,1

void
create_room()
{
   
   areaname  = "Greenholm";		/*Name of village*/
   land          = "the Shire";		/*Name of land   */
   roomtype  = 8;				/*Type of room in the smial   */
   areatype   = "hamlet";			/*Type of village*/
   smialsize   = "large";			/*Size of the house*/
   
   extraline = "This hall branches out four ways- north, south, "+
   "and east toward bedrooms; west back towards the parlour.";
  
   add_exit(EXIT1);
   add_exit(EXIT2);
   add_exit(EXIT3);
   add_exit(EXIT4);

   make_the_room();

}



