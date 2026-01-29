#pragma strict_types

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_armour()
{
    set_name("collar");
    set_pname("collars");
    set_adj(({"leather", "silver-spiked"}));
    set_short("leather silver-spiked collar");
    set_pshort("leather silver-spiked collars");
    set_long("A leather silver-spiked collar, worn by "+
        "the guards of the priestess. It fits tightly around the "+
        "neck and there appears to be a metal loop on one side for "+
        "attaching a leash.\n");
    set_default_armour(10, A_NECK);
    add_prop(OBJ_I_VALUE, 150);
    add_prop(OBJ_I_WEIGHT, 120);
    add_prop(OBJ_I_VOLUME, 100);
}
