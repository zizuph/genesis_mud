inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#include "../local.h"

#define EXIT1 ER_BASE_DIR + "village/greenholm/5h","west",0,1

void reset_room();
static object hob;

void
create_room()
{
   
   areaname  = "Greenholm";		/*Name of village*/
   land          = "the Shire";		/*Name of land   */
   roomtype  = 5;				/*Type of room in the smial   */
   areatype   = "hamlet";			/*Type of village*/
   smialsize   = "large";			/*Size of the house*/
    

   extraline = "This large bedroom is opulent even when compared "+
   "to the others.  The extremely large bed leaves no doubts- the master "+
   "of this smial lives here.";

   add_item("extremely large bed","It takes up nearly half the room, and "+
   "is covered in very fine sheets and pillows.\n");

   add_exit(EXIT1);

   make_the_room();
   reset_room();
}

void
reset_room()
{
   if(random(3) > 0)
   {
    if(!hob)
    {
     hob = clone_object(ER_BASE_DIR + "npc/bighobbit");
     hob->arm_me();
     hob->move(TO);
    }
   }
}
