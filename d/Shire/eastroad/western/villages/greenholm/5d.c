inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


#include "../local.h"

#define EXIT1 ER_BASE_DIR + "village/greenholm/5c","northwest",0,1
#define EXIT2 ER_BASE_DIR + "village/greenholm/5e","east",0,1
#define EXIT3 ER_BASE_DIR + "village/greenholm/5f","south",0,1

static object hob;

void reset_room();

void
create_room()
{
   
   areaname  = "Greenholm";		/*Name of village*/
   land          = "the Shire";		/*Name of land   */
   roomtype  = 4;				/*Type of room in the smial   */
   areatype   = "hamlet";			/*Type of village*/
   smialsize   = "large";			/*Size of the house*/
   
   extraline = "This is a rather large and expansive kitchen, with "+
   "many shelves for pots, pans and utensils.  The cupboards seem "+
   "overflowing with cups, saucers, plates and bowls.  Pantries are "+
   "east and south, northwest leads back to the dining room.";

   add_item(({"pots","pans","utensils","shelves","pot","pan"}),
   "The shelves barely hold all the pots, pans, and utensils.\n");

   add_item(({"cupboards","cups","saucers","plates","bowls","cup"}),
   "The cupboards do not quite close completely because of the "+
   "bowls, saucers, plates and cups sticking out from them.\n");
  
   add_exit(EXIT1);
   add_exit(EXIT2);
   add_exit(EXIT3);

   make_the_room();
   reset_room();
}

void
reset_room()
{
   if(random(3) > 0)
   {
     if(!hob)
     {
       hob = clone_object(ER_BASE_DIR + "npc/femhobbit");
       hob->arm_me();
       hob->move(TO);
     }
   }
}
