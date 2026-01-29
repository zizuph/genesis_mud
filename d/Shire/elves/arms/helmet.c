/*
 * Greaves worn by the Elf leader
 * This is the basic armour worn by the elves who travel.
 * They are not magical
 * - Finwe, January 2018
 */
#pragma save_binary
 
inherit "/std/armour";
inherit "/lib/keep";

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <language.h>

#define AC  20

create_armour()
{
    set_name("helmet");
    add_name("helm");
    set_adj(({"plain", "high-steel"}));
    set_short("plain high-steel helmet");
    set_long("This " + short() + " was forged by elves in Middle-earth. It is bowl shaped with the top coming to a point. The helmet encloses the whole head. The front is open with a retangle metal piece protecting the nose. It is made of extra hard steel and is plain and unadorned. \n");
    set_ac(AC);
    set_am(({-1,1,0}));
    set_at(A_HEAD);
    set_keep(1);

    add_prop(OBJ_I_VALUE, 1000 + random(100));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC, A_HEAD));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 2);
    add_prop(OBJ_I_VALUE, 1000 + random(500));
}
