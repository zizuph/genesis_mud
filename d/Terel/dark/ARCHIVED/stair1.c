
inherit "/std/room";

#define PATH "/d/Terel/dark/"

create_room(){

set_short("Stair");
set_long("An elaborate set of stairs has been cut into the\n"
   +"the stone, polished and gleaming of bright red carnelian\n"
    +"and deep multi-colored sardonyx.\n"
);

add_exit(PATH + "ne1", "up");
add_exit("/d/Avenir/common/dark/l1/stair4", "down", 0);
add_exit("/d/Terel/dark/lair", "north");
}

