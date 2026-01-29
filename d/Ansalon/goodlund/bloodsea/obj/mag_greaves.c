/* created by Arman, 29/05/04 
* These magical greaves increases the dex
* of those who can wear it by 10 points.
*/

/*
 * Navarre August 13th 2008.
 * Changed the greaves so all alignments can wear them.
 * It's the best pair of greaves in the realm currently,
 * and we like to make it more fair.
 */

inherit "/std/armour";
inherit "/lib/keep";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include "/d/Ansalon/common/defs.h"

object wearer;

void
create_armour()
{
    set_name("greaves");
    add_name("armour");
    set_adj("red");
    add_adj("runed");
    add_adj("red-runed");
    set_short("pair of red-runed greaves");
    set_pshort("pairs of red-runed greaves");
    set_long("These heavy greaves seem to be roughly carved from thick obsidian, " +
       "with jagged spikes jutting out at all angles. Pulsing like lines of magma " +
       "are fiery red runes, that glow malevolently.\n");
    set_at(A_LEGS);
    set_ac(45);
    set_af(TO);

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_ID_INFO,
      ({"These greaves were forged in the upper levels of the Abyss. " +
        "This pair is enchanted to offer great " +
        "protection to the legs as well as to make one more " +
        "dexterous.\n",70}));
    add_prop(MAGIC_AM_MAGIC,({10,"enchantment"}));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(45, A_LEGS));
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(45));

}

void
wear_message()
{
    if(E(TO) != wearer)
	return;

    wearer->catch_msg("A burst of dark energy " +
                      "runs through your legs, making you feel more dexterous.\n");

    tell_room(E(wearer),QCTNAME(wearer)+
              " crouches suddenly like a predator, then straightens " +
              "gracefully.\n", wearer);
}

mixed
wear(object what)
{
    //    if(TP->query_alignment() > -200)
    //        return "The red-runed greaves glow malevolently, contracting so " +
    //        "that you are unable to wear them.\n";

    TP->set_stat_extra(SS_DEX, (TP->query_stat_extra(SS_DEX) + 10));

    wearer = TP;
    set_alarm(0.5, 0.0, "wear_message");
    return 0;
}

mixed
remove(object what)
{
    if (wearer)
        wearer->set_stat_extra(SS_DEX, (TP->query_stat_extra(SS_DEX) - 10));

    wearer = 0;
    return 0;
}

void
leave_env(object ob, object from)
{
    if (wearer)
        remove(this_object());

    ::leave_env(ob, from);
}

