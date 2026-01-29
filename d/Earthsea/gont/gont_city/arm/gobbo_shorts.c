#pragma strict_types

inherit "/std/armour";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_armour()
{
    set_name("shorts");
    add_name("pair of gobbo boxer shorts");
    set_pname("pairs of gobbo boxer shorts");
    add_name("pair of shorts");
    add_name("pair");
    add_pname("pairs");
    add_name("armour");
    set_short("filthy pair of gobbo boxer shorts");
    set_pshort("filthy pairs of gobbo boxer shorts");
    set_long("This is a pair of indescribably filthy "+
        "gobbo boxer shorts.\n");
    set_at(A_LEGS);
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 5);
}
