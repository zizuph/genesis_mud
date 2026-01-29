inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


#define EXIT1 GREEN_DIR + "burrow/1c","south",0,1
#define EXIT2 GREEN_DIR + "burrow/1g","west",0,1


void reset_room();
void make_hob();

static object hob, hob2, hob3;

void
create_room()
{
   
   areaname  = "Greenfields"; /*Name of village*/
   land          = "the Shire"; /*Name of land   */
   roomtype  = 5; /*Type of room in the smial   */
   areatype   = "hamlet"; /*Type of village*/
   smialsize   = "tiny"; /*Size of the house*/
   
   extraline = "There are several blankets and pillows spread out on the floor.  "+
   "West is another bedroom.";

   add_item(({"blanket","blankets","pillow","pillows"}),
   "There are seven blankets and nine pillows on the floor here, and it "+
   "is very untidy.\n");
   
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

   	hob2 = clone_object(ER_DIR +"npc/whobbit");
   	hob2->arm_me();
   	hob2->move(TO);


   	hob3 = clone_object(ER_DIR +"npc/wehobbit");
   	hob3->arm_me();
   	hob3->move(TO);

}
