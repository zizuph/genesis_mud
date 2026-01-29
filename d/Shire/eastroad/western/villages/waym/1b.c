#include "../local.h"

inherit SMIAL;

static object hob;

void
create_smial()
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

   add_exit(WAYMET_DIR + "1a","west");
   reset_shire_room();
}

void
reset_shire_room()
{
   if (!hob)
     {
      	hob = clone_object(HOBBITMAKER);
   	hob->set_type(CITIZEN);
	hob->set_power(60);
   	hob->move(TO);
      }

}
