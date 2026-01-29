/*
 * Greaves worn by the Elf leader
 * They are an alternative to the Galvorn armours, but still
 * a unique item
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

#define AC  25

create_armour()
{
    set_name("helmet");
    add_name("helm");
    set_adj(({"polished", "mithril"}));
    set_short("polished mithril helmet");
    set_long("This " + short() + " was forged by elves in Middle-earth. It is bowl shaped with the top coming to a point. The helmet encloses the whole head. The front is open with a retangle metal piece protecting the nose. It gleams in the light and decorated with intricate designs\n");
    set_ac(AC);
    set_am(({-1,1,0}));
    set_at(A_HEAD);
    set_keep(1);

    add_prop(OBJ_S_WIZINFO,"This armour is rare and worn by the leader of " +
        "wandering elves in the Shire. No special features are implemented " +
        "into them.\n");
    add_prop(MAGIC_AM_ID_INFO,
        ({"This armour is made by the elves of Middle-earth. A strong " +
        "sense of power seems to radiate from it.", 10}));
    add_prop(MAGIC_AM_MAGIC,({10, "enchantment"}));

    add_prop(OBJ_I_VALUE, 1000 + random(100));

    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC, A_HEAD));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 2);
    add_prop(OBJ_I_VALUE, 1000 + random(500));
}
