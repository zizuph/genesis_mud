/*
**  MCLUB - Memorial Shrine, South Entrance
**
**  History:
**  Coder        Date                       Action
**  ---------- --------  -----------------------------------------------------
**  Zima       4/7/95    Created
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
create_room() {
   object door;
   set_short("The vestibule of a shrine");
   set_long(
      "You are standing in the souther vestibule of a stone shrine, "+
      "sunlight falling on the floor from a doorway to the west. "+
      "A high pointed arch demarks the entrance to the central chamber "+
      "of the shrine to the north, while a set of steep steps lead out "+
      "of the vestibule to the base of the hill to the south. A tall "+
      "painting hangs on the cold stones next to a heavy oak door "+
      "on the chamber's east wall.\n");
 
   add_item(({"vestibule","chamber"}),
      "It is a simple square chamber constructed of irregular stones "+
      "of various sizes and shapes. A roof of wooden shingles protects "+
      "the interior from the elements.\n");
   add_item(({"rocks","stones","walls","wall"}),
      "The walls of the chamber are constructed of rocks and stones of "+
      "various sizes and shapes. They mysteriously meld together to "+
      "create the thick walls of the fortressed shrine. The stones look "+
      "rather ancient, worn by centuries of weather, but seem to have "+
      "been recently placed to construct this chamber.\n");
   add_item(({"roof","ceiling","shingles"}),
      "The roof slants southward away from the center of the shrine, "+
      "made of simple wooden shingles.\n");
   add_item("steps",
      "The steps are long flat stones set into the side of the steep "+
      "hill on which the shrine sets to allow for an easier climb "+
      "to the summit. They lead out, down to the southern side of "+
      "the hill.\n");
   add_item("hill",
      "The shrine is built on top of a rather steep hill. A set of "+
      "steps lead out to the south to the hill's base.\n");
   add_item(({"doorway","doorways"}),
      "Sunlight spills in from a rectangular doorway which leads to "+
      "an outdoor area to the west.\n");
   add_item(({"arch","entrance"}),
      "The arch is a thick arch made of heavy oak, its sides marking the "+
      "entrance to the chamber to the north, meeting at the apex "+
      "in a gothic point. The wood is polished and well-oiled.\n");
   add_item("central chamber","It is to the north.\n");
   add_item("painting","@@exa_painting");
 
   add_prop(ROOM_I_INSIDE,1);
 
   door=clone_object(ROOM_DIR+"bdoorout"); /* doorway to belltower */
   door->move(this_object());
   add_exit(ROOM_DIR+"shtemple","north", 0);
   add_exit(ROOM_DIR+"shgardsw","west", 0);
   add_exit(ROOM_DIR+"shoak6", "steps","@@steps");
}
 
string exa_painting() {
   string desc = "The oil painting depicts and strong elf armoured in "+
          "a silver helmet and mail, holding a silvery-steel longsword "+
          "with the point on the ground. A golden winged-lion sits next "+
          "to him, a mysterious creature of great strength.";
 
   if (InMClub(this_player()))
      desc=desc+" You recognize the figures as Cirthes the Doorkeeper "+
                "and Asrafar the Guardian of the Ancients.\n";
   else
      desc=desc+"\n";
   return desc;
}
 
int steps() {
   write("You walk down the steps to the south.\n");
   return 0;
}
