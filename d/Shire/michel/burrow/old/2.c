inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 MICH_DIR + "gamroad2","out",0,1
#define EXIT2 MICH_DIR + "burrow/2a","north",0,1
#define EXIT3 MICH_DIR + "burrow/2b","south",0,1

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
   
   extraline = "The entryhall of this smial is covered in paintings and "+
   "ornately woven carpets.  Not a spot of bare wall or floor is to be "+
   "found.  North is a room with a large table and south, the sound of "+
   "fire crackling comes to your ears.";

   add_item("paintings","The paintings are of all shapes and sizes, and "+
   "any imaginable subject- from a large painting of a small green frog "+
   "to a tiny portrait of a tall grey wizened man.\n");

   add_item("carpets","The carpets are only viewable as a whole, no "+
   "individual carpets are to be found, as they all overlap and form a "+
   "rainbow of colors and shapes for the eye to behold.\n");   

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
