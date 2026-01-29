// file name: marsh42
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
     +"hill climbs up from the marsh to the east.");

add_hill();

AE(HILL+"hill3","east",0,5);
am("44","north");
am("39","south");
am("41","west");

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
