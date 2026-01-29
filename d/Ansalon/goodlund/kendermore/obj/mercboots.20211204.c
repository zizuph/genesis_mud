/* Boots for Jane the Mercenary, Gwyneth, June 1999 */

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("boots");
    set_pname(({"pairs of boots", "armours"}));
    add_name("pair of boots");
    set_adj("sharp");
    add_adj("steel-toed");
    set_short("steel-toed boots");
    set_pshort("pairs of steel-toed boots");
    set_long("The steel coverings on these boots have a sharp tip on them " + 
        "for extra damage while kicking. They reach mid-calf, and look " + 
        "well used.\n");
    set_ac(13);
    set_at(A_FEET);
    add_prop(OBJ_I_VOLUME, 300);
}
