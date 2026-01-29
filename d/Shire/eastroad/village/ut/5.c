inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#include "../local.h"

#define EXIT1 ER_BASE_DIR + "village/ut/5b","south",0,1
#define EXIT2 ER_DIR + "er3n","out",0,1


void reset_room();

static object hob;

void
create_room()
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

   
   add_exit(EXIT1);
   add_exit(EXIT2);

   make_the_room();
   reset_room();
}

void
reset_room()
{
   if (!hob)
   {
   	hob = clone_object(ER_BASE_DIR +"npc/ghobbit");
   	hob->arm_me();
   	hob->move(TO);
   }
}
