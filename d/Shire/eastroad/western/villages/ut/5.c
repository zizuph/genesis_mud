#include "../local.h"

inherit SMIAL;

static object hob;

void
create_smial()
{
   
   areaname  = "Undertowers"; /*Name of village*/
   land          = "Westmarch"; /*Name of land   */
   roomtype  = 1; /*Type of room in the smial   */
   areatype   = "hamlet"; /*Type of village*/
   smialsize   = "small"; /*Size of the house*/
   
   extraline = "The smell of something cooking comes from the "+
   "south, that must be the kitchen.  On the walls are "+
   "some pegs and shelves to deposit burdens.";

   add_item(({"smell","cooking","smell of something cooking"}),
   "It smells like meat roasting in an oven.\n");

   add_item(({"peg","pegs","shelf","shelves","burdens"}),
   "The many pegs and shelves attached to this entry-way wall "+
   "are filled from time to time with coats, cloaks, hats and "+
   "sometimes even mathoms, gifts that one gives on a birthday.\n");

   add_exit(UT_DIR + "5b","south");
   add_exit(EAST_R_DIR + "er3n","out");

}

void
reset_room()
{
   if (!hob)
   {
   	hob = clone_object(HOBBITMAKER);
   	hob->set_type(MAIDEN);
	hob->set_power(90);
   	hob->move(TO);
   }
}
