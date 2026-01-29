#include "../local.h"

inherit SMIAL;

#define EXIT1 ER_BASE_DIR + "village/greenholm/viln2","out",0,1
#define EXIT2 ER_BASE_DIR + "village/greenholm/7c","south",0,1
#define EXIT3 ER_BASE_DIR + "village/greenholm/7b","north",0,1

static object hob;

void
create_smial()
{
   
   areaname  = "Greenholm"; /*Name of village*/
   land          = "the Shire"; /*Name of land   */
   roomtype  = 1; /*Type of room in the smial   */
   areatype   = "hamlet"; /*Type of village*/
   smialsize   = "large"; /*Size of the house*/
   
   extraline = "This foyer has a small bench placed along the east wall "+
   "for quiet relaxation or putting on one's coat.  Some hooks hang above "+
   "the bench and above the open round door.  A wonderful smell comes from "+
   "the south and the distinct crackling of a fire echoes from the north.";

   add_item(({"foyer"}), "It is the entrance hall for this smial.\n");
   add_item(({"bench","east wall","parcels","hooks"}),
   "The bench is made of well-crafted oak, and currently holds nothing on it. "+
   "The east wall has hooks sticking out from it, probably more for "+
   "the coats and cloaks of guests than for picture-hanging.\n");
   add_item(({"open round door","round door","door"}),
   "Distinctively round in the hobbit fashion, the door is made of sturdy "+
   "oak, with a fine brass handle set in the center of the door.  It is useless "+
   "however, as the door is propped open with a medium-sized stone.\n");
   
   add_exit(GREENHOLM_DIR + "viln2","out");
   add_exit(GREENHOLM_DIR + "7c","south");
   add_exit(GREENHOLM_DIR + "7b","north");   
   reset_shire_room();
}

void
reset_shire_room()
{
   if (!hob)
   {
   	hob = clone_object(HOBBITMAKER);
   	hob->set_type(CHILD);
	hob->set_power(30);
   	hob->move(TO);
   }
}
