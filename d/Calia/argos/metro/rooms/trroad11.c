/*
**   ARGOS - Metro - Chiphas and Tritos Roads
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   8/12/95    Zima       Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
#define NUM 2
object *guard=allocate(NUM);
 
void make_monster(int i) {
    if (guard[i]) return;
    guard[i]=clone_object(NPC_DIR+"strguard");
    guard[i]->equip_me();
    guard[i]->move(THIS);
    tell_room(THIS,QCNAME(guard[i])+" takes his post.\n");
}
 
void reset_room() {
   int i;
   for (i=0; i<NUM; i++) make_monster(i);
}
 
void create_room() {
   set_short("Tritos and Chiphas Roads");
   set_long(
       "You are standing at the intersection of Tritos and Chiphas "+
       "roads in the heart of Argos. You can see several of the "+
       "city's major attractions here, including the Aeropagus in the "+
       "northwestern corner of the intersection, the park framed with "+
       "its well-trimmed hedge to the southwest, the Amphitheatre "+
       "to the southeast, and an ornate building in the northeastern "+
       "corner. Chiphas road leads east and west while Tritos "+
       "runs north and south.\n");
 
   add_item("building",
       "Pillars are set into the wall of the building, their capitols "+
       "supporting a shallow angled roof on top. It looks more ornate "+
       "than most of the commercial district, so you guess it must be "+
       "some kind of government building. You see no entrance to it "+
       "here.\n");
   add_item(({"aeropagus","Aeropagus"}),
       "The Aeropagus is an open-air convocation center of the city. "+
       "It is lined with a set of pillars on its sides. You see no "+
       "entrance through the pillars here.\n");
   add_item(({"pillar","pillars"}),
       "Tall columns of marble with ornate capitols, they stand "+
       "independently around the Aeropagus like a wall of marble "+
       "trees spaced perfectly apart.\n");
   add_item("park",
       "It is surrounded with a well-trimmed hedge. There is an "+
       "entrance through the hedge to the southwest.\n");
   add_item("hedge",
       "Composed of long rows of evergreen bushes, the hedge has "+
       "been trimmed into a rectangular shape, making a wall around "+
       "the park.\n");
   add_item(({"Amphitheatre","amphitheatre"}),
       "The Ampthitheatre of Argos sits in the southeastern corner "+
       "of the intersection. It is an open-air place where citizens "+
       "and visitors alike gather to see dramatic and comic productions. "+
       "It is faced with a line of very tall "+
       "columns which stand in a quarter-circle from its northeastern "+
       "to its southwestern corner. The entrance to the Amphitheater "+
       "is to the southeast at the center of the curving line of "+
       "columns.\n");
   add_item(({"column","columns"}),
       "Standing in a curving line, the columns reach high into the "+
       "sky and form the facade of the Amphitheatre, curving from "+
       "its northeastern to its southwestern corners. Each column "+
       "is topped with a capitol sculpted with happy and sad-faced "+
       "actors' masks.\n");
 
 
   /* exits */
   add_exit(ROOM_DIR+"trroad10","north",0);
   add_exit(ROOM_DIR+"trroad12","south",0);
   add_exit(ROOM_DIR+"croad14", "east",0);
   add_exit(ROOM_DIR+"croad12", "west",0);
   add_exit(ROOM_DIR+"park4",   "southwest",0);
   add_exit(ROOM_DIR+"amph1",   "southeast",0);
   reset_room();
}
