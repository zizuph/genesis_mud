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
      "A gentle breeze dances through the branches of the dark forest, "+
      "cooling you as you make you way down the cobblestone road. The "+
      "road continues along the river's bank to the east and west.\n");
 
#include "csroad.h"
 
   add_exit("csroad05","west",0);
   add_exit("csroad03","east",0);
}
