#include "../local.h"

inherit SMIAL;

void
create_smial()
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
     
   add_exit(WAYMET_DIR + "1h","west");
   add_exit(WAYMET_DIR + "1a","east");
   add_exit(WAYMET_DIR + "1e","north");
   add_exit(WAYMET_DIR + "1d","south");
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


