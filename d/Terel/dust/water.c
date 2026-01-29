inherit "/std/drink";
#include <stdproperties.h>

create_drink()
{
    set_name("water");
    set_pname("water");
    set_adj("gallon of");
    set_short("gallon of water");
    set_pshort("gallons of water");
    set_long("This is about a gallon - nearly 4l - of clear water.\n");
    set_soft_amount(3785);
    add_prop(OBJ_I_WEIGHT, 3785);
    add_prop(OBJ_I_VOLUME, 3785);
    add_prop(OBJ_I_NO_GET,
	"You can carry water in a container, but not pick it up with " +
	"your bare hands.\n");
    add_prop(OBJ_I_NO_DROP,
	"If you dropped the water, it would vanish in the ground " +
	"immediately.\n");
    add_prop(OBJ_I_NO_GIVE,
	"Nobody can keep a gallon of water in his bare hands, so you " +
	"can't give it away.\n");
}
