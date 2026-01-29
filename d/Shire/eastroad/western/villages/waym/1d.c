#include "../local.h"

inherit SMIAL;

void
create_smial()
{
   
   areaname  = "Waymeet";		/*Name of village*/
   land          = "the Shire";		/*Name of land   */
   roomtype  = 3;				/*Type of room in the smial   */
   areatype   = "hamlet";			/*Type of village*/
   smialsize   = "large";			/*Size of the house*/
   
   extraline = "There is a large fireplace in the west wall, and a window "
	+"set into the southern wall lets light into the room during the "
	+"day.";
   
   add_item("fireplace",
      "Not currently lit, you can imagine the cheery warmth that "
      +"would come from this large fireplace.\n");
   add_item("window","Looking through the window, you can "
      +"see the "+areatype+" of "+areaname+".\n");
  
   add_exit(WAYMET_DIR + "1c","north");
}





