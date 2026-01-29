#include "../local.h"

inherit SMIAL;

void
create_smial()
{
   
   areaname  = "Waymeet";		/*Name of village*/
   land          = "the Shire";		/*Name of land   */
   roomtype  = 10;				/*Type of room in the smial   */
   areatype   = "hamlet";			/*Type of village*/
   smialsize   = "large";			/*Size of the house*/
    
   add_exit(WAYMET_DIR + "1e","south");

}




