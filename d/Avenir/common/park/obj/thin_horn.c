// file name: thin_horn.c
// creator(s): Ilyian
// last update: 
//              Cirion, June 1997: Made then usable as daggers
// purpose: Horn of /mon/bicornblk.c, used as a leftover
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/inherit/weapon";
#include "/d/Avenir/common/common.h"

void
create_weapon()
{
        set_name("horn");
        set_short("thin black horn");
        set_adj("thin");
        add_adj("black");
        set_long("This is a thin black horn, and very sharp at the "
           +"end. The sides are somewhat rough and not completely "
           +"formed, but it a beautiful object nonetheless.\n");

       add_prop (OBJ_I_WEIGHT, 20);
       add_prop (OBJ_I_VOLUME, 40);
       add_prop (OBJ_I_VALUE,  130 + random(90));

    set_default_weapon(4, 4, W_KNIFE, W_IMPALE, W_ANYH);
}
