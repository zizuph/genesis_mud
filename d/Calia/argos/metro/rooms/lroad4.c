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
       "You admire the architecture of a set of arches which lead "+
       "into the courtyard of a building to the north as you "+
       "walk down Lambdos road. The high walls of the temple to the "+
       "south with its massive pillars make it look almost like a fortress. "+
       "Lambdos road leads east into town and west toward the river.\n");
 
    add_item(({"arch","arches","entrance"}),
       "A set of arches mark the entrance to the courtyard of a "+
       "prestigious looking building to the north. Their tall "+
       "thin columns support capitols sculpted with oak leaves. "+
       "An inscription is written in large sharp letters across "+
       "the top of the arches.\n");
    add_item("inscription",
       "It is written above the arches. Perhaps you can read it.\n");
    add_cmd_item("inscription","read",
       "It reads: ACADEMIE OF ARGOS.\n");
    add_item("courtyard",
       "It lies to the north behind the set of arches.\n");
    add_item("building",
             "The building on the north side of the road is another "+
             "of the marble structures which make up the city. Tall "+
             "thin columns with elaborate capitals flank the walls "+
             "of the building, where windows look out over the "+
             "road. Arches mark the entrance to the courtyard of the "+
             "building.\n");
    add_item(({"columns","capitols"}),
             "The columns of the building to the north are topped "+
             "with elaborate capitols sculpted in the "+
             "shape of oak leaves.\n");
    add_item("windows","They overlook the road from the building to "+
             "the north.\n");
 
    add_item("city", "It is to the east.\n");
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
    add_exit(ROOM_DIR+"lroad3","west",0);
    add_exit(ROOM_DIR+"lroad5","east",0);
    add_exit(ACADEMIE_DIR+"rooms/court1","north");
}
