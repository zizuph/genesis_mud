inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


#define EXIT1 MICH_DIR + "burrow/5","northeast",0,1
#define EXIT2 MICH_DIR + "burrow/5g","south",0,1


void reset_room();
void make_hob();

static object hob;

void
create_room()
{
   
   areaname  = "Michel Delving"; /*Name of village*/
   land          = "the Shire"; /*Name of land   */
   roomtype  = 5; /*Type of room in the smial   */
   areatype   = "town"; /*Type of village*/
   smialsize   = "large"; /*Size of the house*/
   
   extraline = "This bedroom is quite messy, with clothes and "+
   "sheets and odds and ends cluttering the floor.";

   add_item(({"clothes","sheets","sheet","odds","ends","floor"}),
   "The floor is covered in the possessions of the messy occupants of "+
   "this smial.\n");

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
   	hob = clone_object(ER_DIR +"npc/bighobbit");
   	hob->arm_me();
   	hob->move(TO);
}
