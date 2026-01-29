/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
/* room definition */
void
create_room()
{
   set_short("A clearing in the woods");
   set_long(break_string(
       "You walk into a clearing in the forest, which grows densely "    +
       "to the east and south.  To the west you see a small dwelling, " +
       "probably the home of a local agrarian.  A small path leads "    +
       "northeast into a pallisade, while another cuts through the " +
       "forest to the south.\n",70));
 
    add_item("forest", "It grows densely to the west and south.\n");
    add_item(({"paths","paths"}), break_string( 
       "One leads northeast into a pallisade, while another cuts " +
       "south through the forest.\n",70));
    add_item(({"pallisade","pallisades"}), break_string( 
             "It is a solid fence made of tall, straight tree-trunks, " +
             "surrounding an area to the north.\n",70));
    add_item("dwelling", break_string(
             "Made of wood with a red roof, the small dwelling " +
             "seems a bit run down, though lived-in.\n",70));
 
    /* exits */
    add_exit(ROOM_DIR+"vyardd","west",0);
    add_exit(ROOM_DIR+"vyard5","northeast",0);
    add_exit(ROOM_DIR+"r23","south",0);
}
