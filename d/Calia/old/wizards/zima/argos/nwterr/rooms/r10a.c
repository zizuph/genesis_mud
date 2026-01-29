/* Argos Road
** History
** Date        Coder         Action
** -------- ---------------  ------------------------------------------
** 1993     Zima             Created
** 9/15/96  Zima             Cleaned up, messages added to mountain exits
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
/* room definition */
void create_room() {
   set_short("A marble road at the summit of a mountain");
   set_long(
       "Chilling winds buffet you as you stand atop the summit of a " +
       "large mountain along a marble road. You have an eagle's-eye " +
       "view of the east and west from here, truly breath-taking sights. " +
       "The marble road descends down the side of the mountain to the " +
       "east, and continues along the mountain's craggy summit to the " +
       "northwest.\n");
 
    add_item("road",
       "Made of long slabs of white marble, this road seems fairly " +
       "new. It descends the mountain on the east side and runs " +
       "along the top of the summit to the northwest.\n");
    add_item("mountains",
       "The mountain chain slinks off into the horizon to the north " +
       "and south. The ground is very rocky around the steep road, " +
       "only boulders breaking the craggy top of the mountain.\n");
    add_item("boulders",
        "Huge mounds of granite, some of these seem ready to " +
        "avalanche down the mountain at the slightest touch.\n");
    add_item("west",
        "To the west, you see the mountain descend down into a " +
        "forested plain, the marble road winding through the trees " +
        "and boulders.\n");
    add_item("view",
       "You have a magnificent view to the east and west.\n");
    add_item("east",
        "To the east, you see a lush valley, with a river flowing " +
        "through it. Far off, the river seems to split and rejoin, " +
        "some sign of civilization on the island between the splits. " +
        "The marble road descends down into the valley to the east.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"r10","northwest",0);
    add_exit(ROOM_DIR+"r11","down","@@dodown");
}
int dodown() {
   write("You walk down the road to the east.\n");
   return 0;
}
