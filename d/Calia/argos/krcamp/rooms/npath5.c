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
      "A brisk wind brings the towering black pines into a harmonic "+
      "sway as you make your way down a path in a dark forest. The "+
      "ominous caw of a bird echoes through dark sea of spiny branches.\n");
 
    add_item(({"forest","trees","branches"}),
        "Towering pine trees, their bark as black as night and their " +
        "black needles sharp enough to cut.\n");
    add_item("bird","You don't see it, but you hear it in the distance.\n");
    add_item("sounds",
       "You don't see anything moving...you wonder what is making them.\n");
    add_item("sun",
       "You can't see it, though you can tell it is daytime.\n");
    add_item(({"cones","pine cones"}),
       "You see some hanging high from the branches of the black pines.\n");
    add_item("path",
       "It looks rather new, and leads to the west and northeast.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"npath4","west","@@check_blocked");
    add_exit(ROOM_DIR+"npath6","northeast",0);
    reset_room();
}
