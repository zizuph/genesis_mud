inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


#define EXIT1 MICH_DIR + "burrow/5","northwest",0,1
#define EXIT2 MICH_DIR + "burrow/5b","southeast",0,1

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
   
   extraline = "This sitting room is arranged in a circular conversational "+
   "grouping; chairs, pillows, and couches included.  A fire burns merrily "+
   "away in the fireplace on the eastern wall.  Southeast is a room for meals "+
   "and northwest is the entryway.";
   
   add_item(({"chair","chairs"}),
   "The chairs are comfortably crafted of walnut.\n");

   add_item(({"pillows","pillow","couches","couch"}),
   "The sitting areas are rather colorful- red, yellow, green and pale blue "+
   "predominate.\n");

   add_item(({"fire","fireplace","eastern wall","wall"}),
   "The fireplace is discolored black from all the ash and smoke.  It has "+
   "seen a fair bit of use.\n");

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

   	hob = clone_object(ER_DIR +"npc/whobbit");
   	hob->arm_me();
   	hob->move(TO);

   	hob2 = clone_object(ER_DIR +"npc/ghobbit");
   	hob2->arm_me();
   	hob2->move(TO);

   	hob3 = clone_object(ER_DIR +"npc/bighobbit");
   	hob3->arm_me();
   	hob3->move(TO);

}
