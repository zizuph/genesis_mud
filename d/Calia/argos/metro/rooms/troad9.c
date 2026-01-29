/*
**   ARGOS - Metro - Tetartos Road
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   8/14/95    Zima       Created
**
**   The building to the west is a "closed"/"empty" commercial building,
**   which has been taken over by a group of Kretans as a secret hiding
**   place. The entrance is boarded up, not allowing access,
**   but a player can 'kick boards' until the boards are broken, at
**   which time an exit is added to the room.
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "defs.h"
 
/* current "strength" of the boards over the entrance */
#define MaxBoardStr 300
int BoardStr=MaxBoardStr;
 
void reset_room() {
   BoardStr=MaxBoardStr;
   if (member_array("west",(query_exit())) > -1)
      remove_exit("west");
}
 
void create_room() {
   set_short("Tetartos Road");
   set_long(
       "A dense stand of maple trees shade this part of Tetartos road "+
       "as you make your way along the city's east side. To the west "+
       "is one of the buildings of the commercial district, the boards "+
       "over its entrance suggesting it is empty. Tetartos road continues "+
       "to the north and south.\n");
 
   add_item(({"maples","stand","trees"}),
       "A stand of tall maples grows on the east side of the road. "+
       "As you look closely, you can see the wall of a temple hidden "+
       "behind them.\n");
   add_item("road","It runs north and south.\n");
   add_item("building",
       "It is one of the single level, flat-roofed buildings of the "+
       "commercial district. There are boards over its entrance, "+
       "making you think it must be empty.\n");
   add_item(({"boards","entrance"}),"@@exa_boards");
   add_item(({"buildings","district","commercial district"}),
       "The buildings of the commercial district are cubic marble "+
       "structures which line the roads. The district stretches "+
       "out to the west, Tetartos road bordering it on the east.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"troad8", "north",0);
   add_exit(ROOM_DIR+"troad10","south",0);
   set_alarm(1.0,0.0,"reset_room");
}
 
string exa_boards() {
   if (BoardStr) return (
      "The entrance of the building to the west is blocked by boards "+
      "which have "+
      "been nailed over it. You wonder if you could kick them in.\n");
   else return (
      "The entrance of the building to the west has some broken boards "+
      "nailed over the doorway, but you can go through.\n");
}
 
int kick(string Parms) {
   /* allows player to "kick" the boards over the entrance to the      */
   /* building. Each kick reduces the board strength by the player's   */
   /* strength stat. When Board strength reaches 0, can enter building */
   object Tp=this_player();
   object Tr=this_object();
   int    TpStr;
   string *Parm;
 
   /* check parameters passed for "board" or "boards" */
   if (!(Parms)) return 0;
   Parm=explode(Parms," ");
   if (!((member_array("board",Parm)>-1)||(member_array("boards",Parm)>-1)))
      return 0;
 
   /* if boards kicked in, let player know */
   if (BoardStr==0) {
      write("The boards have already been kicked in.\n");
      return 1;
   }
 
   write("You kick the boards over the entrance to the building hard.\n");
   tell_room(Tr,QCTNAME(Tp)+" kicks the boards over the entrance to the "+
                         "building hard.\n",Tp);
 
   TpStr=Tp->query_stat(SS_STR);
   BoardStr=BoardStr-TpStr;
   if (BoardStr<=0) {
      BoardStr=0; /* set to 0 if went under */
      tell_room(Tr,"The boards crash through with a loud crack!\n");
      if (member_array("west",(query_exit())) == -1) 
         add_exit(ROOM_DIR+"empty","west",0);
   }
   return 1;
}
 
void init() {
   ::init();
   add_action("kick","kick");
}
