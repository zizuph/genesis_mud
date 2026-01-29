/*
**   ARGOS - Metro - Chiphas Road
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   8/12/95    Zima       Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
void create_room() {
   set_short("Chiphas Road");
   set_long(
       "The craftsmanship of the columns which ring the Amphitheatre "+
       "to the south impresses you as you make way down Chiphas road. "+
       "An official looking building sits on the north side of the road, "+
       "a blue banner hanging next to its entrance. Chiphas road "+
       "continues east and west through the city.\n");
 
   add_item("road","It runs east and west.\n");
   add_item("building",
       "Pillars are set into the wall of the building, their capitols "+
       "supporting a shallow angled roof on top. The banner hanging next to "+
       "the entrance tells you it is some kind of government building.\n");
   add_item("banner",
       "Made of blue silk, the banner is embroidered with the arms "+
       "of Argos, a shield emblazoned with a rampant winged horse, "+
       "surmounted by a crown with three jewels.\n");
   add_item(({"Amphitheatre","amphitheatre"}),
       "The Ampthitheatre of Argos sits on the south side of the road "+
       "It is an open-air place where citizens "+
       "and visitors alike gather to see dramatic and comic productions. "+
       "It is faced with a line of very tall "+
       "columns which stand in a quarter-circle from its northeastern "+
       "to its southwestern corner. You see no entrance through the "+
       "curve of columns here.\n");
   add_item(({"column","columns"}),
       "Standing in a curving line, the columns reach high into the "+
       "sky and form the facade of the Amphitheatre, curving from "+
       "its northeastern to its southwestern corners. Each column "+
       "is topped with a capitol sculpted with happy and sad-faced "+
       "actors' masks.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"post",    "north",0);
   add_exit(ROOM_DIR+"croad15", "east",0);
   add_exit(ROOM_DIR+"trroad11","west",0);
}
