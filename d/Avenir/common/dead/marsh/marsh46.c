// file name: marsh46
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
marsh_long(randmarsh[random(sizeof(randmarsh))]+" A steep hill "
    +"climbs out of the mire to the south, and from the west "
    +"you can hear the sound of water.");

add_hill();

AE(HILL+"hill7","south",0,5);
AE(PATH+"shore18","west",0,3);
am("50","north");
am("47","east");

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
