/*
**   ARGOS - Metro - Tetartos Road
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   8/14/95    Zima       Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#define NUM 2
object *citizen=allocate(NUM);
 
void make_monster(int i) {
    if (citizen[i]) return;
    citizen[i]=clone_object(NPC_DIR+"citizen");
    citizen[i]->equip_me();
    citizen[i]->move(THIS);
    tell_room(THIS, QCNAME(citizen[i])+" walks down the road.\n");
}
 
void reset_room() {
   int i;
   for (i=0; i<NUM; i++) make_monster(i);
}
 
void create_room() {
   set_short("Tetartos Road");
   set_long(
       "You are walking down Tetartos road between the columns of "+
       "the Amphitheatre on the west and a stand of maples to the "+
       "east. A gentle breeze lilting through the branches of the "+
       "trees is the only sound you hear in this quiet area. Tetartos "+
       "road continues to the north and south.\n");
 
   add_item(({"amphitheatre","Amphitheatre"}),
       "It is an outdoor area where dramatic and comic presentations "+
       "are performed. It framed by a row of high columns. You see "+
       "no entrance into the amphitheatre here.\n");
   add_item("columns",
       "The columns rise high into the air, their capitols sculpted "+
       "with the images of actor's masks. They stand independently "+
       "around the Amphitheatre, paralleling the road to the north.\n");
   add_item(({"maples","stand","trees"}),
       "A stand of tall maples grows on the east side of the road. "+
       "As you look closely, you can see the wall of a temple hidden "+
       "behind them.\n");
   add_item("temple",
       "You can barely see its wall through the maples, a high barrier "+
       "of white marble which seems to curve toward the west. You "+
       "obviously can not approach it from here.\n");
   add_item("road","It runs north and south.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"troad12", "north",0);
   add_exit(ROOM_DIR+"troad14", "south",0);
   reset_room();
}
