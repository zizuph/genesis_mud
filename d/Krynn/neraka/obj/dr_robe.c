inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name("robe");
    set_default_armour(3, A_ROBE);
    add_adj("small");
    set_short("small robe");
    set_long("It's made of soft and thick material, but yet it's not " +
	"very heavy.\n");
    add_prop(OBJ_I_VOLUME, 4750);
}

