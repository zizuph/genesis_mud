/* Satyr Forest, a Newbie area
**
** History
** Date        Coder       Action
** --------  ------------  ----------------------
** 2/18/95   Zima          Created
** 2/18/97   Zima          south exit changed r14 to r14a (road extension)
** 2/28/97   Zima          Added exit to waterfall path
**/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
/* room definition */
void create_room() {
   set_short("A dense forest");
   set_long(
       "You are standing near the edge of a dense forest of maples and "+
       "oaks near a marble road. Dogwood trees are scattered throughout "+
       "the forest, splashing colors of pink and white in the shade. "+
       "The safety of the road lies to the south, but the forest "+
       "mysteriously invites you to explore its peacefulness.\n");
 
   add_item("road","A marble road lies to the south.\n");
 
#include "sfordesc.ext"
 
   /* exits */
   add_exit("sfor2","northeast",0);
   add_exit("wfpath1","northwest",0);
   add_exit("r14a", "south", 0);
}
