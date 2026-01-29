/* Road to Argos
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 1/30/97     Zima        Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
/* room definition */
void create_room() {
   set_short("A cobblestone road along a river");
   set_long(
      "You are walking down an old cobblestone road through a dense "+
      "forest as it parallels a wide, rushing river to the south. The "+
      "river and road turn here, from the southwest to the east.\n");
 
#include "csroad.h"
 
   add_exit("csroad06","southwest",0);
   add_exit("csroad04","east",0);
}
