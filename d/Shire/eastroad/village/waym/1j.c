inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "../local.h"

#define EXIT1 ER_BASE_DIR + "village/waym/1i","west",0,1

void
create_room()
{
   
   areaname  = "Waymeet";		/*Name of village*/
   land          = "the Shire";		/*Name of land   */
   roomtype  = 7;				/*Type of room in the smial   */
   areatype   = "hamlet";			/*Type of village*/
   smialsize   = "large";			/*Size of the house*/
    
   add_exit(EXIT1);

   extraline = "Set off the master bedroom, this is where the "
	+"owners of this smial keep their clothes.";
   
   add_item("clothes","These clothes are all old and worn, but "
	+"have been lovingly looked after. They don't look worth "
	+"taking.\n");

   add_item(({"shelf","shelves"}),
		"The shelves in this storage room are piled "
		+"up with neatly folded clothes.\n");

   make_the_room();
}




