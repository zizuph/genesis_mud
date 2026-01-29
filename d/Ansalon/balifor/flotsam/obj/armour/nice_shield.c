inherit "/std/armour";
inherit "/lib/keep";

#include <wa_types.h>
#include <formulas.h>
#include "/d/Ansalon/common/defs.h"

public void
create_armour()
{
    set_name("shield");
    set_pname("shields");
    set_adj("oval");
    add_adj(({"steel"}));
    set_short("oval steel shield");
    set_pshort("oval steel shields");
    set_ac(40);
    set_at(A_SHIELD);
    set_am( ({0,0,0}) );
    set_af(TO);
    set_long("This is an oval steel shield, which should " +
             "offer fair protection to the skilled wearer. " +
             "The shield seems to have seen its share of combats.\n");
    add_prop(OBJ_I_VOLUME, 600);
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(25) );
}


public int *
query_shield_slots()
{
    return (::query_shield_slots() + ({ A_BODY, A_LEGS }) );
}
