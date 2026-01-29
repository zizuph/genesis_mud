// file name: marsh21
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
set_short("Grey Marsh");
marsh_long(randmarsh[random(sizeof(randmarsh))]+" The mist "
          +"parts slightly to the east.");

am("24","north");
am("16","south");
am("20","west");
AE(PATH+"path5","east",0,3);

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
