/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
/* room definition */
void
create_room()
{
   set_short("A bridge over a rushing river");
   set_long(break_string(
       "You are standing on a slightly arched wooden bridge which " +
       "spans a rushing river.  To the north, you see a marble road " +
       "running through a forest of oaks and maples, while to the " +
       "south, a dirt road runs along the river next to a dark forest " +
       "of black trees, covered in strangling vines.\n",70));
 
    add_item("river", break_string(
       "The river is very wide, and seems deep with its rushing torrents.  " +
       "Water rolls noisily over boulders in the middle of the stream.\n",70));
 
    add_item("bridge", break_string(
        "Spanning the rushing torrent of the river, " +
        "this wooden bridge looks old, but sturdy.\n",70));
 
    /* exits */
    add_exit(ROOM_DIR+"r21","north",0);
    add_exit(SWTERR_DIR+"rooms/r21","south",0);
}

int washed_out() {
   write("The southern half of the brige has been washed out by a "+
         "recent storm. It should "+
         "be repaired shortly.\n");
   return 1;
}
