inherit "std/armour.c";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("robes");
    add_name("robe");
    set_pname("robes");
    set_short("tattered, rotted robes");
    add_adj(({"tattered", "rotted"}));
    set_ac(6);
    set_at(A_ROBE);
    set_condition(4);
    set_long("These robes must have once been a simple, yet clean and "+
	"protecting, piece of clothing. Now, they are not much more than "+
	"a collection of rags still held together by a piece or two of "+
	"thread.\n");

    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_VALUE,   90);
}
