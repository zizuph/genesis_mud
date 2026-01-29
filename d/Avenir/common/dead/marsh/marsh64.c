// file name: marsh64
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
marsh_long(randmarsh[random(sizeof(randmarsh))]+" The "
   +"mist thins slightly to the west.");

am("66","north");
am("62","south");
am("65","east");
AE(PATH+"path7","west",0,3);

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
