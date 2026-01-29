inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Sarr */


void
create_room()
{
    set_short("In a stairwell in the House of Alexander");
    set_long("You stand in a small stairwell. The stairs here "+
    "are made of black oak, and spiral upwards to the upper "+
    "level of this grand estate. A few candles burn on a "+
    "little stand here.\n");
  
    add_item("stand","The stand is made of black oak, and holds "+
    "some candles.\n");
    add_item("candles","The candles light up this little room.\n");
    add_item("stairs","The stairs are sturdy.\n");

    INSIDE;

    add_exit(NOBLE(alexander/m5),"north",0,-1,0);
    add_exit(NOBLE(alexander/m1),"northwest",0,-1,0);
    add_exit(NOBLE(alexander/m20),"up",0,-1,0);
}
