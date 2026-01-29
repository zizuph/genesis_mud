/* Street, south entrance to village
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 1/30/97     Zima        Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#define  NUM 2
 
object *guard=allocate(NUM);
 
void make_guard(int i) {
   if (guard[i]) return;
   guard[i]=clone_object(NPC_DIR+"guard");
   guard[i]->equip_me();
   guard[i]->move(THIS);
   tell_room(THIS,QCNAME(guard[i])+" steps out of the tent.\n");
}
 
void reset_room() {
   int i;
   for(i=0; i<NUM; i++) make_guard(i);
}
 
/* room definition */
void create_room() {
   set_short("A cobblestone street near a village");
   set_long(
      "You are walking along a narrow cobblestone street which leads "+
      "north into a small village. To the east there is a large round "+
      "tent, made of blue-striped white canvas, its top rising to a "+
      "conical point. Two banners hang from poles on either side of "+
      "the tent's entrance, moving slightly with the gentle breeze. "+
      "To the southwest you see a cobblestone road which runs along "+
      "the bank of a wide river.\n");
 
#include "csroad.h"
 
   add_item("street",
      "It is a narrow street which winds up the hill to the north, "+
      "leading into a small village. The cobblestone are worn smooth "+
      "with year of rain and being trodden upon.\n");
   add_item("tent",
      "It is a large round tent, its top rising to a sharp point. "+
      "The entrance to the tent is open to the east, flanked by two "+
      "banners hanging from poles.\n");
   add_item(({"banner","banners"}),
      "The two banners are identical, each made of snow white silk "+
      "embroidered with an emblem of a shield over two crossed swords, "+
      "a sun burst of red and gold emblazoned on the shield.\n");
   add_item(({"pole","poles"}),
      "Two poles are set in the ground on either side of the entrance "+
      "of the tent, each bearing a banner.\n");
 
   add_exit("csroad01","southwest",0);
   add_exit("street02", "north",    0);
   add_exit("miltent",  "east",     0);
   reset_room();
}
