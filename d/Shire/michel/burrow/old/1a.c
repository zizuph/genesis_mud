inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


#define EXIT1 MICH_DIR + "burrow/1","north",0,1

void reset_room();
void make_hob();

static object hob, hob2, hob3;

void
create_room()
{
   
   areaname  = "Michel Delving"; /*Name of village*/
   land          = "the Shire"; /*Name of land   */
   roomtype  = 2; /*Type of room in the smial   */
   areatype   = "town"; /*Type of village*/
   smialsize   = "large"; /*Size of the house*/
   
   extraline = "The parlor room is much more comfortable than the "+
   "spartan entryway.  Here are four cherry rocking chairs and a "+
   "few large pillows are scattered about on the floor.  The hobbits "+
   "who live here must certainly enjoy visitors.  A fireplace occupies "+
   "the southern wall.  The main parts of the house are north.";

   add_item(({"four chairs","cherry rocking chairs","cherry rocking chair","chair"}),
   "The four cherry rocking chairs are handmade, you suppose, judging by the "+
   "glue left on the outside of the wooden joints.  Still, they must be quite "+
   "comfortable when the afternoon grows long and dinner begins cooking.\n");

   add_item(({"fireplace","fire","fire place","southern wall","wall"}),
   "The black iron fireplace cut into the southern wall is a striking "+
   "contrast to the white chalk wall it is adjoined to.  A subdued fire "+
   "is kept burning by the hobbits who live here.\n");

   
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

   	hob = clone_object(ER_DIR +"npc/wehobbit");
   	hob->arm_me();
   	hob->move(TO);

   	hob2 = clone_object(ER_DIR +"npc/ghobbit");
   	hob2->arm_me();
   	hob2->move(TO);

   	hob3 = clone_object(ER_DIR +"npc/bighobbit");
   	hob3->arm_me();
   	hob3->move(TO);

}
