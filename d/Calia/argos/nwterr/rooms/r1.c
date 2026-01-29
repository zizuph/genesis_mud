/* Path connecting Argos to Calia,
   Coded by Zima.

   History:
            6/3/2000 new connections added                       Maniac
           16/5/95   West connection changed                     Maniac
           10/5/95   Path to Malcontent's Chaos area taken out   Maniac
*/

/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#define WEST_CONNECT "/d/Calia/mountain/road/road19"
#define NORTHWEST_CONNECT "/d/Calia/gelan/rooms/entrance_road"
#define SOUTHWEST_CONNECT "/d/Calia/mountain/road/road18"
 
/* room definition */
void
create_room()
{
   set_short("A light path");
   set_long(break_string(
       "You are standing on a narrow path, not much more than trodden " +
       "grass, which seems to wind southeast through the dense forest " +
       "which surrounds you.  The breeze blows lightly through the " +
       "trees, and some sunlight manages to beam down through the " +
       "thick shelter of the leaves above.  Though the forest " +
       "looks rather thick, and you doubt the path goes very far, " +
       "the peaceful forest gives you a feeling of ease and you " +
       "see no reason why you shouldn't explore further.  The path " +
       "disappears into the forest to the southeast, while you see " +
       "a large roundabout to the west.\n", 70));
 
 
    add_item("path", break_string(
        "Not much more than trodden-down grass, the small path winds " +
        "to the southeast through the trees.\n",70));
 
    add_item(({"canopy","leaves"}), break_string(
        "The dense canopy of leaves provides a peaceful shade " +
        "as you stand amongst the trees.\n",70));
 
    add_item("forest", break_string(
        "A mixture of maples, oaks and evergreens, the forest " +
        "seems dense but rather harmless.\n",70));
 
    /* exits */
    add_exit(NORTHWEST_CONNECT, "northwest"); 
    add_exit(SOUTHWEST_CONNECT, "southwest"); 
    add_exit(WEST_CONNECT, "west",0);
    add_exit(ROOM_DIR+"r2","southeast",0);
}
