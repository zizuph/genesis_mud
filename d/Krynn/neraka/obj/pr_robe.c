/* Evil priest robe */

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name("robe");
    set_adj("black");
    add_adj("dark");
    set_short("black dark robe");
    set_long("The black colour on this robe symbolizes the evil of its " +
	"bearer.\n");
    set_default_armour(8, A_ROBE, ({ 1, 3, -4}));

    add_prop(OBJ_I_VOLUME, 530);
}
