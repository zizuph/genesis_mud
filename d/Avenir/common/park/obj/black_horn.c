// file name: black_horn.c
// creator(s): Ilyian
// last update: Boriska, lowered items value 
//              Cirion, June 1997: Made then usable as daggers
// purpose: Horn of /mon/bicorna.c, used as a leftover
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/inherit/weapon";
#include "/d/Avenir/common/common.h"

void
create_weapon()
{
        set_name("horn");
        set_short("sharp black horn");
        set_adj("sharp");
        add_adj("black");
        set_long("This is a beautiful, ebony-black horn from some "
               +"strange creature. It is smooth, and seems to be "
               +"made of some sort of ivory, tapering to a razor "
               +"sharp point at the end. The light is reflected "
               +"by the shiny black surface, causing the horn to glimmer "
		+"slightly as you regard it.\n");

       add_prop (OBJ_I_WEIGHT, 25);
       add_prop (OBJ_I_VOLUME, 50);
       add_prop (OBJ_I_VALUE, 150 + random(100));

    set_default_weapon(12, 12, W_KNIFE, W_IMPALE, W_ANYH);
}

