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
       "The gentle breeze which rustled the leaves and branches overhead "+
       "further west has stopped, leaving the forest deafeningly quiet, "+
       "echoes of anything that moves bouncing off the trees. You stand "+
       "very still and can hear the crunch of the underbrush as something "+
       "makes its way through the woods.\n");
 
#include "sfordesc.ext"
 
   /* exits */
   add_exit(ROOM_DIR+"sfor6","northwest",0);
   add_exit(ROOM_DIR+"sfor8","northeast",0);
   set_alarm(5.0,0.0,"reset_room");
}
