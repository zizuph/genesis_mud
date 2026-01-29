inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "../local.h"

#define EXIT1 ER_BASE_DIR + "village/waym/1a","west",0,1

void reset_room();

static object hob;

void
create_room()
{
   
   areaname  = "Waymeet";		/*Name of village*/
   land          = "the Shire";		/*Name of land   */
   roomtype  = 2;				/*Type of room in the smial   */
   areatype   = "hamlet";			/*Type of village*/
   smialsize   = "small";			/*Size of the house*/
   
   extraline = "Above the fireplace there is a painting of a "
   	+"village, and there are a number of knicknacks on the "
   	+"mantle above the fire. This room looks very cosy.";
   
   add_item("painting",
      "This painting shows a rather rustic scene - a hobbit "
      +"village with jolly little hobbit smials dug into a hill, "
      +"and a little stream merrily running past the hill.\n");
 
   add_item("knicknacks",
      "These are the sort of trite curios that you often see "
      +"decorating fireplaces.\n");

   reset_room();
  
   add_exit(EXIT1);

   make_the_room();
}

void
reset_room()
{
   if (!hob)
     {
      	hob = clone_object(ER_BASE_DIR +"npc/whobbit");
   	hob->arm_me();
   	hob->move(TO);
      }

}
