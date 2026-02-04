/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>

#define PATH "/d/Terel/mecien/valley/guild/"

create_room(){

set_short("Secret Stair");
set_long(
"Silent in its dismal secrecy, this circular chamber is nothing\n"
+"more than an open staircase leading down in a spiral. From here\n"
+"the stair begins its descent, into a shadowy mist, the stone a\n"
+"strange and almost hypnotic aquamarine. This small landing is all\n"
+"there is before one descends into the darkness.\n"
);


add_exit(PATH + "ss2", "down", 0);
add_exit(PATH + "n_hall2", "east", 0);

}

