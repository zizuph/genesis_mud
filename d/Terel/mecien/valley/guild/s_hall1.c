/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>

object mon;

#define PATH "/d/Terel/mecien/valley/guild/"

reset_room()
{
    if(!mon){
        mon = clone_object(PATH + "mystic4");
        mon->move_living("X", this_object());
    }
}

create_room(){

    set_short("Hallway");
    set_long("Stone arches form the ceiling of this small darkened stone\n" +
             "corridor. Sounds echo here from throughout the shrine, but only\n"
             +"arrive as whispers. Small stained-glass windows line the upper\n"
             +"areas, but provide only a small amount of light.\n");

    add_exit(PATH + "hall", "north", 0);
    add_exit(PATH + "s_hall2", "south", 0);

    add_item(({"windows", "stained-glass windows", "stained-glass"}),
             "They are small and simple. They depict lives of some of the " +
             "great\nand wise mystics.\n");
    reset_room();
}
