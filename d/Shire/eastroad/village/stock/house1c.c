inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


#define EXIT1 GREEN_DIR + "burrow/1b","south",0,1
#define EXIT2 GREEN_DIR + "burrow/1f","north",0,1



void reset_room();
void make_hob();

static object hob, hob2;

void
create_room()
{
   
   areaname  = "Greenfields"; /*Name of village*/
   land          = "the Shire"; /*Name of land   */
   roomtype  = 4; /*Type of room in the smial   */
   areatype   = "hamlet"; /*Type of village*/
   smialsize   = "tiny"; /*Size of the house*/
   
   extraline = "The kitchen is constantly in a state of upheaval.  A pile of "+
   "dishes waits to be washed while a turkey roasts in the oven.";

   add_item(({"dishes","pile","dish"}),
   "The pile of dishes is dirty with catsup and mustard and in some places, "+
   "dust.\n");
   
   add_item(({"turkey","oven"}),
   "The smell of a well-cooked turkey comes from the oven.\n");

   add_exit(EXIT1);
   add_exit(EXIT2);
   
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
   	hob = clone_object(ER_DIR +"npc/femhobbit");
   	hob->arm_me();
   	hob->move(TO);

    hob2 = clone_object(ER_DIR + "npc/femhobbit");
    hob2->arm_me();
    hob2->move(TO);
}
