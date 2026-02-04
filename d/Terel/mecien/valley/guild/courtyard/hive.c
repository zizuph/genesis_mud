inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>

#define TP this_player()
#define TO this_object()
#define EN environment

create_room(){
   
   set_short("Garden Grove");
   set_long(
      "This is a beautiful evergreen grove at the edge of the garden. The walls " +
      "of the shrine are just beyond the edges of the evergreen that circle and make " +
      "this grove. In the center here it is clear, with a wooden post, upon which " +
      "is a strange spiralled globe.\n"
   );
   
   add_item(({"spiralled globe", "hive", "globe"}), "It is made from unknown " +
      "materials, a circular globe that spirals up like a strange little building with a hole at its base.\n");
   add_item("post", "It is a small wooden post, upon which rests the spiralled globe.\n");
   add_item("walls", "They are the walls of the shrine.\n");
   add_item("grove", "This is a small circular grove created by the evergreens.\n");
   add_item(({"evergreens", "evergreen", "trees", "bay", "bay trees"})
      , "These beautiful trees seem to be some variety of bay.\n");
   
   add_item("hole", "It is a small hole in the globe.\n");
   
  add_exit("/d/Terel/mecien/valley/guild/courtyard/sh2", "southeast", 0);

   set_alarm(1.0, -1.0, "bees");
   
}

bees(){
   seteuid(getuid());
   clone_object("/d/Terel/mecien/valley/guild/courtyard/bees")->move(TO);
}

