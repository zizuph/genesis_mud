/*
 * ????? made this Sep 6 2003
 * 
 * Cotillion added this header while fixing the wield code.
 */
inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

static int alarm_id;

void
create_weapon()
{
    set_name(({"warhammer","hammer"}));
    add_name("weapon");
    add_name("club");
    add_name("enforcer");
    set_pname("warhammers");
    set_adj("nordmaarian");
    set_short("nordmaarian warhammer");
    set_pshort("nordmaarian warhammers");
    set_long("This warhammer is of exotic Nordmaarian design. It has a thin handle " +
        "of iron with a heavy wooden head crafted into the visage of a snarling wolf. " +
        "Elaborate markings run down one side of the handle, shimmering brightly.\n");
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({ 10, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({"This warhammer, the Enforcer, was crafted by a renegade " +
        "shaman of the Great Moor for the High King of the Wastes during the Age of Darkness. " +
        "During these turbulent times a champion was needed to bring order to chaos, and this " +
        "weapon was forged for this purpose. This warhammer is more effective for those devoted " +
        "to a cause whether it be good or evil, and so is more effective in the hands of those " +
        "committed to one side or another. This warhammer loathes chaos, and will not allow " +
        "those heavily tainted by the Greygem of Gargath to wield it.\n", 50}));

    add_item("markings","In the barbaric Nordmaarian tongue, you manage to make out the words " +
        "'Enforcer'.\n");
    set_default_weapon(34,34,W_CLUB, W_BLUDGEON,W_ANYH);

    set_wf(TO);

    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(35,35));
}


void
default_wield()
{
    int align_bonus;
    object who;
    
    /* If the wielder is dead or etc we abort */
    who = query_wielded();
    if (!who)
        return;

    align_bonus = ABS(who->query_alignment() / 100);

    who->catch_tell("For some reason you get the strange feeling that the " +
        "nordmaarian warhammer has just evaluated you and your cause.\n");
    
    set_hit(34 + align_bonus);
    set_pen(34 + align_bonus);
    who->update_weapon(TO);
}



mixed
wield(object what)
{
    if (TP->query_race_name() == "kender" || 
        TP->query_race_name() == "minotaur" ||
        TP->query_race() == "dwarf")
        return "A voice booms in your head: You will not wield me, " + 
            "spawn of the Greygem!\n";
    
    alarm_id = set_alarm(1.0, 0.0, default_wield);
    return 0;
}


mixed
unwield(object what)
{
    set_hit(34);
    set_pen(34);
    
    /* Omission of update_weapon is deliberate, attack is to be 
     * removed anyway */
    
    if (get_alarm(alarm_id))
        remove_alarm(alarm_id);
    
    return 0;
}
