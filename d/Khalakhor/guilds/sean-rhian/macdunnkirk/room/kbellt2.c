// Kirk of Port City - Belltower, mid level, and sacristy
//
// History:
// Date        Coder       Action
//----------   ----------- ----------------------------------
// 4/5/97      Zima        Created
// 7/11/98     Zima        Moved sacristy here
//
/* inherits/includes */
#include "defs.h"
inherit  ROOM+"ksanct";
#include <macros.h>
#include <stdproperties.h>
 
object monk;
 
//
// stock - clone objects and put them in the cabinet
//
void stock(object cab, string path, string* item)
{
   int i;
   for (i=0; i<sizeof(item); i++)
      (clone_object(path+item[i]))->move(cab);
}
 
//
// reset_room
//
void reset_room()
{
   if (!objectp(monk))
      {
      monk=clone_object(SR_NPC+"garlon");
      monk->equip_me();
      monk->move(TO);
      tell_room(TO,QCNAME(monk)+" walks up the steps.\n");
      }
}
 
//
// create_khalakhor_room
//
void create_khalakhor_room()
{
   object cab;
   set_short("Belltower and Sacristy of the kirk");
   set_long(
      "   You are standing in the second level of the belltower, a chamber "+
      "which serves as the sacristy of the kirk, a storage room for "+
      "equipment and vestments used by the manachs during their rites. "+
      "A set of steps along the western wall lead down to the base of "+
      "the tower and up to the bell chamber. A long rope hangs down "+
      "through a hole in the ceiling and drops through a hole in the "+
      "floor. A large stained glass window adorns the northern wall.\n");
 
   INSIDE;
   add_prop(SR_K1SECURE,1);
   add_item("kirk",
      "It is a large stone structure, obviously religious in nature.\n");
   add_item(({"tower","belltower","chamber"}),
      "It is a large stone tower rising on the southwest corner of the "+
      "kirk.\n");
   add_item("steps",
      "A set of steep stone steps lead up to the bell chamber and down "+
      "to its base.\n");
   add_item(({"rope","hole"}),
      "A thick rope hangs down from a hole in the center of the ceiling, "+
      "threaded through another small hole in the floor.\n");
   add_cmd_item("rope","pull","You may not pull it from here.\n");
   add_item(({"floor","ceiling","wall"}), "It is made of stone.\n");
   add_item("walls","They are made of stone.\n");
   add_item("window",&windesc(2));
 
   add_exit("kbellt3","up");
   add_exit("kbellt1","down");
 
   // items in this cabinet just for "show", no key available now
   seteuid(getuid());
   cab=clone_object(SR_OBJ+"scabinet");
   cab->set_key(679806052);
   stock(cab,SR_OBJ,   (({"cbwcandle","cbwcandle"})));
   stock(cab,SR_ARMOUR,(({"chasuble","robe","robe","surplice","monshawl"})));
   stock(cab,SR_TOOL,  (({"flask","hwvial"})));
   cab->add_prop(CONT_I_CLOSED,1);
   cab->add_prop(CONT_I_LOCK,1);
   cab->move(TO);
 
   // items in this cabinet needed for quest
   cab=clone_object(SR_OBJ+"scabinet");
   cab->set_key(679806051);
   stock(cab,SR_TOOL,  (({"censor","gplatter","chalice"})));
   cab->add_prop(CONT_I_CLOSED,1);
   cab->add_prop(CONT_I_LOCK,1);
   cab->move(TO);
   reset_room();
}
