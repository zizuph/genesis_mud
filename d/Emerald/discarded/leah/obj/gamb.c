inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void
create_armour()
{
        set_name("gambeson");
        set_short("bright gambeson");
        set_long("This gambeson is simply a padded leather "+
		"shirt that has been brightly dyed.\n");
        set_adj("bright");

        set_ac(8);
        set_at(A_BODY);
     set_am(({       -1,      0,      1 }));
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
