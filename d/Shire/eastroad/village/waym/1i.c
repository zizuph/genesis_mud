inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "../local.h"

#define EXIT1 ER_BASE_DIR + "village/waym/1j","east",0,1
#define EXIT2 ER_BASE_DIR + "village/waym/1h","north",0,1

void
create_room()
{
   
   areaname  = "Waymeet";		/*Name of village*/
   land          = "the Shire";		/*Name of land   */
   roomtype  = 5;				/*Type of room in the smial   */
   areatype   = "hamlet";			/*Type of village*/
   smialsize   = "large";			/*Size of the house*/
    
   add_exit(EXIT1);
add_exit(EXIT2);

   extraline = "Through to the east, there is a walk-in wardrobe, "
	+"and there is a large, airy window set in the south wall, "
	+"providing a view out over the "+areatype+". The walls "
	+"of this bedroom are decorated with pictures, and there "
	+"is a nice, thick carpet on the floor. ";
   
   add_item(({"window","view"}),
	"Looking out the window, you can see the peaceful "
	+areatype+" of "+areaname+".\n");

   add_item(({"picture","pictures"}),
		"Adding character to this room, the pictures are "
		+"paintings of rural and rustic scenes, that make "
		+"the room look bigger than it really is.\n");

   add_item("carpet","This thick carpet feels nice underfoot. "
		+"It is a deep green colour, and would feel almost "
		+"like lush grass to the bare foot.\n");

   make_the_room();
}


