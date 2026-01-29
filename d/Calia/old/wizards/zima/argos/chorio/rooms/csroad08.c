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
      "You come to a bend in the river along the cobblestone road, "+
      "the swift flow of the stream turning to the southeast from the "+
      "west. The trees of the forest grow close to the side of the road, "+
      "their branches shading your path.\n");
 
#include "csroad.h"
 
   add_exit("csroad09","west",0);
   add_exit("csroad07","southeast",0);
}
