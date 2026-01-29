inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 MICH_DIR + "gamroad4","out",0,1
#define EXIT2 MICH_DIR + "burrow/4a","north",0,1
#define EXIT3 MICH_DIR + "burrow/4c","south",0,1

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
   
   extraline = "This very small entryhall seems as if it was planned for "+
   "a closet, but later the builders decided to make it the main entrance. "+
   "This cramped room has a bench and a few hooks above it for coats "+
   "and hats and the like.";

   add_item(({"bench","hooks","hook","coat","hat"}),
   "The pine bench is varnished in a heavy black stain, and the hooks "+
   "above it are fashioned from wrought iron.  No hats or coats are "+
   "on the bench or hooks at the moment.\n");

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
   	hob = clone_object(ER_DIR +"npc/whobbit");
   	hob->arm_me();
   	hob->move(TO);
}
