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
   
   extraline = "This large sitting-room is centered around the fireplace "+
   "against the southeast wall. "+
   "Couches and plush chairs line the walls, making the room seem perfect "+
   "for conversation.  The way back to the entrance-hall is south.";

   add_item(({"fireplace","chimney","grates"}),
   "The fireplace and chimney are set into the southeast wall, "+
   "the chimney going from the fireplace up to a exit point in the roof. "+
   "The fireplace has several openings for the warmth to enter the room "+
   "and, you presume, for it to be tended.\n");

   add_item(({"wall","walls"}),
   "The walls are quite plain apart from the benches and chairs that line "+
   "them.\n");

   add_item(({"couch","couches","chair","chairs","plush chairs"}),
   "The benches and chairs line the walls in a near-circle.\n");
  
   add_exit(GREENHOLM_DIR + "7","south");
}

void
reset_shire_room()
{

   if(random(10) > 3)
   {
     if (!hob)
     {
         hob = clone_object(HOBBITMAKER);
	 hob->set_type(TWEENS);
	 hob->set_power(85);
	 hob->move(TO);
       }
   }
}
