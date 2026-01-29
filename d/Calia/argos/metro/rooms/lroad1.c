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
       "You come to the end of Lambdos road on the western side "+
       "of the city of Argos. The river which surrounds the city "+
       "rushes off to the north and south. A massive arch covers a " +
       "bridge over the river to the west, the entrance to the city. "+
       "The road continues to the east toward the center of town, "+
       "paralleling the high wall of a large temple to the south.\n");
 
    add_item(({"city","town","center","center of town"}),
             "The center of town is to the east.\n");
    add_item("arch",
             "It is an enormous arch made of marble built over the "+
             "bridge to the west. Through it you can leave the city.\n");
    add_item("bridge",
             "It spans the river to the west, covered by a monumental "+
             "arch.\n");
    add_item("road",
             "Made of long slabs of white marble, this road seems fairly " +
             "old.  It runs between the river and the temple to the east.\n");
    add_item("river",
             "The river is very wide, and seems deep with its rushing "+
             "torrents. The forest on the other side of the river is "+
             "heavily forested with oak and maple trees.\n");
    add_item("forest",
             "Stately oaks and maples grow densely on the other side of " +
             "the river.\n");
    add_item("temple",
             "A large temple made of white marble sits to the south, "+
             "its walls butressed by towering pillars. You don't see "+
             "an entrance to the temple here.\n");
    add_item("pillars",
             "They stand along the wall of the temple like a column "+
             "of guardians.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"arch",  "west",0);
    add_exit(ROOM_DIR+"lroad2","east",0);
}
