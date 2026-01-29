/*
 * Greaves worn by the Elf leader
 * They are an alternative to the Galvorn armours, but still
 * a unique item
 * - Finwe, January 2018
 */

inherit "/std/armour";
inherit "/lib/keep";

#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <language.h>

#define AC  35
void
create_armour()
{
    set_name("greaves");
    add_name(({ "pair of greaves" }));
    set_adj(({"polished", "mithril"}));
    set_short("pair of polished mithril greaves");
    set_pshort("pairs of polished mithril greaves");
    set_pname("greaveses");
    set_long("This " + short() + " was forged by elves in Middle-earth. They are polished to a bright luster and shine in the light. They protect the legs and are etched with intricate designs.\n");
    set_at(A_LEGS);
    set_ac(AC);
    set_am(({0, 0, 0}));
    set_keep(1);

    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);

    add_prop(OBJ_S_WIZINFO,"This armour is rare and worn by the leader of " +
        "wandering elves in the Shire. No special features are implemented " +
        "into them.\n");
    add_prop(MAGIC_AM_ID_INFO,
        ({"This armour is made by the elves of Middle-earth. A strong " +
        "sense of power seems to radiate from it.", 10}));

    add_prop(MAGIC_AM_MAGIC,({45, "enchantment"}));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC, A_LEGS));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 2);
    add_prop(OBJ_I_VALUE, 1200 + random(500));
}
