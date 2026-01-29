/*
**  Temple of Dephonia, Office of the Master of Novices
**
**
**  History:
**  Coder        Date                       Action
**  ---------- --------  -----------------------------------------------------
**  Zima       1/1/94    Created
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include "vqscenes.h"
 
#define SCENE_NUM 4
#define NUM 1
object *priest=allocate(NUM);
 
void
make_monster(int i)
{
    if (priest[i]) return;
    priest[i]=clone_object(NPC_DIR+"mstrnov");
    priest[i]->equip_me();
    priest[i]->move(THIS);
    tell_room(THIS, QCNAME(priest[i])+" rises from his desk.\n");
}
 
void
reset_room()
{
   int i;
   for (i=0; i<NUM; i++)
      make_monster(i);
}
 
 
create_room() {
   set_short("Chamber in the Temple of Dephonia");
   set_long(break_string(
      "You are standing in a plushly furnished rectangular chamber " +
      "which serves as the office of the Master of Novices. The room " +
      "is dominated by a heavy desk which sits in the center of the "  +
      "chamber, accompanied by a highbacked chair upholstered with red " +
      "silk. An ornately-carved wooden curio sits against the southeastern " +
      "wall, stocked with several scrolls.  A long backless sofa, " +
      "cushioned with red silk, sits in front of the desk, obviously " +
      "used as a 'hot seat' for those novices who are called to audience " +
      "here.  Two identical banners hang on both the northwestern and " +
      "southwestern walls, while a silk-threaded tapestry hangs on the " +
      "northeastern. A doorway leads east out of the chamber.\n",70));
 
    add_prop(ROOM_I_INSIDE,1);
 
    add_item("desk", break_string(
      "A long desk fashioned of thick boards of polished mohagany from " +
      "the forest surrounding the temple.  It is ornamented with hemloc " +
      "leaves around the edges and a raven on the front. The person who " +
      "sits here obviously holds an important office in the Order. " +
      "You see a note laying on the desktop.\n",70));
 
    add_item("note", break_string(
       "It is laying on top of the desk and bears the seal of the " +
       "High Priestess of Dephonia. There is writing on it.\n",70));
    add_cmd_item("note","read", break_string(
       "The note reads: Have the Novices arm themselves in the event " +
       "of an attack. Strangers have been seen in the forest.\n",70));
 
    add_item("chair", break_string(
       "Like the desk, the accompanying chair is crafted of polished " +
       "mohagany and detailed with hemlock leaves. It is upholstered " +
       "with red silk, embroidered with a raven in silver thread.\n",70));
 
    add_item("curio", break_string(
       "Almost reaching the ceiling, the wooden curio sits along the " +
       "southeastern wall. You see several scrolls sitting on its " +
       "shelves.\n",70));
 
    add_item(({"scrolls","scroll"}), break_string(
       "Several scrolls lie rolled and bound with silk cords on the " +
       "shelves of the curio. Each seems to have a seat attached "+
       "with names written on each, probably the names of novices, " +
       "guessing from the position of the one who works here.\n",70));
    add_item(({"scrolls","scroll"}), "read",
       break_string(
       "Each scroll is bound and sealed. You decide it would not be " +
       "a good idea to open them.\n",70));
 
    add_item("sofa", break_string(
       "A marble sofa with ends which curl up into armrests. It sits "+
       "directly in front of the desk, cushioned with red silk, but " +
       "you guess that is little comfort for the unfortunate ones " +
       "who must sit there.\n",70));
    add_item(({"sofa","on sofa"}), "sit", break_string(
       "You would not want to receive that which is bestowed " +
       "upon those who sit there!\n",70));
 
    add_item("tapestry", break_string(
       "Hanging on the northeastern wall, this ancient tapestry is " +
       "threaded with silk to portray "+ vq_scene[SCENE_NUM] + ". "+
       "There is a sash drapped from the top corners " +
       "of the tapestry which bears an inscription.\n",70));
   add_item("sash", break_string(
      "Hanging above the tapestry from its corners, the long red " +
      "silk cloth is embroidered with an inscription.\n",70));
   add_item("inscription",
      "It is threaded into the sash. Perhaps you can read it.\n");
   add_cmd_item("inscription","read",
      "It reads: "+vq_prayer[SCENE_NUM]+".\n");
 
    add_item(({"banner","banners"}), break_string(
       "Two identical banners hang on the back walls, made of red " +
       "silk threaded with the emblem of a raven holding aloft a " +
       "grecian lamp between its wings, the symbol of office of the " +
       "one who sits here.\n",70));
 
    add_item("doorway","It leads out of the chamber to the east.\n");
 
    add_exit(ROOM_DIR+"corr12", "east", 0);
    reset_room();
}
