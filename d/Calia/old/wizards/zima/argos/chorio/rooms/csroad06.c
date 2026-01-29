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
      "The old cobblestone road rounds a southern bend in the river "+
      "here, winding to the northwest and northeast. The wind carries "+
      "the scent of green olives, though you don't see any olive trees "+
      "around.\n");
 
#include "csroad.h"
 
   add_exit("csroad07","northwest",0);
   add_exit("csroad05","northeast",0);
}
