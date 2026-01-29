inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 ER_DIR + "village/frog/frog1w","north",0,1

void reset_room();

static object hob;

void
create_room()
{
   
   areaname  = "Frogmorton";/*Name of village*/
   land          = "the Shire";/*Name of land   */
   roomtype  = 6;/*Type of room in the smial   */
   areatype   = "village";/*Type of village*/
   smialsize   = "large";/*Size of the house*/
   
   extraline = "This bedroom serves as a guest bedroom and is "+
   "also where the Master of the house sleeps after one of his "+
   "long, all night, parties, which his wife disapproves of. "+
   "The simple, albeit, comfortable furnishings, are kept in "+
   "excellent condition in anticipation of unexpected guests.";
   
   
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
