inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#include "../local.h"
#define EXIT1 ER_BASE_DIR + "village/greenholm/1c","north",0,1
#define EXIT2 ER_BASE_DIR + "village/greenholm/1e","south",0,1

void
create_room()
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
  
   add_exit(EXIT1);
   add_exit(EXIT2);

   make_the_room();
}
