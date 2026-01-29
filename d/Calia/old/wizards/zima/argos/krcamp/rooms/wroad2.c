/* Road through Batallion Five Camp
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 8/1/96      Zima        Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#define  ORIGIN_MSG   " takes his post."
#define KRETAN_LIST ({"sentry/sentry4"})
#include "sentry.h"
 
void reset_room() { make_kretans(); }
 
/* room definition */
void create_room() {
   set_short("In a military camp");
   set_long(
      "You are walking along a path on the western side of the camp. "+
      "There is an entrance to one of the round tents to the east, while "+
      "you seen an old stone building to the south. The forest of dark "+
      "pines rises along the western edge of the path, which runs to the "+
      "north and southeast.\n");
 
    add_item("building",
       "It is an old, run-down building, probably an abandoned house. "+
       "Its walls are made of vine covered stones, and it is roofed "+
       "with cracked clay tiles. You don't see an entrance or even a "+
       "window on this side.\n");
    add_item(({"trees","tree","pines","pine","forest"}),
       "They are tall dark pines with black bark and needles grow "+
       "thickly along the western side of the path.\n");
    add_item("path",
        "Just a dusty path which winds through the tents in this "+
        "part of the encampment. It leads north and southeast between "+
        "the thick forest and a line of tents.\n");
    add_item(({"cluster","tent","tents","entrance","entrance","flap",
       "flaps","camp","encampment"}),
       "Large round tents sit to the east, with their tall "+
       "cone-shaped tops rising to a point. They are made of canvas "+
       "striped vertically with various colours. There is an entrance "+
       "to one of them open to the east.\n");
 
    /* exits */
    add_exit("wroad1", "north",0); /* make blocked when wroad3 opened */
    add_exit("wroad3", "southeast","@@closed");
    add_exit("b5tent7","east","@@check_blocked");
 
    reset_room();
}

int closed() { 
   write("A strange force prevents you from going that way.\n");
   return 1;
}
