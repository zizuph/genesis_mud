// file name: marsh61
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
marsh_long(randmarsh[random(sizeof(randmarsh))]+" To the north "
    +"and west you can see a narrow cobbled path running "
    +"through the fog.");

am("58","south");
am("62","east");
AE(PATH+"path6","west",0,3);
AE(PATH+"path7","north",0,3);

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
