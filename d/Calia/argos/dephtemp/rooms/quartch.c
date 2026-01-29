/*
**  Temple of Dephonia, Children's quarters
**
**  History:
**  Coder        Date                       Action
**  ---------- --------  -----------------------------------------------------
**  Zima       1/10/95    Created
**
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include "vqscenes.h"
 
#define SCENE_NUM 1
#define NUM 4
object *child=allocate(NUM);
 
void
make_monster(int i)
{
    if (child[i]) return;
    child[i]=clone_object(NPC_DIR+"child");
    child[i]->equip_me();
    child[i]->move(THIS);
    tell_room(THIS, QCNAME(child[i])+" romps into the room.\n");
}
 
void
reset_room()
{
   int i;
   for (i=0; i<NUM; i++) make_monster(i);
}
 
create_room() {
   set_short("Childrens Quarters in the Temple of Dephonia");
   set_long(
      "This small chamber has brightly colored walls giving it an "+
      "unusually cheery atmosphere. Small beds sit along the northern "+
      "wall, while toys are scattered across the floor. There is a chest "+
      "sitting at the foot of one of the beds. A small painting hangs "+
      "next to the doorway to the east.\n");
 
   add_prop(ROOM_I_INSIDE,1);
 
   add_item("walls","They are painted in yellow and red colors, an "+
            "unusual sight in this shrine of black marble.\n");
   add_item("chamber","The chamber is a bit smaller than most you "+
            "have seen in the temple. It is square, except the "+
            "southeastern corner of the room has been clipped by the "+
            "circular corridor just outside.\n");
   add_item("beds","They are made of dark pine and are short and close "+
            "to the ground, obviously for smaller children.\n");
   add_item("chest","It is a heavy chest made of mohagany. You guess "+
            "it contains either a wealth of toys or clothing for "+
            "the children.\n");
   add_cmd_item("chest",({"open","unlock"}), "The chest is locked and "+
            "can not be opened.\n");
   add_item("toys","Dolls, toy swords, and other toys are scattered "+
            "across the floor.\n");
   add_item("painting","It is a small painting of "+vq_scene[SCENE_NUM] +
            ". It is framed with a rectangular frame of dark pine.\n");
   add_item("frame","It frames the painting on the wall. There are "+
            "some words carved into it on the lower edge.\n");
   add_item("words","They are carved on the frame of the picture on "+
            "the wall. Perhaps you can read them.\n");
   add_cmd_item("words","read","They read: "+vq_prayer[SCENE_NUM]+".\n");
 
 
   add_exit(ROOM_DIR+"corr24","east", 0);
   reset_room();
}
