// file name: marsh49
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
marsh_long(randmarsh[random(sizeof(randmarsh))]+" To the south, "
    +"a long and sheer cliff rises from the mire.");

AI(({"cliff","ledge","rock"}),"The large cliff towers above "
    +"you, disappearing into the mist. The sides are rough, "
    +"and it appears to be completely unclimbable. From "
    +"the east you can hear the sound of water lapping "
    +"against the shore of the island.\n");

add_cmd_item("cliff","climb","The rock is too sheer.\n");

am("53","north");
am("48","west");
AE(PATH+"shore25","east",0,3);

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
