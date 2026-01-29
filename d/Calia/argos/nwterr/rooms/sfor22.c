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
       "The trees of the forest grow larger, thicker and taller in this "+
       "part of the woods, the shade of their branches making the forest "+
       "floor darker than it is to the west. The underbrush is strangely "+
       "thinner here, as if something has eaten it away, but is still "+
       "deep enough to lose a large object.\n");
 
#include "sfordesc.ext"
 
   /* exits */
   add_exit(ROOM_DIR+"sfor21", "west",0);
   add_exit(ROOM_DIR+"sfor31", "northwest",0);
   add_exit(ROOM_DIR+"sfor32", "southwest",0);
   add_exit(ROOM_DIR+"sfor23","east",0);
   set_alarm(5.0,0.0,"reset_room");
}
