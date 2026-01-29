inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 GREEN_DIR + "vill1","out",0,1
#define EXIT2 GREEN_DIR + "burrow/1a","west",0,1
#define EXIT3 GREEN_DIR + "burrow/1b","east",0,1

void reset_room();
void make_hob();

static object hob;

void
create_room()
{
   
   areaname  = "Stock"; /*Name of village*/
   land          = "the Shire"; /*Name of land   */
   roomtype  = 1; /*Type of room in the smial   */
   areatype   = "village"; /*Type of village*/
   smialsize   = "small"; /*Size of the house*/
   
   extraline = "This small burrow is spotless like most hobbit homes are, and "+
   "it seems a lot of hobbits live in this small home.  A parlour "+
   "is west and the main parts of the burrow are to the east.";

   add_item(({"space","small space","burrow"}),
   "The entryhall to this burrow is cluttered with clothing and "+
   "all other manner of hobbit possessions.  The cleanliness of everything "+
   "is amazing, and gleams on many of the things in this small space.\n");
      
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
   	hob = clone_object(ER_DIR +"npc/ghobbit");
   	hob->arm_me();
   	hob->move(TO);
}
