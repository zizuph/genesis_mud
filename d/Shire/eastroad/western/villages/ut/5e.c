#include "../local.h"

inherit SMIAL;

void
create_smial()
{
   
   areaname  = "Undertowers";		/*Name of village*/
   land          = "Westmarch";		/*Name of land   */
   roomtype  = 5;				/*Type of room in the smial   */
   areatype   = "hamlet";			/*Type of village*/
   smialsize   = "small";			/*Size of the house*/
    
   add_exit(UT_DIR + "5d","northeast");


   extraline = "This bedroom is nearly empty.";
}
