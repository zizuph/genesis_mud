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
       "The dogwoods grow very sparsely in this dark part of the forest, "+
       "only a very few scattered beneath the sun-blocking canopy of the "+
       "oaks and maples. The forest is very quiet here, not even a bird "+
       "or a gentle breeze to interrupt the tranquility.\n");
 
#include "sfordesc.ext"
 
   /* exits */
   add_exit(ROOM_DIR+"sfor8", "west",0);
   add_exit(ROOM_DIR+"sfor10","east",0);
   set_alarm(7.0,0.0,"reset_room");
}
