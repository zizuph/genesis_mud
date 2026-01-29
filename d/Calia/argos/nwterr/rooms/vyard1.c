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
   set_long(
       "You walk into a clearing in the forest, which grows densely "    +
       "to the east and south. To the west you see a small dwelling, " +
       "probably the home of a local agrarian. A small path leads "    +
       "northeast into a palisade, while another cuts through the " +
       "forest to the south.\n");
 
    add_item("forest", "It grows densely to the west and south.\n");
    add_item(({"paths","paths"}),
       "One leads northeast into a palisade, while another cuts " +
       "south through the forest.\n");
    add_item(({"palisade","palisades"}),
             "It is a solid fence made of tall, straight tree-trunks, " +
             "surrounding an area to the north.\n");
    add_item("dwelling",
             "Made of wood with a red roof, the small dwelling " +
             "seems a bit run down, though lived-in.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"vyardd","west",0);
    add_exit(ROOM_DIR+"vyard5","northeast",0);
    add_exit(ROOM_DIR+"r23","south",0);
}
