inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


#define EXIT1 MICH_DIR + "burrow/4","south",0,1
#define EXIT2 MICH_DIR + "burrow/4g","west",0,1
#define EXIT3 MICH_DIR + "burrow/4f","east",0,1

void reset_room();
void make_hob();

static object hob, hob2, hob3;

void
create_room()
{
   
   areaname  = "Michel Delving"; /*Name of village*/
   land          = "the Shire"; /*Name of land   */
   roomtype  = 2; /*Type of room in the smial   */
   areatype   = "town"; /*Type of village*/
   smialsize   = "large"; /*Size of the house*/
   
   extraline = "This sitting room is the center of hobbit life.  Here "+
   "stories and tales are exchanged, and rumors too, if the truth be "+
   "known.  East and west are bedrooms; the more functional parts of "+
   "the smial are south.";

   add_item("bedrooms","The east bedroom seems to be the master bedroom "+
   "and the west one seems to be more of a guest room.\n");
   
   add_exit(EXIT1);
   add_exit(EXIT2);
   add_exit(EXIT3);
   
   make_the_room();
   reset_room();
}

void
reset_room()
{
   if (!hob)
   {
    set_alarm(1.5,0.0,"make_hob");
   }
   	
}

void
make_hob()
{

   	hob = clone_object(ER_DIR +"npc/wehobbit");
   	hob->arm_me();
   	hob->move(TO);

   	hob2 = clone_object(ER_DIR +"npc/ghobbit");
   	hob2->arm_me();
   	hob2->move(TO);

   	hob3 = clone_object(ER_DIR +"npc/bighobbit");
   	hob3->arm_me();
   	hob3->move(TO);

}
