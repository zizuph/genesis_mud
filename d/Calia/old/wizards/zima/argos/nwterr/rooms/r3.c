/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
#define NUM 2
object *guard=allocate(NUM);
 
void
make_guard(int i)
{
    if (guard[i]) return;
    guard[i]=clone_object(NPC_DIR+"guard");
    guard[i]->equip_me();
    guard[i]->move(THIS);
    tell_room(THIS, QCNAME(guard[i])+" takes his post.\n");
}
 
void
reset_room()
{
   int i;
   for (i=0; i<NUM; i++) make_guard(i);
}
 
/* room definition */
void
create_room()
{
   set_short("A path through the forest");
   set_long(break_string(
       "You come to a bend in a narrow path which leads through a " +
       "dense forest. Sunlight barely manages to penetrate the " +
       "thick canopy of leaves above, though the shade seems rather " +
       "peaceful and cool.  You hear a forest animal racing along " +
       "through the branches of the trees, though you can not see " +
       "it.  The path continues to the west and to the southeast " +
       "through the trees.\n",70));
 
    add_item("path", break_string(
        "A narrow dirt path winding through the trees, somewhat muddy " +
        "from recent rains.  It leads west and southeast through " +
        "the trees.\n",70));
 
    add_item(({"canopy","leaves"}), break_string(
        "The dense canopy of leaves provides a peaceful shade " +
        "as you walk along the winding path.\n",70));
 
    add_item("forest", break_string(
        "A mixture of maples, oaks and evergreens, the forest " +
        "grows densly on either side of the path.\n",70));
 
    /* exits */
    add_exit(ROOM_DIR+"r2b","west",0);
    add_exit(ROOM_DIR+"r4","southeast",0);
    reset_room();
}
