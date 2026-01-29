/*
 * Common elven helmet
 * By Finwe, Frebruary 2002
 */

#pragma save_binary
 
inherit "/std/armour";
inherit "/lib/keep";

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <language.h>

create_armour()
{
    set_name("helmet");
    add_name("helmet");
    set_short("ancient elven helmet");
    set_long("This ancient helmet was forged ages ago by elves. " +
        "Made of steel, the helmet is durable and seems to be " +
        "untouched by the ravages of war and protects the head " +
        "from blows during battle.\n");
    set_ac(35);
    set_am(({-1,1,0}));
    set_at(A_HEAD);
    set_keep(1);

    add_prop(OBJ_I_VALUE, 1000 + random(100));

    add_prop(OBJ_I_WEIGHT,3000);
    add_prop(OBJ_I_VOLUME,3000);
}
