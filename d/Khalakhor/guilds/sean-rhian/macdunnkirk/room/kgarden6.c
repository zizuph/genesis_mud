/* Kirk of Port City - Abbey garden
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 1/18/98     Zima        Created
**
*/
#include "defs.h"
inherit  ROOM+"kgardbase";
#include <macros.h>
 
object manach=0;
 
void reset_room() {
  ::reset_room();
  if (manach) return;
  manach=clone_object(SR_NPC+"mabon");
  manach->equip_me();
  manach->set_wander(ROOM+"kgard", MASTER_OB(TO), 60);
  manach->move(TO);
  tell_room(TO,QCNAME(manach)+" walks down the path.\n");
}
 
/* room definition */
void create_khalakhor_room() {
   setup_garden_room();
   set_long((query_std_long())+"\n");
 
   add_exit("kgarden8","north");
   add_exit("kgarden5","west");
   reset_room();
}
