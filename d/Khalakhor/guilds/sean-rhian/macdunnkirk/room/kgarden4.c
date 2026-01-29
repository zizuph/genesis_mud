/* Kirk of Port City - Abbey garden
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 1/18/98     Zima        Created
**
*/
#include "defs.h"
inherit  ROOM+"kgardbase";
 
/* room definition */
void create_khalakhor_room() {
   setup_garden_room();
   set_long((query_std_long())+"\n");
 
   add_exit("kgarden3","west");
   add_exit("kgarden2","south");
}
