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
      "You are walking along a cobblestone road which winds its way "+
      "through the thick forest along a wide river. The torrents of "+
      "the river flow over the occassional boulder, its constant rush "+
      "filling the quiet of the surrounding forest.\n");
 
#include "csroad.h"
 
   add_exit("csroad04","west",0);
   add_exit("csroad02","southeast",0);
}
