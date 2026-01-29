/*
 * Bracers worn by the Elf leader
 * They are a rare item made from the metal Galvorn
 * - Finwe, January 2018
 */

inherit "/std/armour";
inherit "/lib/keep";

#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <language.h>

#define AC  40
void
create_armour()
{
    set_name("bracers");
    add_name(({ "pair of bracers" }));
    set_adj(({"jet", "black"}));
    set_short("pair of jet black bracers");
    set_pshort("pairs of jet black bracers");
    set_pname("bracerses");
    set_long("This " + short() + " was made by the elves in ages long past. " +
        "They protect the arms and are crafted from a jet black metal. " +
        "They are decorated with spiral lines and patterns and were " +
        "likely made for royalty. The " + short() + " are crafted so " +
        "well that the armour doesn't show any signs of battle.\n");

    set_at(A_ARMS);
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
    add_prop(MAGIC_AM_MAGIC,({25, "enchantment"}));

    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC, A_ARMS));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 2);
    add_prop(OBJ_I_VALUE, 1200 + random(500));
}
