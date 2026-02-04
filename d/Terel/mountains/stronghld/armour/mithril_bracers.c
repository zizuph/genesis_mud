/*
 * bracers for stronghold.
 * Tomas  -- Jan 2000
 */


#include <wa_types.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

public void
create_terel_armour()
{
    set_name("bracers");
    set_short("pair of mithril bracers");
    set_adj(({"mithril", "leather"}));
    set_long("A pair of mithril bracers, light weight yet, provides " +
       "some decent protection.\n");

    set_default_armour(20, A_ARMS, 0, 0);
    set_armour_size(SMALL);
    
    add_prop(OBJ_I_VALUE,            100);
    add_prop(OBJ_I_WEIGHT,          350);
}
