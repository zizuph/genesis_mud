inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 MICH_DIR + "gamroad5","out",0,1
#define EXIT2 MICH_DIR + "burrow/5a","southeast",0,1
#define EXIT3 MICH_DIR + "burrow/5f","southwest",0,1

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
   
   extraline = "This entryhall is long and low, some of the taller hobbits "+
   "would have to duck to enter.  Pegs line the walls and there are two benches "+
   "on either side of the hallway.  Southwest leads to the sleeping areas "+
   "of the smial and southeast leads to the more public parts of the burrow.";

   add_item(({"pegs","walls","peg","wall"}),
   "The wooden pegs seem to hold well in the white chalky walls here in "+
   "the White Downs.\n");

   add_item(({"bench","benches","hall","hallway"}),
   "The benches are low to the ground and made of maple- they line up "+
   "along the hallway.\n"); 

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
