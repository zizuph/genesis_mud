inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


#define EXIT1 MICH_DIR + "burrow/4","north",0,1
#define EXIT2 MICH_DIR + "burrow/4b","west",0,1
#define EXIT3 MICH_DIR + "burrow/4d","south",0,1


void reset_room();
void make_hob();

static object hob;

void
create_room()
{
   
   areaname  = "Michel Delving"; /*Name of village*/
   land          = "the Shire"; /*Name of land   */
   roomtype  = 4; /*Type of room in the smial   */
   areatype   = "town"; /*Type of village*/
   smialsize   = "large"; /*Size of the house*/
   
   extraline = "This kitchen seems to be in disuse, like "+
   "the dining room.";  
   
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
   	hob = clone_object(ER_DIR +"npc/femhobbit");
   	hob->arm_me();
   	hob->move(TO);
}
