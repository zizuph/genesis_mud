inherit "/std/drink";
#include <stdproperties.h>

create_drink()
{
    set_name("water");
    set_pname("water");
    set_adj("pint of");
    set_short("pint of water");
    set_pshort("pints of water");
    set_long("This is some clear water, about a pint of it.\n");
    set_soft_amount(568);
    add_prop(OBJ_I_WEIGHT, 568);
    add_prop(OBJ_I_VOLUME, 568);
    add_prop(OBJ_I_NO_GET,
	"You can carry water in a container, but not pick it up with " +
	"your bare hands.\n");
    add_prop(OBJ_I_NO_DROP,
	"If you dropped the water, it would vanish in the ground " +
	"immediately.\n");
    add_prop(OBJ_I_NO_GIVE,
	"Nobody can keep so much water in his bare hands, so you " +
	"can't give it away.\n");
}
