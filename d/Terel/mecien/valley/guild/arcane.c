/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";

#define PATH "/d/Terel/mecien/valley/guild/"

create_room(){

set_short("Shelves");
set_long("This is a deep passage between the rows of the library\n"
  + "shelves. Carved wooden arches lead into the different\n"
   + "sections. A small table and chair stand in the corner\n"
  + "between two of the arches.\n"
);

add_item("table", "It is a beatiful oak table, it is small and\n"
   + "kept here just for quick note writing.\n");
add_item("chair", "A smooth oak chair, it is carved with the emblem\n"
  + "of the star on its back.\n");
add_item("arch", "Carved of dark cherry-wood and inscribed with\n"
   + "ancient symbols.\n");

add_exit(PATH + "gen_sec", "general", 0);
add_exit(PATH + "abj_sec", "abjurations", 0);
add_exit(PATH + "ench_sec", "enchantments", 0);
add_exit(PATH + "conj_sec", "conjurations", 0);
add_exit(PATH + "library", "out", 0);


}

