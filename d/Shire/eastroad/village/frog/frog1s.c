inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 ER_DIR + "village/frog/frog1","north",0,1
#define EXIT2 ER_DIR + "village/frog/frog1dine","east",0,1

void reset_room();

static object fhob;

void
create_room()
{
   
   areaname  = "Frogmorton";/*Name of village*/
   land          = "the Shire";/*Name of land   */
   roomtype  = 8;/*Type of room in the smial   */
   areatype   = "village";/*Type of village*/
   smialsize   = "large";/*Size of the house*/
   
   extraline = "This corridor leads to the living area of the "+
   "smial. Sweet aromas of baking bread and boiling herbs "+
   "drift in from the east. The hall itself is very cheerful, "+
   "decorated in light colours and flooded with light from "+
   "overhead lamps.";
   
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
