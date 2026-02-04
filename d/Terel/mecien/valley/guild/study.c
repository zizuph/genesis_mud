/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";

#define PATH "/d/Terel/mecien/valley/guild/"

create_room(){

set_short("Study");
set_long("This elegant wooden loft carved of soft pine looks out\n"
  + "over the vast library. A long table with chairs takes\n"
  + "most of the room. A silver chandelier lights the area,\n"
  + "hanging over the center of the table.\n"
);

add_exit(PATH + "library", "down", 0);
add_my_desc("A small wooden staircase leads down.\n");
add_item("table", "A beautiful long table made of pine. Itis used\n"
  + "for study ad meetings.\n");
add_item("chairs", "They are slender pine chairs with blue cushions.\n");
add_item("chandelier", "It is an elaborate one made of silver. It has\n"
  + "about a dozen candles lit.\n");
add_item("library", "It is vast and ancient. It must hold many secrets.\n");
   clone_object(PATH + "obj/dagger3")->move(this_object());

}


