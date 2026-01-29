inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 ER_DIR + "village/frog/frog1kit","west",0,1



void
create_room()
{
   
   areaname  = "Frogmorton";/*Name of village*/
   land          = "the Shire";/*Name of land   */
   roomtype  = 10;/*Type of room in the smial   */
   areatype   = "village";/*Type of village*/
   smialsize   = "large";/*Size of the house*/
   
   extraline = "Bushels, boxes, crates and trays of food and "+
   "spices fill this pantry. There is no doubt that food ranks "+
   "very high up in a hobbit's daily priority, possibly even "+
   "number one. Despite the vast amount of provisions, everything "+
   "is orderly and easy to reach.";
   
   add_item (({"bushels","boxes","box","crate","crates","tray","trays"}),"Piled "+
      "high with food of all kinds, these containers are neatly "+
      "stacked and all within easy reach of the halflings. Apparently "+
      "apples are a favorite, as many bushles of them are here.\n");
   
   
   add_exit(EXIT1);
   
   make_the_room();
}

