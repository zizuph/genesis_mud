/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "std/room";

#define PATH "/d/Terel/mecien/valley/guild/"

create_room(){
set_short("Lower Hall");
set_long(
"Cryptic in its ancient patterns, this lower hall is formed of\n"
+"bleak and shadowy stone. The air itself seems to whisper the\n"
+"voices of the ages. The floor smooth and damp, painted with a\n"
+"design of silvery stars.\n"
);

add_exit(PATH + "d_hall2", "east", 0);
add_exit(PATH + "chamber", "up", 0);

add_item("floor",
    "The floor is painted with a design of silvery stars.\n");
add_item("stars", "They are very silvery.\n");

}

