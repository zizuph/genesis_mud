inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


#define EXIT1 MICH_DIR + "burrow/1c","south",0,1
#define EXIT2 MICH_DIR + "burrow/1g","west",0,1


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
   
   extraline = "This must be the master bedroom- it only has one bed "+
   "and the bed is fairly large by hobbit standards.  A doorway leads "+
   "west to another bedroom and south will put you back in the kitchen.";

   add_item("bed","The bed is about four feet by four feet square, and "+
   "is currently made up.\n");
   
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
   	hob = clone_object(ER_DIR +"npc/ghobbit");
   	hob->arm_me();
   	hob->move(TO);
}
