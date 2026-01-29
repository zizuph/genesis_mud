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
       "You continue down Lambdos road on the western side of the "+
       "city of Argos, between a large temple on the south side of "+
       "the road, and a prestigious building on the north. The busy "+
       "center of town lies further to the east, while the entrance "+
       "to the city is to the west.\n");
 
    add_item("building",
             "The building on the north side of the road is another "+
             "of the marble structures which make up the city. Tall "+
             "thin columns with elaborate capitals flank the walls "+
             "of the building, where windows look out over the "+
             "road. You see no entrance to it here.\n");
    add_item(({"columns","capitols"}),
             "The columns of the building to the north are topped "+
             "with elaborate capitols which are sculpted in the "+
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
             "its walls butressed by towering pillars. You don't see "+
             "an entrance to the temple here.\n");
    add_item("pillars",
             "The stand along the wall of the temple like a column "+
             "of guardians.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"lroad1","west",0);
    add_exit(ROOM_DIR+"lroad3","east",0);
}
