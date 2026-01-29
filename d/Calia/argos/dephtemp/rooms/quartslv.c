/*
**  Temple of Dephonia, Servant's  quarters
**
**  History:
**  Coder        Date                       Action
**  ---------- --------  -----------------------------------------------------
**  Zima       1/10/95    Created
**  ?          1997/01/26  Previous edit
**  Lavellan   2010/09/01  Typo
**
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
#define NUM 4
object *servant=allocate(NUM);
 
void
make_monster(int i)
{
    if (servant[i]) return;
    servant[i]=clone_object(NPC_DIR+"aservant");
    servant[i]->equip_me();
    servant[i]->move(THIS);
    tell_room(THIS, QCNAME(servant[i])+" trudges into the room.\n");
}
 
void
reset_room()
{
   int i;
   for (i=0; i<NUM; i++) make_monster(i);
}
 
create_room() {
   set_short("Servants Quarters in the Temple of Dephonia");
   set_long(
      "This small chamber is modestly furnished but neatly kept, and "+
      "it seems somewhat different from other chambers in the temple. "+
      "A few beds sit along the northern and western "+
      "wall, while an old wardrobe sits next to the doorway to the "+
      "west. A small tapestry has been hung on the rounded southeastern "+
      "wall.\n");
 
   add_prop(ROOM_I_INSIDE,1);
 
   add_item(({"chamber","wall","walls"}),
            "The chamber is a bit smaller than most you "+
            "have seen in the temple. It is square, except the "+
            "southwestern corner of the room has been clipped by the "+
            "circular corridor just outside.\n");
   add_item("beds","They are made of oak and are constructed of simple "+
            "patterns. Not your ancestors' antiques.\n");
 
   add_item("wardrobe","It is an old oak wardrobe which probably holds "+
            "the clothes and other personal items of those who live "+
            "here.\n");
   add_cmd_item("wardrobe",({"open","unlock"}), "The wardrobe is locked "+
            "and can not be opened.\n");
   add_item("tapestry","It is a small tapestry woven of coarse wool. It "+
            "is threaded to portray a large city of columned white "+
            "marble temples nestled in a valley.\n");
 
 
   add_exit(ROOM_DIR+"corr24","west", 0);
   reset_room();
}
