/*
 *  IGARD_ARM + "i_shoes.c"
 *  Standard Isengard Shoes
 *
 *    Last modified by Alto, 07 October 2001
 *
 */

#pragma strict_types

inherit "/std/armour";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"
#include "../igard_defs.h"

mixed    wear(object what);
mixed    remove(object what);

int worn;

void
create_armour()
{
    set_name("shoes");
    add_name(({ "pair of iron-shod shoes" }));
    set_pname("shoeses");
    set_adj("iron-shod");
    add_adj("iron");
    set_short("pair of iron-shod shoes");
    set_pshort("pairs of iron-shod shoes");
    set_long("The pair of iron-shod shoes stinks of orc, but otherwise "
        + "looks fairly sound. Huge iron nails are driven into the soles, "
        + "ensuring that they do not wear out during long marches.\n");
    add_item(({"nail", "nails", "iron nails"}), "Iron nails are driven "
        + "into the soles of the iron-shod shoes.\n");
    add_item(({"sole", "soles"}), "The soles of the iron-shod shoes "
        + "have huge iron nails driven into them.\n");

    set_default_armour(10, A_FEET, ({ 1, 1, -2 }), 0);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(10, A_FEET));
    add_prop(OBJ_I_VOLUME, 1000); 
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(20)+random(100)-50);
    add_prop(IGARD_ARMOUR, 1);
    set_af(TO);
    seteuid(getuid(TO));

}


mixed
wear(object what)
{
    if (what != TO)
        return 0;

    write("You pull the pair of iron-shod shoes onto your feet. They stink, "
        + "but seem otherwise quite comfortable.\n");
    say(QCTNAME(TP) + " pulls " + TP->query_possessive() + " pair of iron-shod "
        + "shoes onto " + TP->query_possessive() + " feet.\n");

    worn = 1;
    return 1;
}

mixed
remove(object what)
{
    object wearer = query_worn();

    if (what != TO || !TP)
        return 0;

    if (wearer->query_hp() == 0)
        {
        worn = 0;
        return 1;
        }

    wearer->catch_tell("You slip your feet out of the pair of iron-shod "
        + "shoes.\n"); 
    tell_room(environment(wearer), QCTNAME(wearer) 
       + " slips " + POSSESSIVE(wearer) + " feet out of "
        + "the pair of iron-shod shoes.\n", 
        ({wearer}));

    worn = 0;
    return 1;
}


