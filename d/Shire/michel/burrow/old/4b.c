inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


#define EXIT1 MICH_DIR + "burrow/4c","east",0,1




void
create_room()
{
   
   areaname  = "Michel Delving"; /*Name of village*/
   land          = "the Shire"; /*Name of land   */
   roomtype  = 3; /*Type of room in the smial   */
   areatype   = "town"; /*Type of village*/
   smialsize   = "large"; /*Size of the house*/
   
   extraline = "An ordinary square maple dining table seems too small for this "+
   "spacious dining room.  A small "+
   "window is cut into the western wall.";

   add_item(({"dining table","table","square maple table","maple table"}),
   "The square maple dining table is very dusty and seems to be "+
   "little used by the residents of this smial.  On careful examination "+
   "you can see the letter k written in the dust.\n");

   add_item("window","Looking through the window, you can "
      +"see the "+areatype+" of "+areaname+".\n");

   add_exit(EXIT1);

   make_the_room();

}
