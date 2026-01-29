// file name: marsh60
// creator(s): Ilyian (28 August, 1995)
// last update:
// purpose:
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/common/dead/dead";
#include "../dead.h"

create_room()
{
marsh_long(randmarsh[random(sizeof(randmarsh))]+" The fog thins "
   +"out slightly to the east.");

am("63","north");
am("57","south");
am("59","west");
AE(PATH+"shore30","east",0,3);

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
