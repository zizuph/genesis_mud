inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


#include "../local.h"

#define EXIT1 ER_BASE_DIR + "village/ut/5d","northeast",0,1



void
create_room()
{
   
   areaname  = "Undertowers";		/*Name of village*/
   land          = "Westmarch";		/*Name of land   */
   roomtype  = 5;				/*Type of room in the smial   */
   areatype   = "hamlet";			/*Type of village*/
   smialsize   = "small";			/*Size of the house*/
    
   add_exit(EXIT1);


   extraline = "This bedroom is nearly empty.";

   make_the_room();
}
