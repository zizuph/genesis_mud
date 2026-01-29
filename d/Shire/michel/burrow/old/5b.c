inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


#define EXIT1 MICH_DIR + "burrow/5c","south",0,1
#define EXIT2 MICH_DIR + "burrow/5a","northwest",0,1



void
create_room()
{
   
   areaname  = "Michel Delving"; /*Name of village*/
   land          = "the Shire"; /*Name of land   */
   roomtype  = 3; /*Type of room in the smial   */
   areatype   = "town"; /*Type of village*/
   smialsize   = "large"; /*Size of the house*/
   
   extraline = "A walnut table is the focus of the eating activities "+
   "of this smial.  This dining room is of a good size and the "+
   "walnut dining table, which could serve six "+
   "hobbits, fits nicely in the room.  A small "+
   "window is cut into the eastern wall.";

   add_item(({"dining table","table","ordinary dining table","walnut table"}),
   "The walnut table is of a light shade and seems to be in "+
   "regular use by the residents of this smial.  On careful examination "+
   "you notice a hole in one of the edges of the table.\n");

   add_item("window","Looking through the window, you can "
      +"see the "+areatype+" of "+areaname+".\n");

   add_exit(EXIT1);
   add_exit(EXIT2);
   
   make_the_room();

}
