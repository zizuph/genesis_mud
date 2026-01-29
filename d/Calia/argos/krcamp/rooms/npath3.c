/* Northern Path through dark forest around Kretan Camp
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 12/2/95     Zima        Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include "reduce.h"
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#define KRETAN_LIST ({"sentry/sentry3","sentry/sentry3","sentry/sentry3"})
#define  ORIGIN_MSG   " steps out from the woods"
#include "sentry.h"
#include "kr_reset.h"

/* room definition */
void create_room() {
   set_short("A path through a dark forest");
   set_long(
      "You are standing at the intersection of two light paths in the "+
      "middle of a dark forest. Tall pines with sharp black needles crowd "+
      "the paths, one leading west and east, while the other runs "+
      "south.\n");
 
    add_item(({"forest","trees","branches"}),
        "Towering pine trees, their bark as black as night and their " +
        "black needles sharp enough to cut.\n");
    add_item("sounds",
       "You don't see anything moving...you wonder what is making them.\n");
    add_item("sun",
       "You can't see it, though you can tell it is daytime.\n");
    add_item(({"cones","pine cones"}),
       "You see some hanging high from the branches of the black pines.\n");
    add_item(({"path","paths"}),
       "They look newly made. One runs west and east, while another "+
       "leads south.\n");
    /* exits */
    add_exit(ROOM_DIR+"npath2","west",0);
    add_exit(ROOM_DIR+"npath4","east",0);
    add_exit(ROOM_DIR+"mroad1","south",0);
    reset_room();
}
