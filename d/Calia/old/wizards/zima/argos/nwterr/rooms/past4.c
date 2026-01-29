/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include "stepdung.h"  /* this is for the stepping in sheep dung action */
 
#define NUM 2
object *sheep=allocate(NUM);
 
void
make_monster(int i)
{
    if (sheep[i]) {
       sheep[i]->remove_prop(SHEEP_SHEARED); /* can be sheared again */
       return;
     }
    sheep[i]=clone_object(NPC_DIR+"sheep");
    sheep[i]->move(THIS);
    tell_room(THIS, QCTNAME(sheep[i])+" grazes on the pasture.\n");
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
       "You walk along the southern edge of a fenced-in pasture, covered " +
       "in short green grass.  You smell a distinctive odor here, and " +
       "see that it is coming from soft dark patties scattered about the " +
       "field.  The fence borders the pasture to the south and east " +
       "here, allowing you to walk north and west.\n",70));
 
    add_item("grass", break_string(
             "Lush green grass, kept short by grazing sheep, it covers " +
             "the gently rolling pasture.\n",70));
    add_item(({"pasture","field"}), break_string(
             "The pasture is covered with short green grass within " +
             "the fence, and stretches to the west and north.\n",70));
    add_item("fence", break_string(
             "A simple wooden fence, enclosing the field you are standing " +
             "in.  It borders the pasture to the south and east here.\n",70));
    add_item("patties", break_string(
             "Dark mounds scattered around the field, tiny white wisps "+
             "rising from them, giving off a very unpleasant odor.\n",70));
 
    reset_room();
 
    /* exits */
    add_exit(ROOM_DIR+"past3","west",0);
    add_exit(ROOM_DIR+"past7","north",0);
}
