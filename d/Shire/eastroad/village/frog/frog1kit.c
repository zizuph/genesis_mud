inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 ER_DIR + "village/frog/frog1dine","west",0,1
#define EXIT2 ER_DIR + "village/frog/frog1pant1","east",0,1

void reset_room();

static object fhob;

void
create_room()
{
   
   areaname  = "Frogmorton";/*Name of village*/
   land          = "the Shire";/*Name of land   */
   roomtype  = 4;/*Type of room in the smial   */
   areatype   = "village";/*Type of village*/
   smialsize   = "large";/*Size of the house*/
   
   extraline = "Although there is so much cooking being done "+
   "the kitchen is meticulously clean. There seems "+
   "to be enough food being prepared for half the residents "+
   "of Shire. Of course Hobbits are known for their huge appetites.";
   
   add_item("food","Meats, vegatables, cakes and pies abound. Enough food "+
      "for at least six meals, a hobbits daily intake.\n");
   
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
