/*
**  Temple of Dephonia - Temple Armoury and Forge
**
**  There is a hammer and a sword laying on the anvil (@ each reset)
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
int hammer_here=1; /* hammer and sword here when loaded */
int sword_here=1;
 
void
reset_room() {
   hammer_here=1; /* hammer and sword here at each reset */
   sword_here=1;
}
 
create_room() {
   set_short("The Armoury of the Temple of Dephonia");
   set_long(
      "The thick smell of soot almost overtakes you, the sticky " +
      "black dust covering the walls of this rectangular chamber " +
      "which runs from the northeast to the southwest. This room " +
      "obviously serves as a forge and armoury, as there is a large "+
      "iron pot of coal and an anvil in the center of the room, while "+
      "boxes of what are probably weapons and armour are stacked " +
      "all around.\n");
 
   add_item(({"soot","walls"}),
      "The walls are covered in the smelly soot, almost choking your "+
      "every breath.\n");
 
   add_item(({"pot","coal"}),
      "The iron pot of coal is usually heated with a fire so that "+
      "metal can be put in the coals to make it malleable enough "+
      "to shape and sharpen. There is no fire beneath the pot and "+
      "the coals are cold, so you guess it's been a little while "+
      "since it has been used.\n");
 
   add_item(({"box","boxes"}),
      "Long rectangular boxes made of hard pine are stacked around "+
      "the room, probably full of the weapons and other metal "+
      "items made here.\n");
   add_cmd_item(({"box","boxes"}),({"open","break","break open"}),
      "The heavy boxes are sealed and can not be opened.\n");
 
   add_item("anvil","@@exa_anvil");
   add_item(({"sword","sword on anvil","sword on the anvil",
             "sword from anvil","sword from the anvil"}),
             "@@exa_sword");
   add_item(({"hammer","hammer on anvil","hammer on the anvil",
             "hammer from anvil","hammer from the anvil"}),
             "@@exa_hammer");
 
   add_prop(ROOM_I_INSIDE,1);
 
   add_exit(ROOM_DIR+"corr16","west",0);
}
 
string
exa_anvil() {
   string desc;
   desc="It is a large block of iron, used as a table where the "+
        "metal craftsman beats his 'clay' into beautiful and "+
        "functional objects. ";
   if (hammer_here)
      if (sword_here)
         desc = desc+"There is a sword and a hammer laying on it.\n";
      else
         desc = desc+"There is a hammer laying on it.\n";
   else
      if (sword_here)
         desc = desc + "There is a sword laying on it.\n";
      else
         desc = desc + "\n";
   return desc;
}
string exa_hammer() {
   if (hammer_here) return "It is laying on top of the anvil.\n";
   else return "You find no hammer in the room.\n";
}
string exa_sword() {
   if (sword_here) return "It is laying on top of the anvil.\n";
   else return "You find no sword in the room.\n";
}
 
 
int take(string ParmStr) {
   object TPlay=this_player();
   object TRoom=this_object();
   object sword;
   object hammer;
   string *Parm;
   int    FoundSword=0;
   int    FoundHammer=0;
   int    i;
 
   if (!(hammer_here||sword_here)) return 0;
   if (!ParmStr) return 0;
   Parm=explode(ParmStr," ");
 
   for (i=0; i<sizeof(Parm); i++)
      if (Parm[i]=="hammer") FoundHammer=1;
      else if (Parm[i]=="sword") FoundSword=1;
 
   if ((FoundHammer)&&(hammer_here)) {
      hammer=clone_object(WEAPON_DIR+"fohammer");
      hammer->move(TPlay);
      write("You take the hammer from the anvil.\n");
      tell_room(TRoom,QCNAME(TPlay)+" takes a hammer from the anvil.\n",
                TPlay);
      write("The hammer is hot and burns your hand! You yelp in pain!\n");
      tell_room(TRoom,QCNAME(TPlay)+" yelps in pain!\n",TPlay);
      hammer_here=0;
      return 1;
   }
 
   if ((FoundSword)&&(sword_here)) {
      sword=clone_object(WEAPON_DIR+"sword");
      sword->move(TPlay);
      write("You take the sword from the anvil.\n");
      tell_room(TRoom,QCNAME(TPlay)+" takes a sword from the anvil.\n",
                TPlay);
      sword_here=0;
      return 1;
   }
   return 0;
}
 
void init() {
   ::init();
   add_action("take","get");
   add_action("take","take");
}
