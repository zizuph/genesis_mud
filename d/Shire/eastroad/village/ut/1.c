inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#include "../local.h"

#define EXIT1 ER_BASE_DIR + "village/ut/1c","south",0,1
#define EXIT2 ER_BASE_DIR + "village/ut/1b","north",0,1
#define EXIT3 ER_DIR + "er3s","out",0,1

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
   
   extraline = "The large round door stands open to the outdoors, "+
                     "north, a corridor leads to a parlour, and south, you "+
                     "smell the odor of herbs and things baking.";

   add_item(({"odor","smell","herbs","baking","things baking"}),
   "It smells like a most excellent cook lives in this burrow.\n");
   
   
   add_exit(EXIT1);
   add_exit(EXIT2);
   add_exit(EXIT3);
   
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
