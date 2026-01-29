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
       "You come to what is almost a clearing in the forest amongst "+
       "the maples, oaks and dogwoods. A bit of sunlight filters through "+
       "the thinning canopy of the limbs of the trees overhead, warming "+
       "you pleasantly. The forest is a bit thinner here and allows you "+
       "to walk in several directions.\n");
 
#include "sfordesc.ext"
 
   /* exits */
   add_exit(ROOM_DIR+"sfor12","northwest",0);
   add_exit(ROOM_DIR+"sfor5", "southwest",0);
   add_exit(ROOM_DIR+"sfor13","northeast",0);
   add_exit(ROOM_DIR+"sfor7", "southeast",0);
   set_alarm(5.0,0.0,"reset_room");
}
