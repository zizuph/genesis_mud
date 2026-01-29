/* ARGOS - SWTERR - Dirt road along south bank of river
**
** History:
** Date      Coder      Action
** --------- ---------- --------------------------------
** 1/12/93   Zima       Created
** 11/16/95  Zima       Added Path to dirt road (nw)
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
/* room definition */
void create_room() {
   set_short("A dark forest");
   set_long(
       "You follow a narrow path through a dark forest, dead leaves " +
       "crunching under your feet. You are surrounded by ominous black-" +
       "barked oaks which seem almost dead with their brown leaves. " +
       "A heavy, shrivelled acorn falls from the trees, almost hitting " +
       "you in the head. The path continues east and west through the " +
       "forest, while you see a break in the forest leading to a dirt "+
       "road to the northeast.\n");
 
    add_item(({"forest","trees","oaks"}),
        "Black-barked oak trees with brown leaves. They look almost dead.\n");
    add_item("road",
       "It is a simple dirt road to the northeast.\n");
    add_item("acorns",
       "Poisonous looking black acorns hang from the oaks and "+
       "are scattered along the ground.\n");
   add_cmd_item(({"acorns","acorn"}),({"take","get","pick"}),
       "The acorns look poisonous so you leave them alone.\n");
 
 
 
    /* exits */
    add_exit(ROOM_DIR+"for6","west",0);
    add_exit(ROOM_DIR+"for8","east",0);
    add_exit(ROOM_DIR+"r22","northeast",0);
}
