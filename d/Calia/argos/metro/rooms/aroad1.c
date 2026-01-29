/*
**   ARGOS - Metro - Alpharon road (West End)
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   11/12/95   Zima       Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#define NUM 3
object *guard=allocate(NUM);
 
void make_monster(int i) {
    if (guard[i]) return;
    guard[i]=clone_object(NPC_DIR+"strguard");
    guard[i]->equip_me();
    guard[i]->move(THIS);
    tell_room(THIS, QCNAME(guard[i])+" takes his post.\n");
}
 
void reset_room() {
   int i;
   for (i=0; i<NUM; i++) make_monster(i);
}
 
 
void create_room() {
   set_short("Alpharon Road");
   set_long(
       "A small guard house sits just to the south, where the sentinels "+
       "who protect this back entrance to the city are headquartered. "+
       "The walls of a massive temple rise to the north, following along "+
       "Alpharon Road which leads east into the city. An arched bridge "+
       "spans the torrential river which surrounds the city to the west.\n");
 
   add_item(({"road","roads","street","streets"}),
       "Alpharon road runs east along a large temple into the city.\n");
   add_item("temple",
      "It is a massive structure of white marble, its high walls buttressed "+
      "by tall pillars.\n");
   add_item("pillars",
       "They buttress the wall of the temple, topped with capitols "+
       "ringed with sculpted perched falcons.\n");
   add_item(({"house","guard house","headquarters"}),
       "It is a small but official looking marble structure with a "+
       "canonical roof which makes it look somewhat like a tent. A "+
       "blue banner hangs above its entrance.\n");
   add_item("banner",
       "It is a banner made of blue silk bearing the royal arms of Argos, "+
       "a shield emblazoned with a rampant winged horse surmounted by a "+
       "crown of three jewels.\n");
   add_item("bridge",
      "It is a sturdy oak bridge which spans the river to the west.\n");
   add_item("river",
      "It is a deep and rushing river which flows from the north to "+
      "the south here, eventually surrounding the entire city.\n");
 
   reset_room();
   /* exits */
   add_exit(SWTERR_DIR+"rooms/sbridge",   "west",0);
   add_exit(ROOM_DIR+"aroad2",            "east",0);
   add_exit(ROOM_DIR+"swghouse",          "south",0);
}
