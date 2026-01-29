/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
#define NUM 2
object *sheep=allocate(NUM);
 
void
make_monster(int i)
{
    if (sheep[i]) {
       sheep[i]->remove_prop(SHEEP_SHEARED);
       return;
    }
    sheep[i]=clone_object(NPC_DIR+"sheep");
    sheep[i]->move(THIS);
    tell_room(THIS, QCNAME(sheep[i])+" grazes on the pasture.\n");
}
 
void
reset_room()
{
   int i;
   for (i=0; i<NUM; i++)
      make_monster(i);
}
 
/* room definition */
void
create_room()
{
   set_short("A green pasture");
   set_long(break_string(
       "You walk along the northern edge of a fenced-in pasture, covered " +
       "in short green grass.  You smell a distinctive odor here, and " +
       "decide you should watch where you step.  A fence runs along the " +
       "northern and western edges of the field, but you may walk to other " +
       "parts of the pasture to the south and east.\n",70));
 
    add_item("grass", break_string(
             "Lush green grass, kept short by grazing sheep, it covers " +
             "the gently rolling pasture.\n",70));
    add_item(({"pasture","field"}), break_string(
             "The pasture is covered with short green grass within " +
             "the fence, and stretches to the south and east.\n",70));
    add_item("fence", break_string(
             "A simple wooden fence, enclosing the field you are standing " +
             "in.  It borders the pasture to the north and west here.\n",70));
 
    reset_room();
 
    /* exits */
    add_exit(ROOM_DIR+"past6","east",0);
    add_exit(ROOM_DIR+"past2","south",0);
}
