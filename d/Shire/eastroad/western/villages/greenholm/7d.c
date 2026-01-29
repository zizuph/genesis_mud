#include "../local.h"

inherit SMIAL;

void
create_smial()
{
   
   areaname  = "Greenholm";		/*Name of village*/
   land          = "the Shire";		/*Name of land   */
   roomtype  = 3;				/*Type of room in the smial   */
   areatype   = "hamlet";			/*Type of village*/
   smialsize   = "large";			/*Size of the house*/
   
   extraline = "This large dining room is characterized by a very large "+
   "round window, which provides light in the daytime.";

   add_item("window","Looking through the window, you can "
      +"see the "+areatype+" of "+areaname+".\n");
  
   add_exit(GREENHOLM_DIR + "7c","north");
   add_exit(GREENHOLM_DIR + "7e","south");

}
