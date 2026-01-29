inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


#include "../local.h"

#define EXIT1 ER_BASE_DIR + "village/ut/5","north",0,1
#define EXIT2 ER_BASE_DIR + "village/ut/5c","south",0,1

static object hob;
void reset_room();


void
create_room()
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


   add_exit(EXIT1);
   add_exit(EXIT2);


   make_the_room();
   reset_room();

}

void
reset_room()
{
   if(!hob)
   {
    hob = clone_object(ER_BASE_DIR + "npc/femhobbit");
    hob->arm_me();
    hob->move(TO);
   }

}
