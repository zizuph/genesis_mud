/* North road through camp
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 8/1/96      Zima        Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include "reduce.h"
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#define  ORIGIN_MSG   " takes his post."
#define  KRETAN_LIST ({"soldier/soldier3","soldier/soldier3", \
                       "soldier/soldier3"})
#include "sentry.h"
#include "kr_reset.h"

/* room definition */
void create_room() {
   set_short("In a military camp");
   set_long(
      "The dark forest closes in on the norther side of the dusty path, "+
      "the trunks of is black pines a seemingly impregnable wall around "+
      "the camp. A tent sits on the southern side of the path, which "+
      "winds its way through the encampment to the east and west.\n");
 
    add_item(({"trees","tree","pines","pine","forest"}),
       "They are tall dark pines with black bark and needles grow "+
       "thickly along the northern side of the path.\n");
    add_item(({"camp","encampment"}),
       "It is a military camp, its dusty foot-trodden paths "+
       "lined with round pointed-top tents on all about.\n");
    add_item("path","It winds through the camp to the east and west.\n");
    add_item(({"cluster","tent","tents"}),
       "It is one of the large round tents with a pointed top, green stripes "+
       "descending down its canvas sides. You see no entrance to it here.\n");
 
    /* exits */
    add_exit("nroad3","east",0);
    add_exit("nroad1","west","@@check_blocked");
    reset_room();
}
