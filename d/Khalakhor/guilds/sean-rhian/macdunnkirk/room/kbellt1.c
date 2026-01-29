/* Kirk of Port City - Belltower, lower level
** Player can "pull rope" which rings they bells, heard in several rooms
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 4/1/97      Zima        Created
** 5/28/97     Zima/Khail  Bell toll throughout city/kirk added
*/
/* inherits/includes */
#define  INC_KHALSYS_DEFS
#include "defs.h"
inherit ROOM+"ksanct";
#include <stdproperties.h>
#include <macros.h>
object   monk=0;
 
void reset_room() {
   if (monk) return;
   monk=clone_object(SR_NPC+"knovice");
   monk->equip_me();
   monk->set_wander(ROOM+"k", MASTER_OB(TO), 60);
   monk->move(this_object());
}
 
 
/* room definition */
void create_khalakhor_room() {
   set_short("Belltower of the kirk");
   set_long(
      "   You are at the base of the belltower of the kirk, a large empty "+
      "stone chamber with steps leading up along the west wall. A large "+
      "stained glass window adorns the north wall, while a pointed arch "+
      "marks the entrance to the tower to the east. A rope hangs down "+
      "from a hole in the center of the ceiling, its end curled on the "+
      "floor.\n");
 
   INSIDE;
   add_prop(SR_K1SECURE,1); // secure area
   add_item("window",&windesc(2));
   add_item("kirk",
      "It is a large stone structure, obviously religious in nature.\n");
   add_item(({"tower","belltower","chamber"}),
      "It is a large stone tower rising on the southwest corner of the "+
      "kirk. Steps lead up to its height along the north wall.\n");
   add_item("steps",
      "A set of steep stone steps lead up into the heights of the tower "+
      "along the west wall.\n");
   add_item(({"arch","entrance"}),
      "A wide pointed arch frames the entrance to the tower to the east.\n");
   add_item(({"rope","hole"}),
      "A thick rope hangs down into the center of the chamber from a "+
      "small hole in the ceiling, its slightly frayed end curled on the "+
      "tower floor.\n");
   add_item(({"floor","ceiling","wall"}), "It is made of stone.\n");
   add_item("walls","They are made of stone.\n");
   add_item("plaque","It is bolted into the wall. There is writing on it.\n");
   add_cmd_item("plaque","read",
      "When ye hear the bells' toll, gather ye here for the Rite of the "+
      "Word.\n");
 
   add_exit("kfoyer","east");
   add_exit("kbellt2","up");
   reset_room();
}
 
/*
** filter_kirk - determine if player (ob) is in the kirk
*/
public int filter_kirk(object ob)
{
   return ((environment(ob)) &&
           (wildmatch(ROOM+"*", file_name(environment(ob)))));
}
 
/*
** filter_road - determine if player (ob) is in the streets of the port
*/
public int filter_road(object ob)
{
   return ((environment(ob)) &&
           (wildmatch(MACDUNN_DIR+"room/road*", file_name(environment(ob)))));
}
 
/*
** toll_bell - finds players and sends tolling message
*/
public void toll_bell() {
   object *kplayers = filter(users(), filter_kirk);
   object *rplayers = filter(users(), filter_road);
   if (sizeof(kplayers)>0)
      kplayers->catch_tell("You hear the great bells of the kirk ring out "+
                           "in a clammering toll!\n");
   if (sizeof(rplayers)>0)
      rplayers->catch_tell("You hear the clammering toll of great bells "+
                           "in the distance.\n");
}
 
/*
** pull - allows player to "pull rope" to ring the bells
*/
int pull(string parms) {
   string *parm;
   if (!(stringp(parms)))           { write("Pull what?\n"); return 1; }
   parm=explode(parms," ");
   if (member_array("rope",parm)<0) { write("Pull what?\n"); return 1; }
   write("You pull down on the rope with a heave.\n");
   tell_room(TO,QCTNAME(TP)+" pulls down on the rope with a heave.\n",TP);
   toll_bell(); /* defined in ktoll_list.h */
   return 1;
}
 
/*
** init
*/
public void init() {
   ::init();
   add_action(&pull(),"pull");
}
