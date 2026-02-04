/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>

#define PATH "/d/Terel/mecien/valley/guild/"

create_room(){

set_short("Hallway");
set_long(
"The dismal stone hall rises up to form a small vault that\n"
+ "meets the south wall, forming half an oval. A thick cloud\n"
+ "of incense billows out of a pair of censers that hang from\n"
+ "the vaulted ceiling. The floor is painted with a silver and\n"
+ "white star, it shimmers and sparkles. An open black archway\n"
+ "leads south, high above it on the wall is a large inscription\n"
+ "of gothic letters.\n"
);

add_item("archway", "It is simply carved from jet.\n");
add_item(({"floor", "star"}),
   "The floor has been painted with a beautiful silver and\n"
  + "white four-pointed star. The colors seem to sparkle and\n"
  + "and shimmer with a pale light.\n");
add_item(({"incense", "cloud"}), 
  "A thick cloud of incense, it billows out of a pair of censers.\n");
add_item(({"letters", "inscription"}), "They are large painted letters.\n");

add_cmd_item("incense", "smell", "It is balsam and myrrh.\n");
add_cmd_item(({"inscription", "writing", "letters"}),
"read", "\n       IN MYSTERY ABIDES TRUTH\n" +
"  COMING FORTH FROM THE ANCIENT DAYS OUR FIRES SHALL\n" +
"  NOT BE QUELLED. THUS SHALL WE ARISE IN THE GLORY OF\n" +
"  THE TRUTH IN ITS MOST SACRED FORM, THE HOLY FLAME\n");
add_exit(PATH + "u_hall1", "north", 0);
add_exit(PATH + "hearth", "south", 0);


}
