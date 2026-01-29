inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#include "../local.h"

#define EXIT1 ER_BASE_DIR + "village/greenholm/viln1","out",0,1
#define EXIT2 ER_BASE_DIR + "village/greenholm/1c","south",0,1
#define EXIT3 ER_BASE_DIR + "village/greenholm/1b","north",0,1

void reset_room();
void make_hob();

static object hob;

void
create_room()
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
   
   
   add_exit(EXIT1);
   add_exit(EXIT2);
   add_exit(EXIT3);
   
   make_the_room();
   reset_room();
}

void
reset_room()
{
   if (!hob)
   {
    set_alarm(1.5,0.0,"make_hob");
   }
   	
}

void
make_hob()
{
   	hob = clone_object(ER_BASE_DIR +"npc/wehobbit");
   	hob->arm_me();
   	hob->move(TO);
}
