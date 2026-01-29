/* Pair of leather pants for Maen, Gwyneth, June 1999 */

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("pants");
    set_adj("leather");
    set_short("pair of leather pants");
    set_pshort("pairs of leather pants");
    set_long("These are a pair of stiff leather pants. Black " + 
        "charcoal markings are smeared here and there. They look like " + 
        "they give decent enough protection.\n");
    set_ac(8);
    set_at(A_LEGS);
    set_am(({0,1,-1}));
    add_prop(OBJ_I_VOLUME, 150);
}

