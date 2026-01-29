/* Satyr Forest, a Newbie area
**
** History
** Date        Coder       Action
** --------  ------------  ----------------------
** 2/18/95   Zima          Created
** 7/7/95    Maniac        Link to Amelia's pond area added
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
       "The thick underbrush crackles beneath your feet as you tromp "+
       "through this peaceful forest of maples, oaks and dogwoods. A "+
       "gentle breeze stirs the branches of the trees overhead and "+
       "refreshes you as you enjoy the calming solitude of the woods.\n");
 
#include "sfordesc.ext"
 
   /* exits */
   add_exit(ARGOS_CONNECT_TO_POND+"nearp", "north", 0);
   add_exit(ROOM_DIR+"sfor3","northeast",0);
   add_exit(ROOM_DIR+"sfor1","southwest",0);
}
