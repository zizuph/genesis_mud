/*
**  MCLUB - Memorial Shrine, West Entrance
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
      "You enter the western vestibule of a stone shrine, the ancient "+
      "stones emanating a mysteriously cold but inviting presence. "+
      "A steep set of steps leads out of the foyer down the hill "+
      "to the west, while two doorways lead north and south into "+
      "the sunshine. A tall painting hangs next to the entrance to the "+
      "central chamber of the shrine to the east, which is marked by "+
      "a high pointed arch.\n");
 
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
      "The roof slants westward away from the center of the shrine, "+
      "made of simple wooden shingles.\n");
   add_item("steps",
      "The steps are long flat stones set into the side of the steep "+
      "hill on which the shrine sets to allow for an easier climb "+
      "to the summit. They lead out, down to the western side of "+
      "the hill.\n");
   add_item("hill",
      "The shrine is built on top of a rather steep hill. A set of "+
      "steps lead out to the west to the hill's base.\n");
   add_item(({"doorway","doorways"}),
      "Rectangular doorways lead to the north and south, apparently "+
      "to outdoor areas from where the sunlight spills in.\n");
   add_item(({"arch","entrance"}),
      "The arch is a thick arch made of heavy oak, its sides marking the "+
      "entrance to the chamber to the east, meeting at the apex "+
      "in a gothic point. The wood is polished and well-oiled.\n");
   add_item("central chamber","It is to the east.\n");
   add_item("painting","@@exa_painting");
 
   add_prop(ROOM_I_INSIDE,1);
 
   add_exit(ROOM_DIR+"shgardnw","north", 0);
   add_exit(ROOM_DIR+"shgardsw","south", 0);
   add_exit(ROOM_DIR+"shtemple","east",0);
   add_exit(ROOM_DIR+"shoak9", "steps","@@steps");
}
 
string exa_painting() {
   string desc = "The oil painting depicts and elderly human with a kind "+
          "face, dressed in a long blue robe with a silver mantle embroidered "+
          "with stars. He stands before an altar with his hands upraised "+
          "as he chants an ancient aria.";
 
   if (InMClub(this_player()))
      desc=desc+" You recognize the figure as Mieriys the Holy Cantor.\n";
   else
      desc=desc+"\n";
   return desc;
}
 
int steps() {
   write("You walk down the steps to the west.\n");
   return 0;
}
