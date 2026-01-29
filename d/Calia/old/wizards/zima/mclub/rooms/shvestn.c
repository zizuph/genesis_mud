/*
**  MCLUB - Memorial Shrine, North Entrance
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
   set_short("The vestibule of a shrine");
   set_long(
      "You are standing in the northern vestibule of a shrine built of "+
      "stone, the ancient rocks seeming to have been recently placed. "+
      "A steep set of steps leads out of the building down the hill "+
      "to the north, while a doorway leads west into the sunshine. "+
      "A pointed arch marks the entrance to the central "+
      "chamber of the shrine to the south, next to which "+
      "hangs a tall painting.\n");
 
   add_item(({"vestibule","chamber"}),
      "It is a simple square chamber constructed of irregular stones "+
      "of various sizes and shapes. A roof of wooden shingles protects "+
      "the interior from the elements. Exits in all four directions "+
      "lead out of the chamber.\n");
   add_item(({"rocks","stones","walls","wall"}),
      "The walls of the chamber are constructed of rocks and stones of "+
      "various sizes and shapes. They mysteriously meld together to "+
      "create the thick walls of the fortressed shrine. The stones look "+
      "rather ancient, worn by centuries of weather, but seem to have "+
      "been recently placed to construct this chamber.\n");
   add_item(({"roof","ceiling","shingles"}),
      "The roof slants northward away from the center of the shrine, "+
      "made of simple wooden shingles.\n");
   add_item("steps",
      "The steps are long flat stones set into the side of the steep "+
      "hill on which the shrine sets to allow for an easier climb "+
      "to the summit. They lead out, down to the northern side of "+
      "the hill.\n");
   add_item("hill",
      "The shrine is built on top of a rather steep hill. A set of "+
      "steps lead out to the north to the hill's base.\n");
   add_item(({"doorway"}),
      "A rectangular doorway leads to the west, apparently "+
      "to an outdoor area from where the sunlight spills in.\n");
   add_item(({"arch","entrance"}),
      "The arch is a thick arch made of heavy oak, its sides marking the "+
      "entrance to the chamber to the south, meeting at the apex "+
      "in a gothic point. The wood is polished and well-oiled.\n");
   add_item("central chamber","It is to the south.\n");
   add_item("painting","@@exa_painting");
 
 
    add_prop(ROOM_I_INSIDE,1);
 
    add_exit(ROOM_DIR+"shgardnw","west", 0);
    add_exit(ROOM_DIR+"shtemple","south",0);
    add_exit(ROOM_DIR+"shoak12", "steps","@@steps");
}
 
string exa_painting() {
   string desc = "The oil painting portrays an elderly human, his eyes full "+
          "of wisdom and strength, dressed in a long green robe with "+
          "a silver mantle. His hands are clasped as in prayer, though "+
          "his eyes seem to stare deep into your soul. He stands "+
          "in an enclave of some magnificent temple, a round dais "+
          "directly behind him. ";
 
   if (InMClub(this_player()))
      desc=desc+" You recognize the figure as Avirigh the Elder Keeper.\n";
   else
      desc=desc+"\n";
   return desc;
}
 
int steps() {
   write("You walk down the steps to the north.\n");
   return 0;
}
