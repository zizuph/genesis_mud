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
      "The rush of the river lulls you as you make your way down an "+
      "old cobblestone road which runs along its northern bank. Through "+
      "the trees to the northeast, you see evidence of a small village "+
      "built on the slope of a large hill. The forest around the river "+
      "is tranquil, and the canopy of its trees shade your path.\n");
 
#include "csroad.h"
 
   add_exit("csroad03","northwest",0);
   add_exit("csroad01","southeast",0);
}
