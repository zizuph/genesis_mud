inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>

#define PATH "/d/Terel/mecien/valley/city/"

create_room(){

set_short("Street");
set_long(
"The stones of the road are loose, the pieces broken. Tall buildings\n"
+"hang over the street, providing a haunted feeling. A light mist hangs\n"
+"in the air, but nothing more. North of the street a gothic white building\n"
+"towers, to the south a small stone building stands, a small blue and\n"
+"white canopy stretched out from it.\n"
);

add_exit(PATH + "square", "east", 0);
add_exit(PATH + "hall", "north", 0);
add_exit(PATH + "eatery", "south", "@@closed");
add_exit(PATH + "street8", "west", 0);

add_item("canopy", "It is blue and white striped. There is writing on it.\n");
add_cmd_item("canopy", "read", "Ulavi's Eatery\n");

}

closed(){
write("It is closed.\n");
return 1;
}

