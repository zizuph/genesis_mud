/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>

#define PATH "/d/Terel/mecien/valley/guild/"

create_room(){

set_short("Secret Stair");
set_long(
"Deep and shadowy, this open gothic chamber is the landing to some\n"
+"massive staircase leading upwards into a haunting mist. This place,\n"
+"like some huge cylindrical pit, echoes whispers and mysteries of some\n"
+"ancient days. The staircase spirals up around the sides of the pit,\n"
+"open and dangerous. The stone here is some strange deep aquamarine colour\n"
+"and the walls are painted with strange silvery runes.\n"
);

add_item("runes", "They are silvery and incribed upon the walls.\n");
add_cmd_item("runes", "read", "MYSTERY, THE MOTHER OF LIFE\n");
add_item("stairs", "They leads upwards in a spiral.\n");

add_exit(PATH + "ss2a", "up", 0);
add_exit(PATH + "sfoyer", "east", 0);
add_exit(PATH + "lowt1", "north", 0);
add_exit(PATH + "dc1", "west", 0);

}

