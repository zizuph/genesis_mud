inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

void
create_weapon()
{
    set_name("knife");
    set_pname("knives");
    set_adj("dull");
    set_short("dull knife");
    set_pshort("dull knives");
    set_default_weapon(9, 11, W_KNIFE, W_IMPALE, W_ANYH);
    set_dull(2);
    set_corroded(2);
    set_long("This knife look rusty and very dull.\n");
    add_prop(OBJ_I_VOLUME, 180);
}

