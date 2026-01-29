/*
**  Temple of Dephonia, Dining Hall, north end
**
**  History:
**  Coder        Date                       Action
**  ---------- --------  -----------------------------------------------------
**  Zima       1/10/95    Created
**
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include "vqscenes.h"
#define  SCENE_NUM 6
int      goblet_here=1;
int      bowl_here=1;
 
void reset_room() { bowl_here=1; goblet_here=1;}
 
create_room() {
   set_short("Banquet Hall of the Temple of Dephonia");
   set_long(
      "You are standing at the north end of the grand banquet hall "+
      "of the temple, "+
      "a very long polished antique table extending into the hall "+
      "to the south surrounded by dozens of chairs. The eastern "+
      "wall of this end of the hall is covered by a large mural. "+
      "You can walk along the sides of the hall to the south.\n");
 
   add_prop(ROOM_I_INSIDE,1);
 
   add_item("table","@@exa_table");
   add_item("chairs","Made of the same polished wood as the table, "+
            "the chairs are lined up around the table in perfect "+
            "perspective.\n");
   add_item("mural","Covering the entire wall, the mural is painted "+
            "with somber, pleasing color and portrays a scene of "+
            vq_scene[SCENE_NUM]+". A long narrow plaque hangs on "+
            "it just beneath the ceiling.\n");
   add_item("plaque","It is a long wooden plaque with words carved "+
            "into it. Perhaps you can read them.\n");
   add_item("words","They are carved into the plaque on the wall. "+
                    "perhaps you can read them.\n");
   add_cmd_item(({"plaque","words"}), "read","The plaque reads: "+
                vq_prayer[SCENE_NUM]+".\n");
 
   add_item(({"goblet","goblet from table","goblet on table"}),
              "@@exa_goblet");
   add_cmd_item(({"goblet from table","goblet on table"}), ({"take","get"}),
                  "@@take_goblet");
   add_item(({"bowl","bowl from table","bowl on table"}),
              "@@exa_bowl");
   add_cmd_item(({"bowl from table","bowl on table"}), ({"take","get"}),
                  "@@take_bowl");
   add_cmd_item(({"goblet","bowl"}), ({"get","take"}),
                  "Take what from what?\n");
 
   add_exit(ROOM_DIR+"dine2",  "south", 0);
}
 
string exa_table() {
   string desc="It is a very long table which extends into the "+
               "hall to the north, made of polished mohagany, it looks "+
               "very old but thick and sturdy. ";
 
   if (goblet_here)
      if (bowl_here)
          desc=desc+"There is a goblet and a bowl sitting on the end.\n";
      else
         desc=desc+"There is a goblet sitting on the end.\n";
   else
      if (bowl_here)
         desc=desc+"There is a bowl sitting on the end.\n";
      else
         desc=desc+"\n";
 
   return desc;
}
 
string exa_goblet() {
   if (goblet_here) return "It is a gold goblet, but it is stained with "+
                           "wine, so it doesn't look to have much value.\n";
   else return "You find no goblet.\n";
}
string exa_bowl() {
   if (bowl_here) return "It is a gold bowl, but it is covered with dried "+
                          "food, so it doesn't look to have much value.\n";
   else return "You find no bowl.\n";
}
int take_bowl() {
   object TPlay=this_player();
   object TRoom=environment(TPlay);
 
   if (bowl_here) {
      (clone_object(OBJ_DIR+"dbowl"))->move(TPlay);
      write("You take the dirty gold bowl from the table.\n");
      tell_room(TRoom,QCNAME(TPlay)+" takes a dirty gold bowl from "+
                "the table.\n",TPlay);
      bowl_here=0;
      }
   else write("You find no bowl.\n");
   return 1;
}
int take_goblet() {
   object TPlay=this_player();
   object TRoom=environment(TPlay);
 
   if (goblet_here) {
      (clone_object(OBJ_DIR+"dgoblet"))->move(TPlay);
      write("You take the dirty gold goblet from the table.\n");
      tell_room(TRoom,QCNAME(TPlay)+" takes a dirty gold goblet from "+
                "the table.\n",TPlay);
      goblet_here=0;
      }
   else write("You find no goblet.\n");
   return 1;
}
