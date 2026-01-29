/*
** Temple of Dephonia - Back room of Library
**
** The Alpha and Eta (first and last) tomes of the Vision Quest are
**     found on the altar here.
**
**  History:
**  Coder        Date                       Action
**  ---------- --------  -----------------------------------------------------
**  Zima       1/1/95    Created
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "defs.h"
int alpha_here=1; /* tome is present when loaded */
int eta_here=1;   /* tome is present when loaded */
 
void return_object(int NumObj) {
   switch (NumObj) {
      case 0: alpha_here=1;  break;
      case 1: eta_here=1;    break;
   }
}
 
create_room() {
   set_short("The Library of the Temple of Dephonia");
   set_long(break_string(
      "The musty smell and crowded surroundings of the adjacent " +
      "room of the library give way to this spacious and pristine " +
      "chamber, filled with the sweet scent of perfumed candles. " +
      "A large marble altar rests in the center of the room, covered "+
      "in a snow white cloth with two red candles burning on either " +
      "end. A tapestry adorns the southeastern wall. " +
      "You think this chamber must hold something important.\n",70));
 
    add_prop(ROOM_I_INSIDE,1);
 
    add_item("cloth", break_string(
       "A large white cloth made of fine silk, trimmed with gold " +
       "embroidery, is drapped over the marble altar.\n",70));
 
    add_item("tapestry", break_string(
       "The wool tapestry portrays a priestess dressed in a black "+
       "robe embroidered with a silver raven encircled with twelve "+
       "stars. She wears a golden medallion around her neck and "+
       "holds seven scrolls out in an offeratory manner.\n",70));
 
    add_item(({"candle","candles"}), break_string(
       "Sitting in two tall golden candlesticks on either end of "+
       "the rectangular altar, the candles burn with a calm " +
       "flame, perfuming the room with their odor.\n",70));
 
    add_item("altar","@@exa_altar");
 
    add_item(({"tome","tomes"}), "@@exa_tomes");
    add_item(({"tomes from the altar","tome from the altar",
               "tome from altar","tomes from altar",
               "tomes on the altar","tome on the altar",
               "tomes on altar","tome on altar"}), "@@exa_tomes");
    add_cmd_item(({"tomes from the altar","tome from the altar",
                   "tome from altar","tomes from altar","tome","tomes",
                   "tomes on the altar","tome on the altar",
                   "tomes on altar","tome on altar"}),"read","@@read_tomes");
 
    add_cmd_item(({"tomes on the altar","tomes on altar",
                  "tomes from the altar","tomes from altar"}),
                  ({"take","get"}),"@@take_tomes");
    add_cmd_item(({"tome on the altar","tome on altar",
                  "tome from the altar","tome from altar"}),
                  ({"take","get"}),"@@take_tome");
   add_cmd_item(({"tome","tomes"}), ({"take","get"}), "Take tome from what?\n");
 
    add_exit(ROOM_DIR+"library2","northwest",0);
}
 
string exa_altar() {
   string desc = "It is a long rectangular altar with a pedestal base, " +
                 "made of marble and covered with a white altar cloth. "  +
                 "Two red candles atop golden candlesticks sit on "+
                 "either end of the altar. ";
   if (alpha_here)
      if (eta_here)
         desc = desc + "There are two ancient tomes laying in the altar.\n";
      else
         desc = desc + "There is an ancient tome laying in the altar.\n";
   else
      if (eta_here)
         desc = desc + "There is an ancient tome laying in the altar.\n";
      else
         desc = desc + "\n";
   return desc;
}
 
string exa_tomes() {
   if ((alpha_here) && (eta_here))
      return "There are two ancient tomes laying on top of the altar.\n";
   if ((alpha_here) || (eta_here))
         return "There is an ancient tome laying on top of the altar.\n";
   return "You find no tome.\n";
}
 
string read_tomes() {
   if ((alpha_here)||(eta_here))
       return "You must take the tome from the altar to read it.\n";
    else
       return "You find no tome.\n";
}
 
void move_tome(string tome_name, object TPlay, object TRoom) {
   object tome=clone_object(OBJ_DIR+tome_name);
 
   tome->move(TPlay);
   write("You take the ancient tome from the altar.\n");
   tell_room(TRoom, QCNAME(TPlay)+
             " takes the ancient tome from the altar.\n",TPlay);
   if (tome_name == "tomea")
      alpha_here=0;
   else
      eta_here=0;
}
 
int take_tomes() { /* take both if here */
   object TPlay=this_player();
   object TRoom=environment(TPlay);
 
   if (alpha_here)
      if (eta_here) {
         move_tome("tomea",TPlay,TRoom);
         move_tome("tomeh",TPlay,TRoom);
         }
      else
         move_tome("tomea",TPlay,TRoom);
   else
      if (eta_here)
         move_tome("tomeh",TPlay,TRoom);
      else
         write("You find no tomes.\n");
   return 1;
}
 
int take_tome() { /* take first available tome if any */
   object TPlay=this_player();
   object TRoom=environment(TPlay);
 
   if (alpha_here)
      move_tome("tomea",TPlay,TRoom);
   else
      if (eta_here)
         move_tome("tomeh",TPlay,TRoom);
      else
         write("You find no tome here.\n");
   return 1;
}
