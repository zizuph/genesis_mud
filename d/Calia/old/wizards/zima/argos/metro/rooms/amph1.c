/*
**   ARGOS - Metro - Amphitheatre Entrance
**   Statue of Thespia is here for Toe Quest
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   1/30/95    Zima       Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include "toequest.c"
 
void create_room() {
   set_short("Amphitheatre of Argos");
   set_long(
       "You are standing at the entrance of the Amphitheatre of Argos, "+
       "an outdoor area in the shape of a quarter circle walled by "+
       "high columns. The stage is located in the southeastern corner "+
       "of the area, inaccessible from the seating areas which lie "+
       "to the east and south. A statue of a majestic woman stands "+
       "atop a large pedestal here at the entrance, in the center of "+
       "the curved wall of columns around the northwestern side. A path "+
       "leads to the northwest out of the Amphitheatre.\n");
 
   add_item("stage",
       "It is a quarter-circular stage made of marble fitting "+
       "perfectly in the southeastern corner of the Amphitheatre "+
       "of the same shape. You can't get to it from here, as it "+
       "rises above the ground which slopes down from here to the "+
       "base of the stage.\n");
   add_item(({"seats","seating area"}),
       "Nothing more than the gentle slope of the ground, the "+
       "seating area is really anywhere one would want to sit. "+
       "It extends to the south and east.\n");
   add_item("ground",
       "It is a grassy area which slopes down toward the stage "+
       "to the southeast, obviously hollowed out so that a good "+
       "view of the stage can be had anywhere within the columns.\n");
   add_item("entrance",
       "It is simply a break in the center of the curved line of "+
       "columns which wrap around the northwestern side of the "+
       "Amphitheatre. A path leads through it to the northwest.\n");
   add_item(({"Amphitheatre","amphitheatre","area"}),
       "It is a grassy outdoor area, sloping toward the southeast, "+
       "where dramatic and comic "+
       "theatrical presentations are made. It is in the shape of "+
       "a quarter circle, walled by a straight line of columns on "+
       "the south and east, and a curved line on the northwest. "+
       "The stage area is in the southeastern corner, high enough "+
       "above the crater-like area to be inaccessible from here.\n");
   add_item("columns",
       "The columns are set at regular intervals around the Amphitheatre, "+
       "rising high into the air, their capitols sculpted with masks "+
       "commonly worn by actors.\n");
   add_item("statue",
       "It is the statue of a beautiful young woman in a long robe, "+
       "wearing a crown on her head and an actor's mask in one hand. "+
       "She holds her other arm out toward the entrance in a welcoming "+
       "manner.\n");
   add_item("pedestal",
       "It is an ornately sculpted block of marble on top of "+
       "which the statue stands. An inscription is written "+
       "across the face of the pedestal.\n");
   add_item("inscription",
       "It is written on the pedestal. Perhaps you can read it.\n");
   add_cmd_item("inscription","read",
       "It reads: THESPIA : SEVENTH MONARCH OF ARGOS : 189-222 AT.\n");
   add_item(({"toe","toe of statue","toe on statue"}),
       "The toe of the queen looks highly polished compared to "+
       "the rest of the statue.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"trroad11","northwest",0);
   add_exit(ROOM_DIR+"amph3",   "east",0);
   add_exit(ROOM_DIR+"amph2",   "south",0);
   toe_quest_set_statue_prop(TOE_QUEST_THESPIA);
}
