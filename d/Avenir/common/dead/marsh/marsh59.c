// file name: marsh59
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
marsh_long(randmarsh[random(sizeof(randmarsh))]);

am("62","north");
am("56","south");
am("58","west");
am("60","east");

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
