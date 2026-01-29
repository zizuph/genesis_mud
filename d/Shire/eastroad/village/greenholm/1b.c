inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#include "../local.h"

#define EXIT1 ER_BASE_DIR + "village/greenholm/1","south",0,1

void reset_room();

static object hob;

void
create_room()
{
   
   areaname  = "Greenholm";		/*Name of village*/
   land          = "Shire";		/*Name of land   */
   roomtype  = 2;				/*Type of room in the smial   */
   areatype   = "hamlet";			/*Type of village*/
   smialsize   = "large";			/*Size of the house*/
   
   extraline = "This fine sitting-room is centered around the fireplace "+
   "which is situated in the middle of the room, quite oddly enough. "+
   "Benches and low chairs line the walls, making the room seem perfect "+
   "for conversation.  The way back to the entrance-hall is south.";

   add_item(({"fireplace","chimney","grates"}),
   "The fireplace and chimney are set into the center of the room "+
   "the chimney going from the fireplace up to a exit point in the roof. "+
   "The fireplace has several openings for the warmth to enter the room "+
   "and, you presume, for it to be tended.\n");

   add_item(({"wall","walls"}),
   "The walls are quite plain apart from the benches and chairs that line "+
   "them.\n");

   add_item(({"bench","benches","chair","chairs"}),
   "The benches and chairs line the walls in a near-circle.\n");
  
   add_exit(EXIT1);

   make_the_room();
   reset_room();
}

void
reset_room()
{

   if(random(10) > 5)
   {
     if (!hob)
     {
       hob = clone_object(ER_BASE_DIR +"npc/ghobbit");
   	  hob->arm_me();
   	  hob->move(TO);
     }
   }
}
