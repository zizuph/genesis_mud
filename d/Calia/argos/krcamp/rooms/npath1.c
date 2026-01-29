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
      "Strange sounds surround you as you make your way down this narrow "+
      "path through the forest. The dark pines rise high above you, their "+
      "sharp black needles almost blocking the sun.\n");
 
    add_item(({"forest","trees","branches"}),
        "Towering pine trees, their bark as black as night and their " +
        "black needles sharp enough to cut.\n");
 
    add_item("sounds",
       "You don't see anything moving...you wonder what is making them.\n");
    add_item("sun",
       "You can't see it, though you can tell it is daytime.\n");
 
    add_item("path",
       "It looks rather new, and leads to the northwest and northeast.\n");
 
    /* exits */
    add_exit(SWTERR_DIR+"rooms/for15","northwest",0);
    add_exit(ROOM_DIR+"npath2","northeast","@@check_blocked");
    reset_room();
}
