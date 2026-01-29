/*
**   ARGOS - Metro - Library - Reading Room
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   3/5/95     Zima       Created
**   5/12/16    Jaacar     Fixed typo
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#define  SITTING "_argos_lib_issitting"
 
void create_room() {
   set_short("Library of Argos");
   set_long(
      "This spacious chamber is the reading room of the library, "+
      "though most locals come here to relax in the utter silence "+
      "and grandeur of the room. A short table sits in the center of "+
      "the room, framed by four couches, all situated on a "+
      "colorful carpet. A relief is sculpted into the northern "+
      "wall, while two busts sit atop pedestals on either side "+
      "of the entrance to the hall to the south.\n");
 
   add_item(({"ceiling","roof"}),
      "Rising high above you, the ceiling is made of enormous squares "+
      "of gray marble which seem coated in glass.\n");
   add_item(({"chamber","walls","floor","room"}),
      "The chamber is constructed of gray marble which seems to be coated "+
      "in glass. A relief is sculpted into the northern wall.\n");
   add_item("entrance","It leads south into the grand hall.\n");
   add_item("table",
      "It is a short table made of polished wood, the centerpiece of the "+
      "room.\n");
   add_item(({"sofa","sofas","couch","couches"}),
      "Four couches are set in a square facing each other around the table, "+
      "each a long marble bench made of white marble, the ends curling "+
      "upward into armrests. They are beautiful but the hard marble "+
      "doesn't look very comfortable.\n");
   add_item("carpet",
      "It is a large square carpet in the center of the room, woven "+
      "with intricate geometric shapes in various shades of blue and "+
      "gray.\n");
   add_item(({"bust","busts","pedestal","pedestals"}),
      "Two busts sit atop pedestals on either side of the entrance. "+
      "One is the bust of a balding, bearded elderly man, a look of "+
      "wisdom in his eyes. An inscription on the bottom of the bust "+
      "reads: Alexis. The second bust is of a regal figure with a "+
      "boyish face wearing a short crown. The inscription reads: "+
      "Biblionus.\n");
   add_item("relief",
      "Sculpted into the northern wall, the relief portrays a crowned "+
      "man sitting on a throne, handing a scroll to a man who "+
      "bows before him with a staff in his hand.\n");
 
   /* room properties */
   add_prop(ROOM_I_INSIDE,1);
 
   add_exit(ROOM_DIR+"libhall1","south","@@go_south");
}
 
int go_south() {
   if (this_player()->query_prop(SITTING)) {
      write("You must rise from the couch before you can walk!\n");
      return 1;
   }
   return 0;
}
 
int sit(string parms) {
   object Tp=this_player();
   object To=this_object();
   if (Tp->query_prop(SITTING)) {
      write("You are already sitting and relaxing on the couch.\n");
      return 1;
   }
 
   write("You sit on one of the comfortable couches and relax.\n");
   tell_room(To,QCTNAME(Tp)+" sits on one of the couches and relaxes.\n",Tp);
   Tp->add_prop(SITTING,1);
   return 1;
}
 
int rise(string parms) {
   object Tp=this_player();
   object To=this_object();
   if (!(Tp->query_prop(SITTING))) return 0;
   write("You get up from the couch feeling relaxed.\n");
   tell_room(To,QCTNAME(Tp)+" gets up from the couch.\n",Tp);
   Tp->remove_prop(SITTING);
   return 1;
}
 
void init() {
   ::init();
   add_action("sit","sit");
   add_action("sit","relax");
   add_action("rise","rise");
}
