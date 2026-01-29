// file name: marsh57
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
marsh_long(randmarsh[random(sizeof(randmarsh))]+" To the south "
   +"and east can be heard the sounds of the sea.");

am("60","north");
am("56","west");
AE(PATH+"shore29","east",0,3);
AE(PATH+"shore28","south",0,3);

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
