/* Kirk of Port City - Corridor
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 5/25/97     Zima        Created
**
*/
/* inherits/includes */
#include "defs.h"
inherit  ROOM+"kcorr";
 
/* room definition */
void create_khalakhor_room() {
   init_kcorr("west","east","north","south");
   add_exit("kcorr3",  "north");
   add_exit("kcorr5",  "south");
   add_exit("kcandles","west");
}
