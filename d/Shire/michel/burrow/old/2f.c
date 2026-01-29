inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


#define EXIT1 MICH_DIR + "burrow/2g","south",0,1
#define EXIT2 MICH_DIR + "burrow/2b","northeast",0,1


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
   
   extraline = "The master bedroom of this smial is not especially opulent "+
   "or well-furnished.  It has a bed in the center of the room and a chest of "+
   "drawers against the west wall.  A doorway leads south into another bedroom.";

   add_item(({"bed","center"}),
   "The bed in the center of this master bedroom is not especially large nor "+
   "especially comfortable.\n");

   add_item(({"chest","chest of drawers","drawers","west wall","wall"}),
   "The chest of drawers on the west wall is probably the most valuable "+
   "item in the smial, as it seems to be made of exceedingly high quality "+
   "oak.  It is closed and probably locked as well.\n");

   
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
