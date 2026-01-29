inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


#define EXIT1 MICH_DIR + "burrow/1f","east",0,1

void reset_room();
void make_hob();

static object hob;

void
create_room()
{
   
   areaname  = "Michel Delving"; /*Name of village*/
   land          = "the Shire"; /*Name of land   */
   roomtype  = 6; /*Type of room in the smial   */
   areatype   = "town"; /*Type of village*/
   smialsize   = "large"; /*Size of the house*/
   
   extraline = "This bedroom has five separate beds in it, it must be "+
   "for the children of the family or overnight guests.  The beds are "+
   "tidily ordered in a row.  East is the master bedroom.";

   add_item(({"beds","bed","five beds","row"}),
  "The row of beds is very neatly organized against the north "+
   "wall, and the beds are made up and at the moment, empty.\n");
   
   add_exit(EXIT1);
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
