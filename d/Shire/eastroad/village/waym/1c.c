inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "../local.h"

#define EXIT1 ER_BASE_DIR + "village/waym/1h","west",0,1
#define EXIT2 ER_BASE_DIR + "village/waym/1a","east",0,1
#define EXIT3 ER_BASE_DIR + "village/waym/1e","north",0,1
#define EXIT4 ER_BASE_DIR + "village/waym/1d","south",0,1

void
create_room()
{
   
   areaname  = "Waymeet";		/*Name of village*/
   land          = "the Shire";		/*Name of land   */
   roomtype  = 8;				/*Type of room in the smial   */
   areatype   = "hamlet";			/*Type of village*/
   smialsize   = "small";			/*Size of the house*/
   
   extraline = "This corridor leads further into the smial, with "
	+"rooms leading off from it in all directions. From the "
	+"north, you can smell food odours, that make your "
	+"mouth water.";
   
  
   add_exit(EXIT1);
   add_exit(EXIT2);
   add_exit(EXIT3);
   add_exit(EXIT4);

   make_the_room();
}

void init()	
{
    	::init();
	add_action("do_smell","smell");
}

int do_smell()
{
    NF("Drifting from the kitchen to the north, you can smell "
	+"the delightful odours of freshly baked bread, and "
	+"roasting meats.  It is more than enough to get the "
	+"saliva flowing.\n");
    return 0;
}


