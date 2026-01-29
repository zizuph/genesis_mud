inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   int i;
   set_short("rat place\n");
   set_long("This passageway of large, stone blocks turns " +
      "sharply here.  There is a slight sideways slant to the " +
      "passageway that is making you a bit uneasy about roaming " +
      "about down here.  The passage is flooded with about a foot " +
      "or so of water and is inhabited...\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item("water","The water is murky, green, and littered with " +
      
      "pieces of trash you can only guess as to where they came from " +
      "or what they're made of which float on top of the water along " +
      "with a filmy layer of slime.\n");
   add_item(({"block","blocks"}), "These large, dark blocks of " +
      "stone approximately one by two feet in dimension are covered " +
      "with brackish green and black molds and drip slime from tiny " +
      "cracks throughout the mortar.\n");
   for (i = 0; i < 5; i++)
   clone_object("/d/Rhovanion/mute/dungeon1/rat.c")->move(TO);
   for (i = 0; i< 3; i++)
   clone_object("/d/Rhovanion/mute/dungeon1/rat2.c")->move(TO);
   for (i = 0; i < 7; i++)
   clone_object("/d/Rhovanion/mute/dungeon1/rat3.c")->move(TO);
   add_exit("/d/Rhovanion/mute/dungeon1/tun19","north");
   add_exit("/d/Rhovanion/mute/dungeon1/int7","east");
}

