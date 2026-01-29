// file name: blue_horn.c
// creator(s): Ilyian
// last update: 
//              Cirion, June 1997: Made then usable as daggers
// purpose: Horn of /mon/bicornv.c, used as a leftover
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/inherit/weapon";
#include "/d/Avenir/common/common.h"

void
create_weapon()
{
        set_name("horn");
        set_short("tiny blue horn");
        set_adj("tiny");
        add_adj("blue");
        set_long("This is a small blue horn of an ivory-like "
            +"material. It tapers to a rounded point at the end, "
            +"and is quite soft.\n");

       add_prop (OBJ_I_WEIGHT, 10);
       add_prop (OBJ_I_VOLUME, 20);
       add_prop (OBJ_I_VALUE,  102);

    set_default_weapon(8, 8, W_KNIFE, W_IMPALE, W_ANYH);
}
