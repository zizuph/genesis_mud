#pragma strict_types

#include "../local.h"

inherit SMIAL;

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
   "for sitting or storing the parcels of guests.  Some hooks hang above "+
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
   
    add_exit(GREENHOLM_DIR + "viln1","out");
    add_exit(GREENHOLM_DIR + "1b","north");
    add_exit(GREENHOLM_DIR + "1c","south");   
}

void
reset_shire_room()
{
  setuid(); seteuid(getuid());
  if (!hob)
   {
     hob = clone_object(HOBBITMAKER);
     hob->set_type(TWEENS);
     hob->set_power(50);
     hob->move(TO);
   }
   	
}
