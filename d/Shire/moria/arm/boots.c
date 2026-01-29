/*
 * Plain mining boots from Moria
 * Finwe, January 2005
 */

#include "/d/Shire/sys/defs.h"
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit "/std/armour";
inherit "/lib/keep";

#define AC  15

create_armour() {
    add_name(({"pair","pair of boots", "boots"}));
    add_pname("pairs of boots");
    add_adj(({"steel","mining"}));
    set_short("pair of steel mining boots");
    set_pshort("pairs of steel mining boots");
    set_long("This pair of steel mining boots was forged by dwarves " +
        "many years ago. They are heavy duty and designed to assist " +
        "in mining and to protect the feet. Steel spurs pattern the " +
        "soles of the boots and the toe tips, but they have been worn " +
        "down and smooth.\n");
    set_default_armour(AC,A_FEET,({0,0,0}),0);
    set_af(TO);
    set_ac(5);
    add_prop(OBJ_I_WEIGHT,1000);
    add_prop(OBJ_I_VOLUME,1500);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(5)+random(10)+5);
    set_keep(1);
}


string query_recover()
{
    return MASTER + ":" + query_arm_recover();
}


void init_recover(string arg)
{
    init_arm_recover(arg);
}
