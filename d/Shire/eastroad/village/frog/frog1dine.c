inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 ER_DIR + "village/frog/frog1s","west",0,1
#define EXIT2 ER_DIR + "village/frog/frog1kit","east",0,1

void reset_room();

static object fhob;

void
create_room()
{
   
   areaname  = "Frogmorton";/*Name of village*/
   land          = "the Shire";/*Name of land   */
   roomtype  = 3;/*Type of room in the smial   */
   areatype   = "village";/*Type of village*/
   smialsize   = "large";/*Size of the house*/
   
extraline = "Sweet cooking aromas waft in from the kitchen "+
"causing the mouth of anyone in this room to salivate in "+
"anticipation of a wonderful meal.";
   
   add_item(({"lamp","lamps","overhead lamps"}),"These oil lamps "+
      "are hanging down from the ceiling and cast off a great deal "+
      "of light.\n");
   
   reset_room();
   
   add_exit(EXIT1);
   add_exit(EXIT2);
   
   make_the_room();
}

void
reset_room()
{
/*
   if (!hob)
      {
      hob = clone_object(ER_DIR +"npc/ghobbit");
      hob->arm_me();
      hob->move(TO);
   }
*/
   if (!fhob)
      {
      fhob = clone_object(ER_DIR +"npc/femhobbit");
      fhob->arm_me();
      fhob->move(TO);
   } 
}
