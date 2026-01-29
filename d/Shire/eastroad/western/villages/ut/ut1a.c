#include "../local.h"

inherit SMIAL;

#define EXIT1 ER_BASE_DIR + "village/ut/1c","south",0,1
#define EXIT2 ER_BASE_DIR + "village/ut/1b","north",0,1
#define EXIT3 ER_DIR + "er3s","out",0,1

static object hob;

void
create_smial()
{
   
   areaname  = "Undertowers"; /*Name of village*/
   land          = "Westmarch"; /*Name of land   */
   roomtype  = 1; /*Type of room in the smial   */
   areatype   = "hamlet"; /*Type of village*/
   smialsize   = "small"; /*Size of the house*/
   
   extraline = "The large round door stands open to the outdoors, "+
                     "north, a corridor leads to a parlour, and south, you "+
                     "smell the odor of herbs and things baking.";

   add_item(({"odor","smell","herbs","baking","things baking"}),
   "It smells like a most excellent cook lives in this burrow.\n");
   
   add_exit(UT_DIR + "ut1b","north");
   add_exit(UT_DIR + "ut1c","south");
   add_exit(EAST_R_DIR + "er3s","out");
  
   reset_shire_room();
}

void
reset_shire_room()
{
   if (!hob)
   {
   	hob = clone_object(HOBBITMAKER);
   	hob->set_type(ELDER);
	hob->set_power(140);
   	hob->move(TO);
   }
}
