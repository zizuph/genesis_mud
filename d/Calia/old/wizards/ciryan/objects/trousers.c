inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_pname("pairs of trousers.");
    set_name("trousers");
    set_adj("short");
    set_adj("linen");
    set_short("pair of linen trousers");
    set_long("This is a pair of grey linen trousers, very bleached by frequent" +
    " use out in the sun. The legs are short, ending just below the knee." +
	  " They seem to be well used and repaired many times. A piece of" +
	     " rope is used as belt keeping them up.\n");
    set_at(A_LEGS);
    set_ac(15);
    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VOLUME, 400);
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
