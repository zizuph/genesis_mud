/*
**  Temple of Dephonia, Novice Priestess chamber
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
 
#define SCENE_NUM 11
#define NUM 4
object *priestess=allocate(NUM);
 
void
make_monster(int i)
{
    if (priestess[i]) return;
    priestess[i]=clone_object(NPC_DIR+"novprsts");
    priestess[i]->equip_me();
    priestess[i]->move(THIS);
    tell_room(THIS, QCNAME(priestess[i])+" walks into the room.\n");
}
 
void
reset_room()
{
   int i;
   for (i=0; i<NUM; i++) make_monster(i);
}
 
create_room() {
   set_short("Novice Priestess Chambers in the Temple of Dephonia");
   set_long(
      "You are standing in a square chamber where the novice priestesses "+
      "of the Order live. There is a line of beds along the eastern "+
      "wall, while two chests sit on either side of the doorway to "+
      "the west. A full-length mirror in a dark wood frame sits in the "+
      "southwestern corner of the chamber, while a mural is painted "+
      "on the northern wall.\n");
 
   add_prop(ROOM_I_INSIDE,1);
 
   add_item("beds","They are made of dark pine and are set in a row "+
            "along the eastern wall.\n");
   add_item(({"chest","chests"}),"There are two heavy chest made of "+
            "mohagany sitting on either side of the doorway. "+
            "You suppose it holds clothing and other items of the young "+
            "women who live here.\n");
   add_cmd_item(({"chest","chests"}),({"open","unlock"}),
            "The chests are locked and can not be opened.\n");
   add_item("mural","Covering the entire northern wall, the mural "+
            "is painted in vibrant colors depicting "+vq_scene[SCENE_NUM]+
            ". There are some words written on the border of the "+
            "wall next to the ceiling.\n");
   add_item("words","They are sculpted into the marble on the "+
            "border above the northern wall. Perhaps you can read them.\n");
   add_cmd_item("words","read","They read: "+vq_prayer[SCENE_NUM]+".\n");
   add_item("mirror", "It is a full-length mirror setting in the "+
            "corner. You wonder why it would be here.\n");
 
   add_exit(ROOM_DIR+"corr27","west", 0);
   reset_room();
}
