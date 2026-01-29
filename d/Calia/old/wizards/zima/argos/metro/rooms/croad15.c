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
       "You are walking down Chiphas road on the east side of town, "+
       "the city's Amphitheatre with its outer ring of columns to the "+
       "south. There is an entrance to one of the city's businesses "+
       "to the north, a flat-topped building made of marble like most "+
       "of the others in the commercial district. Chiphas road continues "+
       "to the east and west.\n");
 
   add_item("road","It runs east and west.\n");
   add_item(({"business","building","entrance"}),
       "It is one of the single level, flat-topped buildings of the "+
       "commercial district of Argos, housing one of the city's "+
       "thriving businesses. A simple sign is bolted next to the "+
       "entrance to the north.\n");
   add_cmd_item("sign","read","It reads: PIESTERIO OF ARGOS.\n");
   add_item("sign",
       "It is a simple wooden sign which reads: PIESTERIO OF ARGOS.\n");
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
   add_exit(ROOM_DIR+"press","north",0);
   add_exit(ROOM_DIR+"troad11",  "east",0);
   add_exit(ROOM_DIR+"croad14",  "west",0);
}
