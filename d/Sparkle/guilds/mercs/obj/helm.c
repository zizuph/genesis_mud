inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>

#include "../merc.h"

public void
create_armour()
{
    set_name("helm");
    add_name(({"helmet","armour"}));
    set_pname("helms");
    add_pname(({"armours","helmets"}));
    set_adj("mercenary");
    add_adj(({"steel","black"}));
    set_short("black steel helm");
    set_pshort("black steel helms");
    set_ac(25);
    set_at(A_HEAD);
    set_am( ({-2,3,-1}) );
    set_long("The black steel helmet has an open face, but still "+
	"does an adequate job of protecting the wearer's head. At "+
	"the base of the neck, a small dragon has been etched into "+
	"the steel.\n");
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(25));
}
