/*
 * Common lightweight elven mail
 * by Finwe May 1998
 */
 
inherit "/std/armour";
 
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <language.h>
 
void
create_armour()
{
    set_name("mail");
    set_adj(({"light","elvish"}));
    set_short("light elvish mail");
    set_long("This "+short()+" is by the elves and is designed " +
        "to offer protection to its wearer. It is made of " +
        "interlocking rings and is lightweight and often worn " +
        "underneath clothing.\n");
 
    set_at(A_TORSO);
    set_ac(35);
    set_am(({0, 0, 0}));
 
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(5, A_TORSO));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 2);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(35) + 75 + random(125));
}
