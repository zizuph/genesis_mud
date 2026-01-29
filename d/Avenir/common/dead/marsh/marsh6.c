// file name: marsh6
// creator(s): Ilyian (21 August, 1995)
// last update:
// purpose:
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/common/dead/dead";
#include "../dead.h"

create_room()
{
set_short("Grey Marsh");
marsh_long("The fog snakes in and out of itself, creating eerie "
          +"patterns.");

am("7","east");
am("5","west");
am("9","north");
am("4","south");
reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
}
