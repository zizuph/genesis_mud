/*
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
 
/* room definition */
void create_room() {
   set_short("A dense forest");
   set_long(
       "You stop momentarily to admire the beauty of the woods and "+
       "suddenly realize you hear something stomping through the "+
       "underbrush of the forest to the south. You guess it is probably "+
       "just some woodland creature frolicking amongst the trees. The "+
       "gentle breeze continues to carry the bittersweet scents of "+
       "the forest to your nostrils.\n");
 
#include "sfordesc.ext"
 
   /* exits */
   add_exit(ROOM_DIR+"sfor2","southwest",0);
   add_exit(ROOM_DIR+"sfor4","southeast",0);
}
 
 
 
