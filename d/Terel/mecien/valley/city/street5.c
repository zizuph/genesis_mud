inherit "/std/room";

#define PATH "/d/Terel/mecien/valley/city/"

create_room(){

set_short("Street");
set_long(
"Fog rolls over the cobblestone of this northern street, hiding most\n"
+ "everything beneath its shadows. A domed building stands on the\n"
+ "east side of the street.\n"
);

add_exit(PATH + "street4", "south", 0);
add_exit(PATH + "bank", "east", 0);
add_exit(PATH + "street6", "north", 0);


}

