// file name: soft_horn.c
// creator(s): Ilyian
// last update: 
// purpose: Horn of /mon/bicornbrn.c, used as a leftover
//              Cirion, June 1997: Made then usable as daggers
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/inherit/weapon";
#include "/d/Avenir/common/common.h"

void
create_weapon()
{
        set_name("horn");
        set_short("soft white horn");
        set_adj("soft");
        add_adj("white");
        set_long("This is a horn of soft white ivory, beautifully "
            +"smooth and thin. It tapers at a dull point at the end. "
            +"As you hold it up for inspection, the reflected "
	    +"light makes it seem to gleam with a gentle glow.\n");

       add_prop (OBJ_I_WEIGHT, 20);
       add_prop (OBJ_I_VOLUME, 40);
       add_prop (OBJ_I_VALUE,  130 + random(90));

    set_default_weapon(7, 7, W_KNIFE, W_IMPALE, W_ANYH);
}

