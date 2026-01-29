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
      "You are standing on an old cobblestone road which follows a "+
      "wide river as it meanders through a forest of hardwoods and "+
      "blooming dogwoods. The river flows briskly over boulders which "+
      "dot the river's bed, filling the quiet forest with its babbling "+
      "rush.\n");
 
#include "csroad.h"
 
   add_exit("csroad08","northwest",0);
   add_exit("csroad06","southeast",0);
}
