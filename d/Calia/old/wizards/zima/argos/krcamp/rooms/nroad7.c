/* Northern road through camp
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 8/1/96      Zima        Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#define  ORIGIN_MSG   " appears abruptly!"
#define  KRETAN_LIST ({"impguard/impguard0","impguard/impguard0"})
#include "sentry.h"
 
void reset_room() { make_kretans(); }
 
/* room definition */
void create_room() {
   set_short("In a military camp");
   set_long(
      "You are at the end of a dusty path in the camp, the thick forest "+
      "forming a blockade to the east. A dark stone building sits to the "+
      "south, its door replaced with strong iron bars. It is very quiet "+
      "here, an eerie stillness pervading the air.\n");
 
    add_item(({"trees","tree","pines","pine","forest"}),
       "The thick forest of black pines forms a stockade to the east, "+
       "the branches of the trees laden with sharp black needles.\n");
    add_item("path",
        "It ends here at the edge of the forest, and leads west back "+
        "through the encampment.\n");
    add_item(({"building","prison"}),
        "It is an old stone building, its walls made with boulders. You "+
        "wonder how many were required to lift each stone into its place. "+
        "Iron bars are set over the door, making it look like a prison.\n");
    add_item(({"bars","door","entrance"}),
        "The entrance of the building is blocked with a set of thick "+
        "iron bars, obviously meant to keep even the strongest out..."+
        "or perhaps in.\n");
 
    /* exits */
    add_exit("nroad6", "west", 0);
 
    reset_room();
}
