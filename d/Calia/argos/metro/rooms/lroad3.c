/*
**   ARGOS - Metro - Lambdos road
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   1/30/95    Zima       Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
/* room definition */
void
create_room()
{
   set_short("Lambdos Road");
   set_long(
       "A gentle breeze brings a little relief from the day's warmth "+
       "as you make your way down Lambdos road. "+
       "You notice an entrance in the wall of the grand temple on the "+
       "south side of the road, a small set of steps leading up to it. "+
       "To the north is a prestigious looking building with tall thin "+
       "columns and windows which look out over the road. The heart of "+
       "the city lies east while the entrance of the city is further "+
       "west.\n");
 
 
    add_item("building",
             "The building on the north side of the road is another "+
             "of the marble structures which make up the city. Tall "+
             "thin columns with elaborate capitals flank the walls "+
             "of the building, where windows look out over the "+
             "road. You see no entrance to it here.\n");
    add_item(({"columns","capitols"}),
             "The columns of the building to the north are topped "+
             "with elaborate capitols sculpted in the "+
             "shape of oak leaves.\n");
    add_item("windows","They overlook the road from the building to "+
             "the north.\n");
    add_item(({"city","town","center","center of town"}),
             "The center of town is to the east.\n");
    add_item("road",
             "Made of long slabs of white marble, this road seems fairly " +
             "old.\n");
    add_item("temple",
             "A large temple made of white marble sits to the south, "+
             "its walls butressed by towering pillars. There is an "+
             "entrance to the temple up a set of steps.\n");
    add_item("entrance",
             "It is a small doorway into the temple at the top of the "+
             "steps. It looks like a back entrance. Unfortunately, "+
             "its door is closed and barred.\n");
    add_item("door",
             "It is a large brass door bearing the emblem of a falcon. "+
             "It is closed and barred.\n");
    add_item("steps",
             "A small set of steps lead up to the temple's entrance.\n");
    add_item("pillars",
             "The stand along the wall of the temple like a column "+
             "of guardians.\n");
 
    /* exits */
   add_exit(ROOM_DIR+"lroad2","west",0);
   add_exit(ROOM_DIR+"lroad4","east",0);
   add_exit(ROOM_DIR+"closed","steps","@@closed");
}
int closed() {write("The temple is closed for now.\n"); return 1; }
