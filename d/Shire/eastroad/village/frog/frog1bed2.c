inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 ER_DIR + "village/frog/frog1w","south",0,1

void reset_room();

static object fhob;

void
create_room()
{
   
   areaname  = "Frogmorton";/*Name of village*/
   land          = "the Shire";/*Name of land   */
   roomtype  = 6;/*Type of room in the smial   */
   areatype   = "village";/*Type of village*/
   smialsize   = "large";/*Size of the house*/
   
   extraline = "Obviously a bedroom for children, this room is a bit "+
   "cluttered with toys and other childrens' articles. The walls "+
   "are decorated with drawings of animals, small and large.";
   
   
   reset_room();
   
   add_exit(EXIT1);
   
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
