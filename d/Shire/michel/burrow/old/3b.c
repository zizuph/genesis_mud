inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


#define EXIT1 MICH_DIR + "burrow/3","south",0,1
#define EXIT2 MICH_DIR + "burrow/3a","west",0,1


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
   
   extraline = "This parlor has small wooden chairs around all the walls "+
   "and a fireplace in the center, which lets the heat distribute evenly "+
   "and provides more light than a fireplace in the wall.";

   add_item(({"chairs","chair","small wooden chairs"}),
   "The small wooden chairs are not in good condition, but they look "+
   "comfortable all the same.\n");

    add_item(({"fireplace","center","fire place","chimney"}),
    "The central position of the fireplace in this room allows all an "+
    "equal chance at being warmed and the light is much brighter than "+
    "if the fireplace were in a corner.  The chimney leading up through "+
    "the roof is somewhat distracting to conversations, however.\n");
   
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
