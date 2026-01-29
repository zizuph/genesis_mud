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
   init_kcorr("north","south","east","west");
   add_exit("kdining","north");
   add_exit("kcorr1", "east");
   add_exit("kcorr3","west");
}
