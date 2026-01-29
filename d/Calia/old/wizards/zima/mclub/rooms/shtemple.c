/*
**  MCLUB - Memorial Shrine, Temple (Central Chamber)
**
**  History:
**  Coder        Date                       Action
**  ---------- --------  -----------------------------------------------------
**  Zima       4/7/95    Created
**                       Starting Room for the X-Mystics club.
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
create_room() {
   set_short("The temple of a shrine");
   set_long(
      "You are standing in the central chamber of a mysterious stone "+
      "shrine, encircled by twelve pillars which stand along the "+
      "edges of the tiled floor. Sunlight beams brightly through "+
      "a window on the ceiling of the room, filling it with an aura "+
      "of peace and hope. Four tall pointed arches mark the entrances "+
      "to other chambers in each direction. A feeling of remembrance "+
      "of days past comes over you as you stand in the center of the "+
      "temple, fleeting away in short moment.\n");
 
   add_item(({"central chamber","chamber","temple","ceiling"}),
      "It is a circular chamber made of stone, the center of a "+
      "mysterious shrine. You feel a great presence here, though "+
      "you can not identify it.\n");
   add_item(({"rocks","stones","walls","wall"}),
      "The walls of the chamber are constructed of rocks and stones of "+
      "various sizes and shapes. They mysteriously meld together to "+
      "create the thick walls of the fortressed shrine. The stones look "+
      "rather ancient, worn by centuries of weather, but seem to have "+
      "been recently placed to construct this chamber.\n");
   add_item(({"roof","ceiling","shingles","window"}),
      "The ceiling is made of simple wooden shingles, fanning out from "+
      "the circular center of the chamber. A large round window of painted "+
      "glass centers the ceiling, a painting of a four-pointed blue star "+
      "adorning the window with simple beauty.\n");
   add_item(({"pillar","pillars"}),
      "Twelve pillars encircle the room, three between each arch, "+
      "made of the trunks of trees, sanded to a delicate smoothness. "+
      "They are painted white with long green serpents coiled around "+
      "their trunk.\n");
   add_item(({"sunlight","light"}),
      "Sunlight cascades down through the window of the room, casting "+
      "the image of its blue star on the tile floor of the chamber.\n");
   add_item(({"tile","tiles","floor"}),
      "The floor is covered in baked tiles set in concentric circles "+
      "emanating from the center. A large circle of the tiles are painted "+
      "white, while the remaining are unpainted earth tones. Sunlight "+
      "beaming through the window above casts the image of its symbol "+
      "onto the center of the floor.\n");
   add_item(({"arch","arches"}),
      "Four arches demark the entrances to other chambers of the shrine, "+
      "one in each direction. They are made of heavy oak, their sides "+
      "meeting at their apex in a gothic point. The wood is polished "+
      "and well-oiled.\n");
 
   add_prop(ROOM_I_INSIDE,1);
 
   add_exit(ROOM_DIR+"shvestn","north", 0);
   add_exit(ROOM_DIR+"shvests","south",0);
   add_exit(ROOM_DIR+"shsanct","east",0);
   add_exit(ROOM_DIR+"shvestw","west",0);
}
