/* ARGOS - NWTERR - Marble Road along river
**
** History:
** Date       Coder          Action
** -------- ------------ -------------------------------------
** 1/93     Zima         Created
** 11/12/95 Zima         Removed bridge across river
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
/* room definition */
void create_room() {
   set_short("A marble road along a river");
   set_long(
       "You walk along the northern bank of a rushing river on " +
       "a marble road. The river bends from the northwest to the " +
       "east here, rushing over boulders in the middle. " +
       "The forest grows thickly on the northern " +
       "side of the road, though a few trees seemed to have been " +
       "cleared away. The road follows the river to the northwest and "+
       "east.\n");
 
    add_item("road",
       "Made of long slabs of white marble, this road seems fairly " +
       "new. It runs along the river to the northwest and east.\n");
    add_item("bridge",
       "The old bridge which used to be here was washed out.\n");
    add_item("river",
       "The river is very wide, and seems deep with its rushing torrents. " +
       "The forest on the other side of the river seems dark and " +
       "mysterious.\n");
    add_item("forest",
        "Stately oaks and maples grow densely all around along the " +
        "northern side of the road, though a few seem to have been " +
        "cleared away.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"r20","northwest",0);
    add_exit(ROOM_DIR+"r22","east",0);
    add_exit(ROOM_DIR+"for5","north",0);
}
