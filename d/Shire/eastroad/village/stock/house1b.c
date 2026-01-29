inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

void reset_room();
void make_hob();

#define EXIT1 GREEN_DIR + "burrow/1c","north",0,1
#define EXIT2 GREEN_DIR + "burrow/1","south",0,1

static object hob, hob2, hob3;

void
create_room()
{
   
   areaname  = "Greenfields"; /*Name of village*/
   land          = "the Shire"; /*Name of land   */
   roomtype  = 3; /*Type of room in the smial   */
   areatype   = "hamlet"; /*Type of village*/
   smialsize   = "tiny"; /*Size of the house*/
   
   extraline = "This very tiny dining room has just enough room for four "+
   "hobbits to eat at a time.  Judging by the mass of hobbits inhabiting "+
   "this burrow, eating must be nearly constant.  North is the kitchen, "+
   "and south is the entryway.  A window is on the western wall.";

   add_item("wall","The wall is dusty and covered in cobwebs.\n");

   add_item(({"cobwebs","cobweb","web"}),"The cobwebs look uninhabited.\n");

   add_item("window","Looking through the window, you can "
      +"see the "+areatype+" of "+areaname+".\n");

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

   	hob = clone_object(ER_DIR +"npc/wehobbit");
   	hob->arm_me();
   	hob->move(TO);

   	hob2 = clone_object(ER_DIR +"npc/ghobbit");
   	hob2->arm_me();
   	hob2->move(TO);

   	hob3 = clone_object(ER_DIR +"npc/femhobbit");
   	hob3->arm_me();
   	hob3->move(TO);

}
