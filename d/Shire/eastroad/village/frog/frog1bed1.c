inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 ER_DIR + "village/frog/frog1w","east",0,1

void reset_room();

static object hob;
static object fhob;

void
create_room()
{
   
   areaname  = "Frogmorton";/*Name of village*/
   land          = "the Shire";/*Name of land   */
   roomtype  = 5;/*Type of room in the smial   */
   areatype   = "village";/*Type of village*/
   smialsize   = "large";/*Size of the house*/
   
   extraline = "The beautiful decor of this room speaks well of the "+
   "master and mistress of this home. The blue and white spread on "+
   "the bed is a perfect compliment to the light blue drapes on the "+
   "windows and the darker blue, very plush, carpeting. The room "+
   "is very restfull, as a bedroom should be.";
   
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
   if (!fhob)
      {
      fhob = clone_object(ER_DIR +"npc/femhobbit");
      fhob->arm_me();
      fhob->move(TO);
   } 
}
