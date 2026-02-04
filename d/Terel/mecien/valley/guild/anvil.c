/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/object";
#include <macros.h>
#include <stdproperties.h>

#define PATH  "/d/Terel/mecien/valley/guild/"
#define TP  this_player()

create_object(){

set_name("anvil");
set_short("mysterious black anvil");
set_long(
"It is a massive black anvil, wroght from some deep and dark\n"
+ "metal, mysterious and almost hypnotizing. It rests upon a short\n"
+ "wood stand.\n"
);
add_prop(OBJ_I_NO_GET, "It is too heavy.\n");

}

