inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name("sandals");
    set_adj("leather");
    set_short("pair of leather sandals");
    set_pname("pairs of leather sandals");
    set_long("This is a pair of sandals made of leather and bleached by" +
	 " many hours use out in the sun. They are of simple construction" +
	     " with one single leather strap to keep the foot in place." +
	     " The sandals looks very well used but still comfortable.\n");
    set_at(A_FEET);
    set_am(({0, 0, 0}));
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 150);
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover();
}
void
init_recover(string arg)
{
    init_arm_recover(arg);
}
