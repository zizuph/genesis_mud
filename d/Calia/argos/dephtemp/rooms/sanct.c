/*
**  Temple of Dephonia - Central Sanctuary of the Temple
**
** This is where the final "rites" of the vision quest occur, and where
**     the quest points are given.
**     At the end of the quest, the player should have the following
**     objects: wearing robe, wearing medallion, have bowl, have corpse
**     lamb. Should also have the invisible blessing object.
**     The player then fills the bowl with blood from the corpse,
**     drinks the blood, places the corpse on the altar, shouts praise
**     to Dephonia, and receives his reward
**
**  History:
**  Coder        Date                       Action
**  ---------- --------  -----------------------------------------------------
**  Zima       1/5/95    Created
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include "defs.h"
 
#define DEPH_DOM "Calia"
#define DEPH_GROUP 2
#define DEPH_BIT 0
#define DEPH_XP 15000
#define DEPH_ALIGN_ADJUST -200
 
int corpse_on_altar=0;
 
/* get extensions of this file */
#include "sanct.ex1"
#include "sanct.ex2"
 
create_room() {
  set_short("The Sanctum of the Temple of Dephonia");
  set_long(
     "You enter the inner sanctum of the Temple "+
     "of Dephonia, the consecrated place which is the center of "+
     "worship for the followers of the cult of the Light of Darkness. "+
     "The chamber is a large circular tower which reaches high above "+
     "the temple, eight massive arches converging in the center of " +
     "a dome which caps the top. In the center of the chamber is "+
     "a large round altar of white marble, obviously the focal point "+
     "of the sanctuary. Wide doorways lead into the sanctum's "+
     "anterooms to the west and east, while smaller arched entrances "+
     "lead to the north and south. You feel a strong presence of darkness "+
     "here like nowhere else in the temple.\n");
 
  add_item(({"chamber","sanctum","sanctuary","tower"}),
     "It is a circular tower in the center of the temple, its walls "+
     "made of glassy black marble and buttressed by eight massive "+
     "arches.\n");
  add_item(({"arch","arches"}),
     "The eight arches are placed evenly along the outer circle of "+
     "the chamber, their massive bases buttressing the round "+
     "walls, thining and converging to a point in the dome high "+
     "above you.\n");
  add_item("dome",
     "The dome rises high above the top of the temple, a mosaic "+
     "of darkened crystal, the tips of the arches thinning and "+
     "meeting in the center of the dome.\n");
  add_item(({"doorway","doorways"}),
     "Wide doorways, large enough for three abreast and two high, "+
     "open on the east and west sides of the sanctum, leading " +
     "into anterooms on either side.\n");
  add_item(({"entrance","entrances"}),
     "There are two entrances to adjacent chambers to the north "+
     "and south.\n");
  add_item(({"corpse","lamb","body"}),"@@exa_corpse");
  add_item("altar","@@exa_altar");
 
  add_prop(ROOM_I_INSIDE,1);
  add_exit(ROOM_DIR+"sacris",  "north",0);
  add_exit(ROOM_DIR+"hiercham","south",0);
  add_exit(ROOM_DIR+"anterme", "east",0);
  add_exit(ROOM_DIR+"antermw", "west",0);
   reset_room();
}
 
string exa_altar() {
   if (corpse_on_altar)
      return
      "It is a circular column of white marble, in stark contrast to "+
      "the black stone of the rest of the temple. The body of a "+
      "slaughtered lamb, its throat slit gushing streams of blood "+
      "over the sides of the altar, rests limply on top.\n";
   else
      return
      "It is a circular column of white marble, in stark contrast to "+
      "the black stone of the rest of the temple. The top of the "+
      "altar looks as if it has been charred, and what looks like "+
      "streams of dried blood run down the sides, a grotesque sight.\n";
}
 
void init() {
   ::init();
   add_action("fill","fill");
   add_action("drink","drink");
   add_action("place","place");
   add_action("chant","chant");
   add_action("take","take");
   add_action("take","get");
}
 
string exa_corpse() {
   if (corpse_on_altar)
      return "It is laying on the altar.\n";
   else
      return "Examine what?\n";
}
 
int CorrectTakeParm (string ParmStr) {
   /* if word is lamb or corpse, returns 1, 0 otherwise */
   string *Parm;
   int    OK=0;
   int    i;
 
   if (!(ParmStr)) return 0;  /* no parameters passed */
   Parm=explode(ParmStr," ");
 
   for (i=0;  i<sizeof(Parm); i++)
      if ((Parm[i]=="lamb")||(Parm[i]=="corpse"))
         OK=1;
   return OK;
}
 
int take(string ParmStr) {
   /* this allows the player to take/get the corpse from the altar */
   object TPlay=this_player();
   object TRoom=this_object();
   int    WearsRobe = ((TPlay->query_armour(A_BODY))->id(VDQ_ROBE));
   int    WearsMedal= ((TPlay->query_armour(A_NECK))->id(VDQ_MEDAL));
 
   if (corpse_on_altar) {
      if (CorrectTakeParm(ParmStr))
         if ((WearsRobe)&&(WearsMedal)) {
            write("You take the corpse of the lamb from the altar.\n");
            tell_room(TRoom,QCNAME(TPlay)+" take the corpse of the lamb "+
                      "from the altar.\n",TPlay);
            (clone_object(OBJ_DIR+"lambbody"))->move(TPlay);
            corpse_on_altar=0;
            return 1;
            }
         else {
            write("You try to take the corpse of the lamb from the altar "+
                  "but it burns your hands!\n");
            tell_room(TRoom,QCNAME(TPlay)+" tries to take the corpse of "+
                      "the lamb from the altar but jumps back in pain!\n",
                      TPlay);
            return 1;
         }
      else
         return 0; /* might be taking something else */
   }
   return 0;   /* ignore command if corpse isn't on altar */
}
 
void leave_inv(object Leaving, object To) {
   /* don't let player out of room with the invisible drank object */
   object DrankObj=present(VDQ_DRANK_OBJ,Leaving);
 
   ::leave_inv(Leaving,To);
   if ((DrankObj)&&(!(To==this_object()))) {
      DrankObj->remove_object();
      set_this_player(Leaving);
      write("Your ecstatic feeling fades as you walk away from the "+
            "sanctum.\n");
   }
}
