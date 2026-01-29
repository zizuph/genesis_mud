inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#include "../local.h"

#define EXIT1 ER_DIR + "er6n","out",0,1
#define EXIT2 ER_BASE_DIR + "village/greenholm/5b","east",0,1

void reset_room();

static object hob;

void
create_room()
{
   
   areaname  = "Greenholm"; /*Name of village*/
   land          = "the Shire"; /*Name of land   */
   roomtype  = 1; /*Type of room in the smial   */
   areatype   = "hamlet"; /*Type of village*/
   smialsize   = "large"; /*Size of the house*/
   
   extraline = "This entry-hall is round in the hobbit fashion, but "+
   "somewhat barren.  On the walls are the usual hooks for "+
   "hanging coats, hats, and cloaks.  A corridor leads east, further "+
   "into the smial, and the door leads out.";

   add_item("hooks","They are used for hanging clothing on.\n");
   add_item(({"corridor","smial"}),"The corridor leads east into "+
   "the main parts of the smial.\n");
   add_item("door","The door is big and round with its handle in the "+
   "very middle of the door.\n"); 
   
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
   	hob = clone_object(ER_BASE_DIR +"npc/wehobbit");
   	hob->arm_me();
   	hob->move(TO);
   }
   	
}
