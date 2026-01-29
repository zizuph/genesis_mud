inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 ER_DIR + "village/frog/frog1e","east",0,1
#define EXIT2 ER_DIR + "village/frog/frog1w","west",0,1
#define EXIT4 ER_DIR + "village/frog/frog1s","south",0,1
#define EXIT3 ER_DIR + "er12","out",0,1

void reset_room();

static object hob;

void
create_room()
{
   
   areaname  = "Frogmorton";/*Name of village*/
   land          = "the Shire";/*Name of land   */
   roomtype  = 1;/*Type of room in the smial   */
   areatype   = "village";/*Type of village*/
   smialsize   = "large";/*Size of the house*/
   
   extraline = "There is an exit into the parlor to the east, and "
   +"a corridor leading west further into the smial.  On the west "
   +"wall, near the front door, are a number of pegs.";
   
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
