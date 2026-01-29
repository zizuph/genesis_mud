inherit "/std/armour";
#include "/d/Raumdor/defs.h"
/* Vision's Armour, by Sarr */

void
create_armour()
{
    ::create_armour();
    set_name("platemail");
    set_adj("black");
    add_adj("steel-spiked");
    set_short("black steel-spiked platemail");
    set_long("This is a blackened platemail with nasty looking spikes "+
        "protruding around the shoulder areas.\n");
    set_ac(40);
    set_at(A_BODY | A_ARMS);
    add_prop(OBJ_I_WEIGHT,9000);
    add_prop(OBJ_I_VOLUME,8600);
    add_prop(OBJ_I_VALUE,120);
}
