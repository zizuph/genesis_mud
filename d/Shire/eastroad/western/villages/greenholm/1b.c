#include "../local.h"

inherit SMIAL;

static object hob;

void
create_smial()
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
  

   add_exit(GREENHOLM_DIR + "1","south");
   reset_shire_room();
}

void
reset_shire_room()
{
   setuid(); seteuid(getuid());
   if(random(10) > 5)
   {
     if (!hob)
     {
       hob = clone_object(HOBBITMAKER);
       hob->set_type(CITIZEN);
       hob->set_power(130);
       hob->move(TO);
     }
   }
}
