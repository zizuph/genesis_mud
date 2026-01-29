/*
**   ARGOS - Academie - Courtyard
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   8/25/95    Zima       Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
/* room definition */
void create_room() {
   set_short("Courtyard of the Academie");
   set_long(
       "You are standing in the cloistered courtyard of a prestigious "+
       "looking building, its windowed walls buttressed by tall thin "+
       "columns framing it on the north, west and east sides. A set of "+
       "arches marks the entrance of the courtyard on the south side, "+
       "while the courtyard continues further north in the cloister of the "+
       "building.\n");
 
    add_item("building",
       "The building is constructed of white marble, its walls flanked "+
       "by tall thin columns, framing the courtyard on the west, east and "+
       "further north. Windows line the walls of the building looking out "+
       "over the courtyard.\n");
    add_item("columns",
       "The columns are set into the walls of the building, equally "+
       "spaced around the courtyard like guardian sentinels. Each "+
       "is topped with an elaborate capitol.\n");
    add_item(({"capitol","capitols"}),
       "The capitols atop the colums are sculpted in the shape of oak "+
       "leaves which fan out from their base to the top edge of the "+
       "capitol.\n");
    add_item("windows",
       "The windows overlook the couryard from all three sides of "+
       "the building.\n");
   add_item(({"courtyard","cloister"}),
       "The courtyard is set in the middle of the marble building, "+
       "the columned walls of the building framing it on the "+
       "west, north and east sides. A set of arches marks the "+
       "entrance to the courtyard to the south, while the courtyard "+
       "continues to the north carpeted with lush green grass.\n");
   add_item(({"yard","grass"}),
       "The yard is carpeted with very short green grass, its lush "+
       "color contrasting beautifully with the white marble of the "+
       "building.\n");
   add_item(({"arch","arches","set of arches"}),
       "The set of arches which frame the courtyard on the south side "+
       "are supported by the same tall thin columns which flank "+
       "the walls of the building. You may walk beneath them "+
       "to leave the courtyard.\n");
 
    /* exits */
   add_exit(ROOM_DIR+"court2","north",0);
   add_exit(METRO_DIR+"rooms/lroad4","south",0);
}
