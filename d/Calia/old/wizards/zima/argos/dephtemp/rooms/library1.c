/*
**  Temple of Dephonia, Library front room (Office of the Librarian)
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
 
#define NUM 1
object *priest=allocate(NUM);
 
void
make_monster(int i)
{
    if (priest[i]) return;
    priest[i]=clone_object(NPC_DIR+"libraryn");
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
   set_short("Library of the Temple of Dephonia");
   set_long(break_string(
      "You notice an old musty smell as you walk into the front " +
      "room of the Library of the Temple of Delphonia, which serves " +
      "as the office of the Keeper of the Chronicles, the title given " +
      "to the librarian. An antique mohagany desk and chair sit along " +
      "the northeastern wall of the rectangular room, behind which hangs " +
      "a tapestry of wool. An ornate bookshelf lines the southwestern " +
      "wall, its precious contents kept behind glass doors. A doorway " +
      "leads east back into the hallway, while the stacks of the " +
      "library line the walls to the southeast.\n",70));
 
    add_prop(ROOM_I_INSIDE,1);
 
   add_item("bookshelf", break_string(
      "Crafted of the same dark mohagany as the desk, this ornate " +
      "cabinet with glass doors contains what seems to be some " +
      "very old manuscripts.\n",70));
 
   add_cmd_item("bookshelf",({"open","unlock"}),
      "The bookshelf is locked and can not be opened.\n");
 
   add_item("manuscripts", break_string(
      "They are very ancient-looking manuscripts, kept securely " +
      "inside the bookshelf.\n",70));
 
    add_item("desk", break_string(
      "A long desk fashioned of thick boards of polished mohagany from " +
      "the forest surrounding the temple.  It is ornamented with hemloc " +
      "leaves around the edges and a raven on the front. The person who " +
      "sits here obviously holds an important office in the Order. " +
      "You see a note laying on the desktop.\n",70));
 
    add_item("note", break_string(
       "It is laying on top of the desk and bears the seal of the " +
       "Hierophant of Dephonia. There is writing on it.\n",70));
    add_cmd_item("note","read", break_string(
       "The note reads: We will soon have visitors to the temple. " +
       "Allow them to browse the Chronicles if they wish.\n",70));
 
    add_item("chair", break_string(
       "Like the desk, the accompanying chair is crafted of polished " +
       "mohagany and detailed with hemlock leaves. It is upholstered " +
       "with red silk, embroidered with a raven in silver thread.\n",70));
 
    add_item("tapestry", break_string(
       "Hanging on the northeastern wall, this ancient tapestry is " +
       "made of wool and portrays a group of priests and priestesses " +
       "gathered around an altar, holding hands raised high in a " +
       "circle.\n",70));
 
    add_exit(ROOM_DIR+"library2","southeast",0);
    add_exit(ROOM_DIR+"corr13","east",0);
    reset_room();
}
