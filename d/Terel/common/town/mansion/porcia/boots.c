#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;

#include <stdproperties.h>
#include <wa_types.h>

public void
create_terel_armour()
{
    set_name("pair of boots");
    add_name("boots");
    set_pname("pairs of boots");
    add_pname("boots");
    set_adj("silver");
    add_adj("shiny");
    set_short("pair of shiny silver boots");
    set_pshort("pairs of shiny silver boots");
    set_long("This pair of boots are made of polished silver.\n");
    set_ac(15);
    set_at(A_LEGS);
    set_am(({0, 0, 0}));
    set_armour_size(MEDIUM);
}
