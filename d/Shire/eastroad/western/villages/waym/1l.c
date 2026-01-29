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
   
   extraline = "You are now quite a way into the hill into "
	+"which this smial has been tunnelled. To the west "
	+"and south, the hall opens onto small bedrooms, "
	+"while to the north is another storage room.";
   
   add_item(({"bedroom","bedrooms","storage room"}),
	"Set off the hallway, you would have to enter the "
	+"room to find out what is inside.\n");
  
   add_exit(WAYMET_DIR + "1n","west");
   add_exit(WAYMET_DIR + "1h","east");
   add_exit(WAYMET_DIR + "1m","north");
   add_exit(WAYMET_DIR + "1o","south");

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


