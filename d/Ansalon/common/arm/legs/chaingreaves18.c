/* Ashlar, 9 Jun 97 - chainmail greaves */

inherit "/std/armour";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("greaves");
    add_name("pair");
    set_pname("greaves");
    add_pname("pairs");
    add_pname("armours");
    set_adj("chainmail");
    add_adj("chain");
    add_adj("mail");
    set_short("pair of chainmail greaves");
    set_pshort("pairs of chainmail greaves");
    set_ac(18);
    set_at(A_LEGS);
    set_long("The greaves protect the legs of the wearer with a layer of chain " +
        "mail on soft leather.\n");
    add_prop(OBJ_I_VOLUME, 1200);
    set_am(({-1,2,-1}));
}

