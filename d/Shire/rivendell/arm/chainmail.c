/*
 * Common elven chainmail
 * by Finwe May 1998
 *
 * 1999/05/06 Last update
 * 2011/07/25 Lavellan - Added MAGIC_AM_MAGIC needed for magic armour.
 */
 
inherit "/std/armour";
inherit "/lib/keep";
 
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <language.h>
 
void
create_armour()
{
    set_name("chainmail");
    set_adj(({"silver","elven"}));
    set_short("elven silver chainmail");
    set_long("This "+short()+" appears strong with its many " +
        "interlocking rings. It is made by elves and offers " +
        "protection from battles. Unlike most armours you have " +
        "seen, this one looks as if it has never seen a battle " +
        "as it is in excellent condition.\n");
 
    set_at(A_TORSO);
    set_ac(35);
    set_am(({0, 0, 0}));
    set_keep(1);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
 
    add_prop(OBJ_S_WIZINFO,
        "This armour is the common armor worn by the elves in " +
        "Imladris. No specials associated other than improved " +
        "protection.\n");
 
    add_prop(MAGIC_AM_MAGIC, ({35, "enchantment"}) );
 
    add_prop(MAGIC_AM_ID_INFO,
        ({"This "+short()+" was forged by the ancient elves of " +
        "Middle-earth. A strong sense of power seems to " +
        "radiate from it.", 20}));
 
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(20, A_TORSO));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 2);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(35) + 75 + random(125));
}
