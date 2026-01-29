//
// plateau2.c - plateau on the cliffs
//              part of the entrance quest for Sean Rhian done here
//              all code in the "pit" object
//
// Zima - June 3, 98
//
inherit "/d/Khalakhor/std/room";
#include "local.h"
 
public void create_khalakhor_room()
{
   set_short("On a plateau of the cliffs overlooking the sea");
   set_long("   You are standing at the edge of a high plateau in the cliffs "+
            "along the coast of Cala Fasgadh near Port MacDunn. The wind "+
            "blows so strongly here it is somewhat difficult to "+
            "keep your balance. The plateau extends over the waters of "+
            "the harbour here, with dangerous drop-offs along the west, "+
            "east and south sides. The plateau slopes back to the "+
            "north where the cliffs rise ever higher. You have a "+
            "spectacular view of the harbour here.\n");
 
    add_item(({"plateau","point"}),
       "It is a flat, though slightly angled up to the south, "+
       "area cut into the face of the cliffs. Walled on the north "+
       "by the cliffs, with steep drop offs to the east and west, "+
       "it continues further out to a point to the south.\n");
    add_item(({"cliff","cliffs","wall","walls"}), "Forged by the "+
       "pounding seas with razor sharp edges, the cliffs rise straight "+
       "up from the plateau the north, dashing any hope of climbing "+
       "up them. Over the edge of the plateau the cliffs drop off "+
       "straight down, though you can probably climb down the east "+
       "side the way you came up.\n");
    add_item("pier","You can see it far to the east.\n");
    add_item("boats","There are a few boats in the tumultuous harbour "+
      "to the south.\n");
    add_item("boat","Each boat is different.\n");
    add_item(({"water","salt water","salty water"}),"The water, which " +
      "is the essential element of the harbour, is salty. It is " +
      "rather clean, however.\n");
    add_item(({"harbour","harbour","cala","cala fasgadh","view"}),
      "The harbour extends to the southwest, where it meets Lear " +
      "Min, the sea, which extends all along the southern horizon.\n");
    add_item(({"shore","rocky shore","beach"}),"The rocks on the shore "+
      "far below are sharp and dangerous, though a narrow strip of "+
      "beach lies between them and the pounding surf.\n");
    add_item("rocks","The rocks have razor-sharp edges and might " +
      "cut anyone attempting to pass through them.\n");
    add_item(({"surf","waves"}),"The waves are unusually high for a "+
       "peaceful harbour. They pound violently against the shore.\n");
    add_item("sky","The semi-cloudy sky above you is a typical " +
      "coastal sky.\n");
    add_item("clouds","The clouds above are grey and streaky.\n");
    add_item("cloud","Each cloud looks about the same, although " +
      "location and size differ.\n");
    add_cmd_item(({"water","sea","harbour","into water","into sea",
        "into harbour","off rocks","off beach","off shore"}),
        ({"enter","swim","dive"}),
        "It is much to high to do that, as it would be instant death.\n");
    add_cmd_item(({"cliff","cliffs","rocks","up","up rocks","up cliff",
       "up cliffs"}),"climb","You aren't close enough.\n");
    add_cmd_item(({"down","down rocks","down cliff","down cliffs"}),
       "climb","That would mean instant death here.\n");
 
   add_exit("plateau1","north");
   (clone_object(BEACH_DIR+"pit"))->move(this_object());
}
