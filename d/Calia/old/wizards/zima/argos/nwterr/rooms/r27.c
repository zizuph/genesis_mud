/* ARGOS - NWTERR - Ouside gates of city
**
** History:
** Date      Coder       Action
** --------- ----------- -----------------------------
** 1/93      Zima        Created
** 9/6/95    Zima        Gates to city opened!
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
#define NUM 2
object *guard=allocate(NUM);
object commander=0;
 
void make_monster(int i) {
    if (guard[i]) return;
    guard[i]=clone_object(NPC_DIR+"gguard");
    guard[i]->equip_me();
    guard[i]->move(THIS);
    tell_room(THIS, QCNAME(guard[i])+" takes his post.\n");
}
 
void reset_room() {
   int i;
   for (i=0; i<NUM; i++) make_monster(i);
   if (commander) return;
   commander=clone_object(NPC_DIR+"tcommder");
   commander->equip_me();
   commander->move(THIS);
   tell_room(THIS, QCNAME(commander)+" salutes his men.\n");
}
 
/* room definition */
void create_room() {
   set_short("Before the gates of a city");
   set_long(
       "You are on a marble road which leads up to the towering gates " +
       "of a city. A wide river rushes by to the south, splitting " +
       "into two forks, one going to the north behind the gate, and the " +
       "other flowing south. The road leads along the river to the "     +
       "northwest into the forest, and through the gates onto the grand "+
       "arch which they guard.\n");
 
    add_item("road",
       "Made of long slabs of white marble, this road seems fairly " +
       "new. It runs along the river to the northwest and ends " +
       "at the city gate.\n");
 
    add_item("river",
       "The river is very wide, and seems deep with its rushing torrents. " +
       "It flows from west to east to this point, where it splits into " +
       "two forks, one flowing north and the other south.\n");
 
    add_item("forest",
        "Stately oaks and maples grow all around along the " +
        "northern side of the road, interspersed with flowering " +
        "dogwoods, splashing pink and white in the shade of the " +
        "forest's canopy.\n");
 
    add_item(({"gate","gates"}),
        "Towering high above you, this arched gate is made of " +
        "gleaming white marble, supported by four immense pillars " +
        "across its face. A crest has been cast in gold at the top " +
        "of the arch, and an inscription has been carved along the " +
        "massive slab of marble supporting it. The gates are open.\n");
 
    add_item("inscription","It is written in large letters above the "+
             "gates. Perhaps you can read it.\n");
    add_cmd_item("inscription","read","It simly reads: METROPOLIS OF ARGOS.\n");
    add_cmd_item(({"on gate","on gates"}), "knock", "@@open_gate");
    add_cmd_item(({"gate","gates"}), ({"knock","open"}), "@@open_gate");
    add_cmd_item(({"gate","gates"}), ({"close","lock"}), "@@close_gate");
 
    add_item("arch",
        "The arch sits atop a thick marble foundation, supported by " +
        "the four pillars.  A crest has been cast in gold on the top.\n");
 
    add_item("crest",
        "The crest is composed of a shield emblazoned with a " +
        "rampant winged horse, the shield surmounted by a " +
        "crown with three jewels on top.\n");
 
    add_item("inscription",
        "Carved along the bottom edge of the arch, just above the " +
        "supportive pillars, this inscription reads: A R G O S.\n");
 
    reset_room();
 
    /* exits */
    add_exit(ROOM_DIR+"r26","northwest",0);
    add_exit(METRO_DIR+"rooms/arch","east",0);
}
 
string open_gate() {
    return "The gates to the city are already open.\n";
}
string close_gate() {
    return "You do not have the authority to do that.\n";
}
