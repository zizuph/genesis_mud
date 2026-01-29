/* Satyr Forest, a Newbie area
**
** History
** Date        Coder       Action
** --------  ------------  ----------------------
** 2/18/95   Zima          Created
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
       "This is the darkest part of the forest you have been in so far, "+
       "the densely growing trees blocking the sun until it almost seems "+
       "like dusk. The dogwoods thrive in the shade of their larger "+
       "cousins, but you wonder how they get any light at all. "+
       "You feel you better get out of here before night fall.\n");
 
#include "sfordesc.ext"
 
   /* exits */
   add_exit(ROOM_DIR+"sfor23", "northwest",0);
   add_exit(ROOM_DIR+"sfor25", "northeast",0);
   set_alarm(5.0,0.0,"reset_room");
}
