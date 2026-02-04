/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/d/Terel/mecien/valley/guild/courtyard/garden_room";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

#define PATH "/d/Terel/mecien/valley/guild/courtyard/"

create_room(){
   ::create_room();
   set_short("Garden");
   set_long("Solemn and inspiring, this courtyard is an open garden\n"
      + "of evergreen hedges and flowers. All about the hedges rise,\n"
      + "gleaming in the sunlight, the air rich and moist. Amidst the\n"
      + "hedges are patches of moss, it grows out to the edges of the\n"
      + "simple stone path.\n"
   );
   
   
   add_item("hedges", "Tall hedges of juniper and holly.\n");
   add_item("juniper", "A beautiful deep coloured evergreen. It sprouts\n"
      + "small bluish-gray berries and has prickly leaves.\n");
   add_item("holly", "Bright and shiny evergreen, it sprouts tiny red\n"
      + "and white berries.\n");
   add_item("moss", "A thick and plush blue-green moss, it fills the spaces\n"
      + "between the hedges.\n");
   add_item("path", "Small paths of white stones traverse the garden.\n");
   add_item("flowers", "They are pale violet orchids, they grow tall and\n"
      + "have many blossums.\n");
   add_item("orchids", "Beautiful pale violet flowers.\n");
   
   add_cmd_item(({"orchid", "hedges", "moss", "hedge", "leaf",
    "flower"}), "pick", "It seems wrong, thus you desist.\n");
   add_cmd_item(({"orchid", "flowers", "flower"}), "smell",
      "A sweet smell, strong and almost unbearable.\n");
   
  add_exit(PATH + "g2", "southwest", 0);
   add_exit(PATH + "edge", "northeast", 0);
}


