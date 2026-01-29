// file name: white_horn.c
// creator(s): Ilyian
// last update: 
//              Cirion, June 1997: Made then usable as daggers
// purpose: Horn of /mon/bicornb.c, used as a leftover
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/inherit/weapon";
#include "/d/Avenir/common/common.h"

void
create_weapon()
{
        set_name("horn");
        set_short("white beautiful horn");
        set_adj("beautiful");
        add_adj("white");
        set_long("This is a very long ivory horn, from some "
           +"strange creature. It tapers to a razor sharp point "
           +"at the end, and it's flawlessly smooth along its length. "
           +"The smooth finish reflects the surrounding light to the point "
	   +"of almost seeming to shine by itself.\n");

       add_prop (OBJ_I_WEIGHT, 25);
       add_prop (OBJ_I_VOLUME, 50);
       add_prop (OBJ_I_VALUE,  150 + random(100));

    set_default_weapon(10, 10, W_KNIFE, W_IMPALE, W_ANYH);
}

