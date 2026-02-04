/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";
#include "defs.h"

#define PATH "/d/Terel/mecien/valley/guild/crypt"

create_room(){
   object door;
   
   set_short("Ancient Mausoleum");
   set_long(
      "Here within these ancient catacombs a massive and terrible\n"
      + "mausoleum has been built. Of deep gray stone, it fills the\n"
      + "catacomb like some forsaken palace, a refuge for the dead\n"
      + "that are long forgotten. Its walls are barren, except for the\n"
      + "sconces that protrude from its front. An emptiness arises\n"
      + "from this place, a harrowing sensation. A layer of dust coats\n"
      + "the area, like a mantle of antiquity.\n"
   );
   add_item("ceiling", "It is vaulted, very dark and inscrived with symbols.\n");
   add_item(({"runes", "symbols"}), "They are runes and symbols of the dead.\n");
   add_cmd_item(({"runes", "symbols"}), "read",
     "As you start to read the runes, you are suddenly filled\n" +
    "with a dread of the dead. You stop reading very abruptly.\n");
   add_item("sconces", "They are old iron sconces, lit with thick black\n"
   + "candles that cast a strange glow.\n");
   add_item("candles", "They are thick black candles and cast a strange\n"
   + "glow. A strong scent emanates from them.\n");
   add_cmd_item(({"candle", "candles"}), "smell",
    "A stronge fresh smell of bayberry.\n");
   
   add_exit(PATH + "/c3", "north", 0);
   add_exit(MAZE, "south", 0);
   add_exit(MAZE, "east", 0);
   
   door=clone_object(PATH + "/mdoor1");
   door->move(this_object());
  door->set_key(01710);
   
}

