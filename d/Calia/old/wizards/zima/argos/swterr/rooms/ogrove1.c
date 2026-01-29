/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
/* room definition */
void
create_room()
{
   set_short("A clearing in a dark forest");
   set_long(break_string(
       "This clearing in the forest is surrounded by dark mohagany " +
       "trees, creeping vines crawling up their massive trunks.  "  +
       "A small dwelling is built on the west side of the clearing, " +
       "probably the home of one of the local agrarians.  A well-"  +
       "beaten path leads southwest into a grove of trees.\n",70));
 
   add_item(({"forest","trees"}),  break_string(
       "Cleared away in this area, the mohagany trees tower high, " +
       "their black bark covered with creeping vines.\n",70));
   add_item("vines", break_string(
            "Crawling up the trunks of the trees, they " +
            "almost cover the base of some.\n",70));
   add_item("dwelling",
            "A small wooden hut with a black tile roof.\n");
 
   add_item("grove",
            "A grove of trees lining the clearing to the south.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"r24","north",0);
    add_exit(ROOM_DIR+"ogroved","west",0);
    add_exit(ROOM_DIR+"ogrove2","southwest",0);
}
