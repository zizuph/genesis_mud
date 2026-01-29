// file name: marsh63
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
marsh_long(randmarsh[random(sizeof(randmarsh))]+" To the "
    +"east you can hear the sound of waves lapping against "
    +"the shorline.");

am("65","north");
am("60","south");
am("62","west");
AE(PATH+"shore31","east",0,3);

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
