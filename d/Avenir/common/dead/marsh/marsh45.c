// file name: marsh45
// creator(s): Ilyian (24 August, 1995)
// last update:
// purpose:
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/common/dead/dead";
#include "../dead.h"

create_room()
{
marsh_long(randmarsh[random(sizeof(randmarsh))]+" To the east "
    +"rises a steep hill, and to the north and west, the "
    +"mist thins out a little, revealing the shorline of the "
    +"island.");

add_hill();

AE(HILL+"hill7","east",0,5);
AE(PATH+"shore17","west",0,3);
AE(PATH+"shore18","north",0,3);
am("44","south");

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
