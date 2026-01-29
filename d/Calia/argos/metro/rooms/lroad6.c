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
       "You are walking down Lambdos road near the northwest corner of "+
       "the center of town, the corner of a prestigious building to "+
       "the north and a small grove of maples to the south. The busy "+
       "sounds of the "+
       "city entice you toward its center to the east, while the road "+
       "leads west along a quieter trail.\n");
 
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
             "old.  It is shaded here by trees on the south.\n");
    add_item(({"forest","trees","stand"}),
             "A small grove of oaks stands to the south, "+
             "their reaching branches shading your path.\n");
 
    /* exits */
   add_exit(ROOM_DIR+"lroad5","west",0);
   add_exit(ROOM_DIR+"lroad7","east",0);
}
