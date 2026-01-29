/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
#define NUM 2
object *mason=allocate(NUM);
 
void
make_monster(int i)
{
    if (mason[i]) return;
    mason[i]=clone_object(NPC_DIR+"mason");
    mason[i]->equip_me();
    mason[i]->move(THIS);
    tell_room(THIS, QCNAME(mason[i])+" jumps off the cart.\n");
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
   set_short("The end of a marble road");
   set_long(break_string(
       "You come to the end of a marble road which is being constructed " +
       "through the forest.  A cart sits along side the road, loaded " +
       "with slabs of the hard white material used in construction.  " +
       "The forest has been cleared away for the road which leads " +
       "southeast, while a path runs northwest through the forest.\n",70));
 
    add_item("cart", break_string(
       "A small wagon made of wood, with thick solid wheels and handles " +
       "used to pull it along the road.  The wagon is laden with slabs " +
       "of white marble being used in construction.\n",70));
 
    add_item("path", break_string(
       "A simple dirt path, it seems to be intended for the " +
       "continutation of the road.  It leads northwest into the forest.\n",70));
 
    add_item(({"marble","slabs"}), break_string(
       "Long white slabs of marble have been hammered into the dirt path " +
       "to make the road.  Some are loaded into the cart, " +
       "soon to be used.\n",70));
 
    add_item("road", break_string(
       "The road comes to a craggy end here, marble slabs recently placed " +
       "along the path.  The road leads southeast through the forest.\n",70));
 
    add_item("forest", break_string(
        "A mixture of maples, oaks and evergreens, the forest " +
        "grows densly on either side of the road, keeping you " +
        "on your path.\n",70));
 
    reset_room();
 
    /* exits */
    add_exit(ROOM_DIR+"r3","northwest",0);
    add_exit(ROOM_DIR+"r5","southeast",0);
}
