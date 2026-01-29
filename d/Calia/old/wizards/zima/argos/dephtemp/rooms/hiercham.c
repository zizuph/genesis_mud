/*
**  Temple of Dephonia, Chamber of the Hierophant
**
**  There is a spec. attack coded in the room for the Hierophant (see below)
**  The robe in the wardrobe is needed for the Vision Quest
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
#include "defs.h"
 
#define MAX_RAVENS 5
object hiero=0;
object *raven=allocate(MAX_RAVENS);
int robe_here=1;
 
void return_object(int ObjNum) { robe_here=1; }
 
void reset_room() {
   if (!hiero) {
      hiero=clone_object(NPC_DIR+"hierphnt");
      hiero->equip_me();
      hiero->move(THIS);
      tell_room(THIS, QCNAME(hiero)+" rises from meditation.\n");
   }
}
 
create_room() {
   set_short("Chamber of the Hierophant of Dephonia");
   set_long(
      "The splendor of this chamber lets you know that you are "+
      "in a very special place within the temple, the chamber "+
      "of the Hierophant, or leader, of the Order. Glimmering "+
      "black marble walls define the triangular chamber, a "+
      "subtle light coming from two lamps burning on the "+
      "wall on either side of the entrance to the north. The "+
      "Hierophant's bed and wardrobe stand along the southwestern "+
      "wall, while there is a small prayer altar facing a tapestry "+
      "which hangs on the southeastern wall. The room is so "+
      "immaculately clean you are afraid to touch anything.\n");
 
   add_item(({"wall","walls","chamber","room"}),
      "Three walls of black marble sparkle in a triangular shape, "+
      "giving the room northern, southwestern and southeastern "+
      "sides.\n");
 
   add_item(({"lamp","lamps","light"}),
      "Two silver oil lamps in the shape of ravens are set into " +
      "the northern wall on either side of the doorway, giving "+
      "a subtle light to the chamber.\n");
 
   add_item("bed",
      "Its frame is made of antique mohagany and it is covered "+
      "neatly with a red blanket.\n");
 
   add_item("blanket",
      "It is a completely smoothe spread without wrinkle covering "+
      "the bed. It is embroidered with a raven surrounded by "+
      "twelve stars.\n");
 
   add_item("wardrobe","@@exa_wardrobe");
 
   add_item(({"robe","robe in wardrobe","robe from wardrobe",
              "robe in the wardrobe","robe from the wardrobe"}),
              "@@exa_robe");
 
   add_cmd_item(({"robe in wardrobe","robe from wardrobe",
              "robe in the wardrobe","robe from the wardrobe"}),
              ({"take","get"}),"@@take_robe");
 
   add_cmd_item("robe",({"take","get"}), "Take robe from what?\n");
 
   add_item("tapestry", break_string(
      "Hanging on the wall in front of the altar, the tapestry "+
      "portrays a priestess dressed in a black robe wearing " +
      "a golden medallion, praying in a dark forest.\n",70));
 
   add_item("altar", break_string(
      "It is a small prayer altar made of the same mohagany "+
      "as the other furnishings. There is a small kneeling "+
      "cushion on the front, and it has a slant top with "+
      "two candles on either side.\n",70));
 
   add_item("cushion","It is a red cushion attatched to the altar.\n");
 
   add_item("top","It is slanted slightly for comfort.\n");
 
   add_item(({"candles","candle"}),
      "Two unlit white candles adorn the small altar.\n");
 
   add_cmd_item(({"candle","candles"}), "light",
      "That wouldn't be proper of you.\n");
 
 
   add_prop(ROOM_I_NO_ATTACK,"@@my_attack");
   add_prop(ROOM_I_INSIDE,1);
 
   add_exit(ROOM_DIR+"sanct","north",0);
   reset_room();
}
 
/* When attacked, the Hierophant casts a spell which creates a  */
/* mist. Attack ravens fly from the mist and attack her enemies */
/* She calls the spell again anytime a "kill X" is executed.    */
/* This spell replaces any dead ravens. The spell is not called */
/* again, of course, if the Hierophant is not here. This special*/
/* attack is coded in the room instead of the NPC since new NPCs*/
/* are created and moved to the room, and since the spell must  */
/* "count" the number of ravens present.                        */
void
make_raven(int i)
{
    if (raven[i]) return;
    raven[i]=clone_object(NPC_DIR+"atkraven");
    raven[i]->move(THIS);
    tell_room(THIS, QCNAME(raven[i])+" flies from the mist!\n");
}
 
int my_attack() {
   int i;
   int NumRavens;
 
   /* no use doing the spell if all the ravens are here, so check first */
   NumRavens=0;
   for (i=0; i<MAX_RAVENS; i++) if (raven[i]) NumRavens++;
 
   /* don't do spell if high priestess isn't here either */
   if (! (hiero)) NumRavens = MAX_RAVENS;
 
 
   if (NumRavens < MAX_RAVENS) {
      hiero->command("emote raises her hands above her head.");
      hiero->command("emote chants: Uperazpizo Emena Matera!");
      tell_room(THIS, "A dark mist fills the chamber.\n");
      for (i=0; i<MAX_RAVENS; i++) make_raven(i);
   }
   return 0;
}
 
string
exa_wardrobe() {
   string desc;
   desc="It is a tall ornate cabinet made of dark mohagany used by "+
        "the Hierophant to store her robes, it is probably an "+
        "antique. ";
   if (robe_here) desc=desc+"You see a long black robe hanging in it.\n";
   else            desc=desc+"\n";
   return desc;
}
string exa_robe() {
   if (robe_here) return "It is hanging in the wardrobe.\n";
   else return "You find no robe here.\n";
}
int take_robe() {
   object robe=0;
   object Thisroom=0;
   if (robe_here) {
       robe=clone_object(ARMOUR_DIR+"visrobe");
      Thisroom=environment(this_player());
      robe->move(this_player());
      if (hiero) {
           this_player()->catch_msg(
                 "First you ask "+QCTNAME(hiero)+" to borrow her robe, "+
               "promising to bring it back.\n");
         tell_room(Thisroom, QCNAME(this_player())+" asks "+
                QTNAME(hiero)+" something.\n",
                this_player());
 
         hiero->command("emote nods her head suspiciously.");
      }
      write("You take the robe from the wardrobe.\n");
      tell_room(Thisroom, QCNAME(this_player())+" takes a robe from "+
                "the wardrobe.\n", this_player());
 
      robe_here=0; /* robe gone now */
      }
   else {
      write("You find no robe here.\n");
      hiero->command("say What are you looking for?");
   }
   return 1;
}
