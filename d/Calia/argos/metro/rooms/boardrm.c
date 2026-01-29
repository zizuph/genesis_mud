/*
**   ARGOS - Metro - Board Room in the Visitors Center
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   3/5/95     Zima       Created
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include "defs.h"
 
void load_board();
 
void create_room() {
   set_short("Visitors Center");
   set_long(
      "This is the back room of the Visitors Center, bare of furniture " +
      "but neat and clean. A portrait hangs on the west wall, while "+
      "some notices are posted on the east.\n");
   add_item("portrait",
      "It is the portrait of Cosmopolitus the King of Argos, a handsome "+
      "dark-haired figure garbed in his royal ceremonial vestments.\n");
   add_item("notices",
      "They are official documents posted on the wall. You should read "+
      "them.\n");
   add_cmd_item("notices","read","@@notices");
 
   /* room properties */
   add_prop(ROOM_I_INSIDE,1);
   add_prop(ROOM_M_NO_ATTACK,1);
   add_prop(ROOM_I_NO_STEAL, 1);
   add_prop(ROOM_I_NO_TELEPORT, 1);
   add_prop(ROOM_I_NO_ATTACK, 1);
 
   add_exit(ROOM_DIR+"visitctr","north",0);
   load_board();
}
 
void load_board() {
    object bb;
    seteuid(getuid(this_object()));
    bb = clone_object(ROOM_DIR+"boardrm/board");
    bb->move(this_object());
}
 
void enter_inv(object ob, object from) {
    /* don't allow NPCs in here */
    ::enter_inv(ob, from);
 
    if (living(ob) && !interactive(ob))
        ob->move(from);
}
 
int notices() {
   write("There is one notice:\n"+
         "Some of the local establishments may not yet be open for business. "+
         "Please be patient as our wary businessmen get used to the idea of "+
         "strangers in our midst.\n");
   return 1;
}
