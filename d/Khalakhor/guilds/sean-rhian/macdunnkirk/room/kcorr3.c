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
   init_kcorr("west","east","east","south");
   add_exit("kcorr4", "south");
   add_exit("kcorr2", "east");
   add_exit("kcham1", "west");
}
