#pragma strict_types

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

#define ARMOUR_CLASS 32

public void
create_armour()
{
    set_name("platemail");
    set_pname("platemails");
    set_adj("shiny");
    set_adj("steel");
    set_short("shiny steel platemail");
    set_pshort("shiny steel platemails");
    set_long("This platemail is standard issue for the elite Gont guards," +
        " a seal on left breast plate indicates this." +
        " It has been polished and brightened to reveal the shining" +
        " colour of the steel. It is made of many plates that" +
        " overlap each other, covering a inner lining of chainmail." +
        " It is well constructed and it seems to be able to offer a" +
        " great deal of protection to its wearer.\n");
    set_ac(ARMOUR_CLASS);
    set_at(A_BODY);
    set_am( ({1,1,1}) );
    add_prop(OBJ_I_WEIGHT, 12600 + (random(50) -  25));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(25) - 10);
}

public string
query_recover()
{
    return MASTER + ":" + query_arm_recover();
}

public void
init_recover(string arg)
{
    init_arm_recover(arg);
}
