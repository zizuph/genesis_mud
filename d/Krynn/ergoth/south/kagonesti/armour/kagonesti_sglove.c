#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>

inherit "/std/armour";

void create_armour()
{
    set_name("glove");
    set_adj("shooting");
    set_short("shooting glove");
    set_long("This glove serves as protection for an archer's fingers. It "
        + "reduces the pressure and friction of a bowstring, allowing the "
        + "archer to draw and anchor an arrow without as much pain.\n");
    
    set_ac(4);
    set_at(A_R_HAND);
    set_am(({0, 1, -1}));
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(4) + 500);
}

public mixed command_wear()
{
    mixed result;
    
    if(1 != (result = ::command_wear()))
        return result;

    this_player()->set_skill_extra(SS_WEP_MISSILE,
        this_player()->query_skill_extra(SS_WEP_MISSILE) + 5);

    return 1;
}

public mixed command_remove()
{
    mixed result;

    if(1 != (result = ::command_remove()))
        return result;

    this_player()->set_skill_extra(SS_WEP_MISSILE,
        this_player()->query_skill_extra(SS_WEP_MISSILE) - 5);

    return 1;
}

