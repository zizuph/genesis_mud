#include "../local.h"

inherit SMIAL;

#define EXIT1 ER_BASE_DIR + "village/ut/5","north",0,1
#define EXIT2 ER_BASE_DIR + "village/ut/5c","south",0,1

static object hob;

void
create_smial()
{
   
   areaname  = "Undertowers";		/*Name of village*/
   land          = "Westmarch";		/*Name of land   */
   roomtype  = 4;				/*Type of room in the smial   */
   areatype   = "hamlet";			/*Type of village*/
   smialsize   = "small";			/*Size of the house*/
   
   extraline = "The smell of roasting meat lingers in the air.";

   add_item(({"smell","roasting meat","smell of roasting meat"}),
   "The smell you smelt in the entrance-way you now recognize as "+
   "venison.\n");

   add_exit(UT_DIR + "5","north");
   add_exit(UT_DIR + "5c","south");

   reset_shire_room();
}

void
reset_shire_room()
{
   if(!hob)
   {
    hob = clone_object(HOBBITMAKER);
    hob->set_type(MILITA);
    hob->set_power(100);
    hob->move(TO);
   }

}
