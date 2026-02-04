inherit "std/room";

#define PATH "/d/Terel/common/swamp/"

create_room(){
set_short("Cliff");
set_long("The swamp dries up here, due to the incline. Rising up\n"
   + "here is a solid cliff face, of ice and rock. It is not\n"
   + "possible to pass.\n");

add_item("cliff", "It is a sheer face, unpassable.\n");

add_exit(PATH + "g2", "south", 0);

}
