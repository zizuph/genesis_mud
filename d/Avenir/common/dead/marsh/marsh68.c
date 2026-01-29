// file name: marsh68
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
  +"north and the west, a steep hill rises from the "
  +"swamp.");

add_hill();

am("66","south");
am("69","east");
AE(HILL+"hill12","north",0,5);
AE(HILL+"hill13","west",0,5);

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
