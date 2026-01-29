inherit "/d/Shire/eastroad/smial";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


#define EXIT1 MICH_DIR + "burrow/3b","east",0,1



void
create_room()
{
   
   areaname  = "Michel Delving"; /*Name of village*/
   land          = "the Shire"; /*Name of land   */
   roomtype  = 3; /*Type of room in the smial   */
   areatype   = "town"; /*Type of village*/
   smialsize   = "large"; /*Size of the house*/
   
   extraline = "A smooth circular dining table is placed carefully in "+
   "the center of this room.  This room is rather large and the "+
   "smooth circular dining table could accomodate many hobbits "+
   "at a feast.  A "+
   "window is cut into the eastern wall.";

   add_item(({"dining table","table","smooth dining table","circular table"}),
   "The smooth circular dining table is hardly scratched at all. "+
   " On careful examination "+
   "you notice candlestick marks in the center.\n");

   add_item(({"marks","candlestick marks","mark"}),"The marks seem to be "+
   "from a heavy candlestick.\n");

   add_item("window","Looking through the window, you can "
      +"see the "+areatype+" of "+areaname+".\n");

   add_exit(EXIT1);

   
   make_the_room();

}
