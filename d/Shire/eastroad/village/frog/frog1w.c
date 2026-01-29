inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 ER_DIR + "village/frog/frog1","east",0,1
#define EXIT2 ER_DIR + "village/frog/frog1bed1","west",0,1
#define EXIT3 ER_DIR + "village/frog/frog1bed2","north",0,1
#define EXIT4 ER_DIR + "village/frog/frog1bed3","south",0,1

void reset_room();

static object hob;

void
create_room()
{
   
   areaname  = "Frogmorton";/*Name of village*/
   land          = "the Shire";/*Name of land   */
   roomtype  = 8;/*Type of room in the smial   */
   areatype   = "village";/*Type of village*/
   smialsize   = "large";/*Size of the house*/
   
   extraline = "This corridor is a part of the sleeping area for the "+
   "residents here. There are many paintings on the walls "+
   "lining the hall and entrances to three bedrooms. The corridor "+
   "is well lit and colourfully directed in a blue decore.";
   
   add_item(({"peg","pegs"}),
      "These pegs are for hats and coats, since the hobbits who "
      +"live here are fond of guests.\n");
   
   reset_room();
   
   add_exit(EXIT1);
   add_exit(EXIT2);
   add_exit(EXIT3);
   add_exit(EXIT4);
   
   make_the_room();
}

void
reset_room()
{
   if (!hob)
      {
      hob = clone_object(ER_DIR +"npc/ghobbit");
      hob->arm_me();
      hob->move(TO);
   }
   /*
   if (!fhob)
      {
      fhob = clone_object(ER_DIR +"npc/femhobbit");
      fhob->arm_me();
      fhob->move(TO);
   } 
   */
}
