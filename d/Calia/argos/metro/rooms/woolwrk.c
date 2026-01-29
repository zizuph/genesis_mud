/*
**   ARGOS - Metro - Wool Works
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   8/25/95    Zima       Created
**
**   For a fee of 12cc, the seamstress will spin a bale of wool
**      (objects/wool_bale), obtained by shearing a sheep (see
**      objects/sheep_shears), into a large spool of yarn.
**   For a given price, the seamstress will knit a spool of yarn into
**      various pieces of clothing.
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include "defs.h"
#include "woolwrk.h"
 
object seamstress;
int    busy=0;
string IdleLong;
string BusyLong;
 
void reset_room() {
   if (seamstress) return;
   busy=0;
   seamstress=clone_object(NPC_DIR+"seamstress");
   seamstress->equip_me();
   seamstress->move(THIS);
   IdleLong=(seamstress->query_long());
   BusyLong=IdleLong+"She is busy working at the moment.\n";
   tell_room(THIS,QCNAME(seamstress)+" opens her shop for business.\n");
}
 
/* room definition */
void create_room() {
   set_short("The woolworks shop");
   set_long(
       "Large spools of yarn and stacks of woven material of "+
       "many colors sit around on the shelves of this shop, the "+
       "woolworks of Argos where seamstresses perform their delicate "+
       "artwork. A spinning wheel sits in one corner, while "+
       "a loom sits in another. A simple wooden chair and table "+
       "serve the seamstresses who work here. There is a quaint "+
       "plaque next to the doorway to the north.\n");
 
   add_item(({"building","shop","woolworks"}),
      "It is a quaint shop, kept very clean, where wool is spun "+
      "into yarn which is in turn made into clothing.\n");
   add_item(({"spools","yarn"}),
      "Large spools of yarn sit on some of the shelves, dyed with "+
      "various colors.\n");
   add_item(({"stacks","material"}),
      "Stacks of newly woven material sit on some of the shelves, "+
      "ready to be made into clothing and other woolen items.\n");
   add_item("spinning wheel",
      "It is a wooden contraption made of a frame of long carved "+
      "poles with a large wheel with eight spokes. The seamstresses "+
      "use it to spin bales of wool into spools of yarn.\n");
   add_item("loom",
      "It is a large wooden contraption made of squares of frames, "+
      "a set of many strings threaded through it in perfect parallel. "+
      "The seamstresses use it to weave yarn into cloth.\n");
   add_item("chair",
      "It is just a simple chair where the seamstresses sit and work.\n");
   add_item("table",
      "It is a simple wooden table which holds the smaller tools used "+
      "by the seamstresses. You see some knitting needles on top of it.\n");
   add_item("needles",
      "They are slender long sticks with sharp points used to knit "+
      "yarn into cloth.\n");
   add_item("plaque",
      "Stretched into a wooden frame, the plaque is a piece of white "+
      "cloth with some words embroidered into it.\n");
   add_cmd_item(({"plaque","words"}),"read",
      "+--------------------------------+\n"+
      "| Services Provided:             |\n"+
      "|  - Spin wool into yarn..."+YARN_FEE+"cc  |\n"+
      "|  - Weave yarn into:            |\n"+
      "|    A tunic..............."+TUNIC_FEE+"cc  |\n"+
      "|    A cloak..............."+CLOAK_FEE+"cc  |\n"+
      "|                                |\n"+
      "| Ask seamstress for service     |\n"+
      "+--------------------------------+\n");
 
   /* exits */
   add_exit(ROOM_DIR+"lroad15","north",0);
   add_exit(ROOM_DIR+"troad8", "east",0);
   reset_room();
}
 
/* remaining functions in extension file */
#include "woolwrk.ext"
#include "woolwrk.ex1"
 
void init() {
   ::init();
   add_action("ask","ask");
}
