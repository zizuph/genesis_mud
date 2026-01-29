#pragma strict_types

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

#define ARMOUR_CLASS 50

public void
create_armour()
{
    set_name("platemail");
    set_pname("platemails");
    set_adj("blue");
    set_adj("majestic");
    set_short("majestic blue platemail");
    set_pshort("majestic blue platemails");
    set_long("A majestic blue platemail. This body armour is very well " +
        "constructed. It is made of several heavily reinforced " +
        "metal plates made to conform to the contours of the body. " +
        "An inner lining of chainmail adds even more protection to " +
        "the wearer of this armour. The name 'Gorn Skahrn' is " +
        "stamped on the right breast plate.\n");
    set_ac(ARMOUR_CLASS);
    set_at(A_BODY);
    set_am( ({3,3,3}) );
    add_prop(OBJ_I_WEIGHT, 12000 + (random(50) -  25));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(25) + 1000);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 30, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO, ({ "The platemail seems to be enchanted " +
        "for better protection.", 40 }));
    add_prop(OBJ_S_WIZINFO, "Gorn's magic platemail. Not yet in the game.\n");
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
