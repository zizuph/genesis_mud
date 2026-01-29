/* head_hid: A piece of hide headwear.... */
inherit "/d/Kalad/std/armour";
#include <wa_types.h>
#include "defs.h"

void create_armour()
{
    ::create_armour();
    set_name("hat");
    set_short("hide hat");
    set_long("This extremely thick hat is probably made from the skin "+
             "of a large reptile. The scaley surface is good at keeping "+
             "out the sun, dust, and even some attacks.\n");
    set_adj("hide");

    set_ac(20);
    set_am(({ -4,  1,  2}));
    set_at(A_HEAD);

    add_prop(OBJ_I_WEIGHT, 900);
    add_prop(OBJ_I_VOLUME, 450);
}
