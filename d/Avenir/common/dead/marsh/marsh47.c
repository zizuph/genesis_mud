// file name: marsh47
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
marsh_long(randmarsh[random(sizeof(randmarsh))]+" A steep "
   +"hill climbs up to the south.");

add_hill();

AE(HILL+"hill8","south",0,5);
am("51","north");
am("46","west");
am("48","east");

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
