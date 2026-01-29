#include "../local.h"

inherit SMIAL;

static object hob, fhob;

void
create_smial()
{
   
   areaname  = "Waymeet";/*Name of village*/
   land          = "the Shire";/*Name of land   */
   roomtype  = 1;/*Type of room in the smial   */
   areatype   = "hamlet";/*Type of village*/
   smialsize   = "large";/*Size of the house*/
   
   extraline = "There is an exit into the parlor to the east, and "
   	+"a corridor leading west further into the smial.  On the west "
   	+"wall, near the front door, are a number of pegs.";
   
   add_item(({"peg","pegs"}),
      "These pegs are for hats and coats, since the hobbits who "
      +"live here are fond of guests.\n");

   add_exit(EAST_R_DIR + "er12","out");
   add_exit(WAYMET_DIR + "1b","east");
   add_exit(WAYMET_DIR + "1c","west");
   reset_shire_room();
}

void
reset_shire_room()
{
   if (!hob)
   {
   	hob = clone_object(HOBBITMAKER);
   	hob->set_type(MILITA);
	hob->set_power(160);
   	hob->move(TO);
   }
   if (!fhob)
   {
   	fhob = clone_object(HOBBITMAKER);
	fhob->set_type(MAIDEN);
   	fhob->set_power(100);
   	fhob->move(TO);
   } 
}
