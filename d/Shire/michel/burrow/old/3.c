inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 MICH_DIR + "gamroad3","out",0,1
#define EXIT2 MICH_DIR + "burrow/3d","south",0,1
#define EXIT3 MICH_DIR + "burrow/3b","north",0,1
#define EXIT4 MICH_DIR + "burrow/3f","southwest",0,1
#define EXIT5 MICH_DIR + "burrow/3c","southeast",0,1

void reset_room();
void make_hob();

static object hob;

void
create_room()
{
   
   areaname  = "Michel Delving"; /*Name of village*/
   land          = "the Shire"; /*Name of land   */
   roomtype  = 1; /*Type of room in the smial   */
   areatype   = "town"; /*Type of village*/
   smialsize   = "large"; /*Size of the house*/
   
   extraline = "This entryhall seems to be the center of activity in this "+
   "smial.  The kitchen is southeast, a pantry south, a bedroom southwest, "+
   "and north seems to be a dining room.";
   
   add_exit(EXIT1);
   add_exit(EXIT2);
   add_exit(EXIT3);
   add_exit(EXIT4);
   add_exit(EXIT5);
   
   make_the_room();
   reset_room();
}

void
reset_room()
{
   if (!hob)
   {
    set_alarm(0.9,0.0,"make_hob");
   }
   	
}

void
make_hob()
{
   	hob = clone_object(ER_DIR +"npc/whobbit");
   	hob->arm_me();
   	hob->move(TO);
}
