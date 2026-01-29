inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#include "../local.h"
#define EXIT1 ER_BASE_DIR + "village/greenholm/5","west",0,1
#define EXIT2 ER_BASE_DIR + "village/greenholm/5c","northeast",0,1
#define EXIT3 ER_BASE_DIR + "village/greenholm/5g","southeast",0,1

void reset_room();
void add_stuff();
static object hob, hob2, hob3;

void
create_room()
{
   
   areaname  = "Greenholm";		/*Name of village*/
   land          = "the Shire";		/*Name of land   */
   roomtype  = 2;				/*Type of room in the smial   */
   areatype   = "hamlet";			/*Type of village*/
   smialsize   = "large";			/*Size of the house*/
   
   extraline = "This parlour-room is set up rectangularly, with the "+
   "fireplace on the northern wall, between two arm-chairs of small "+
   "proportions, while the southern wall has several long, padded "+
   "benches.  West leads to the entrance hall, northeast and southeast "+
   "both lead farther into the smial.";


   add_exit(EXIT1);
   add_exit(EXIT2);
   add_exit(EXIT3);

   make_the_room();
   reset_room();
}

void
reset_room()
{
   set_alarm(1.5,0.0,"add_stuff");
}


void
add_stuff()
{
   if (!hob)
  {
     hob = clone_object(ER_BASE_DIR +"npc/whobbit");
   	hob->arm_me();
   	hob->move(TO);
   }
   if(!hob2)
   {
     hob2 = clone_object(ER_BASE_DIR + "npc/ghobbit");
     hob2->arm_me();
     hob2->move(TO);
   }

   if(!hob3)
   {
     hob3 = clone_object(ER_BASE_DIR + "npc/bighobbit");
     hob3->arm_me();
     hob3->move(TO);
   }

}
