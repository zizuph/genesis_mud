/* Satyr Forest, a Newbie area
**
** History
** Date        Coder       Action
** --------  ------------  ----------------------
** 2/18/95   Zima          Created
** 5/12/16   Jaacar        Fixed typo (eratic ->erratic)
**/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#define NumSatyrs 3
#include "sfornpcs.h"
 
/* room definition */
void create_room() {
   set_short("A dense forest");
   set_long(
       "You continue through the trees of the forest, the maples and "+
       "oaks grow so closely together like walls allowing only an "+
       "erratic path through the trees. The breeze seems to have settled "+
       "a little, quieting the rustling of the canopy of branches and "+
       "leaves overhead.\n");
 
#include "sfordesc.ext"
 
   /* exits */
   add_exit(ROOM_DIR+"sfor3","northwest",0);
   add_exit(ROOM_DIR+"sfor5","southeast",0);
   set_alarm(5.0,0.0,"reset_room");
}
