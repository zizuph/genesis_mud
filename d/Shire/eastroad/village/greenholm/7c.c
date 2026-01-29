inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


#include "../local.h"

#define EXIT1 ER_BASE_DIR + "village/greenholm/7","north",0,1
#define EXIT3 ER_BASE_DIR + "village/greenholm/7d","south",0,1
#define EXIT2 ER_BASE_DIR + "village/greenholm/7f","east",0,1

static object hob;
void reset_room();

void
create_room()
{
   
   areaname  = "Greenholm";		/*Name of village*/
   land          = "the Shire";		/*Name of land   */
   roomtype  = 4;				/*Type of room in the smial   */
   areatype   = "hamlet";			/*Type of village*/
   smialsize   = "large";			/*Size of the house*/
   
   extraline = "Something seems to be cooking on the stove, "+
   "and a pantry is east.";

   add_item("something","The something is inside a pot, but it "+
   "sure smells good!\n");
   add_item("pot","It is cooking something on the stove.\n");
   add_item("pantry","The pantry is where the hobbits who "+
   "live here keep their food.\n");
  
   add_exit(EXIT1);
   add_exit(EXIT2);
   add_exit(EXIT3);

   make_the_room();
   reset_room();
}

void
reset_room()
{
   if(random(10) > 1)
   {
     if(!hob)
     {
       hob = clone_object(ER_BASE_DIR + "npc/femhobbit");
       hob->arm_me();
       hob->move(TO);
     }
   }
}
