inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 ER_DIR + "village/frog/frog1","west",0,1

void reset_room();

static object hob;

void
create_room()
{
   
   areaname  = "Frogmorton";/*Name of village*/
   land          = "the Shire";/*Name of land   */
   roomtype  = 2;/*Type of room in the smial   */
   areatype   = "village";/*Type of village*/
   smialsize   = "large";/*Size of the house*/
   
   extraline = "Although a large room, the arrangement of the furniture, gives a feeling of coziness. "+
   "The sofa faces the fireplace, with chairs on either side. "+
   "Over the mantle, hangs a large family painting. The carpet is "+
   "dark green in colour, matching the tan covering "+
   "of the sofa and chairs.";
   
   add_item(({"peg","pegs"}),
      "These pegs are for hats and coats, since the hobbits who "
      +"live here are fond of guests.\n");
   
   reset_room();
   
   add_exit(EXIT1);
   
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
