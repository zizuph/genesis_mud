#include "../local.h"

inherit SMIAL;

void
create_smial()
{
   
   areaname  = "Waymeet";		/*Name of village*/
   land          = "the Shire";		/*Name of land   */
   roomtype  = 6;				/*Type of room in the smial   */
   areatype   = "hamlet";			/*Type of village*/
   smialsize   = "large";			/*Size of the house*/
    
   add_exit(WAYMET_DIR + "1l","north");


   extraline = "There is a small window set into the south wall, "
	+"providing light during the day.";
   
   add_item("window","This round window looks out over the "
	    +areatype+" of "+areaname+".\n");
}




