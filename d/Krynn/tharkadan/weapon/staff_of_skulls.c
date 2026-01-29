inherit "/std/weapon";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";

#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Krynn/common/defs.h"

int default_spellpen = 40;

void
create_weapon()
{
    set_name("staff");
    add_adj("skull");
    add_adj("onyx");
    set_short("staff of skulls");
    set_long("This impressive staff consists of one long rod of onyx, webbed " +
        "with intricate spidery carvings inlaid with silver. Clasped atop the " +
        "staff are three crystal skulls, crackling with violet energy.\n");

    add_item(({"spidery carvings"}), "Spidery carvings of a language you " +
        "do not recognise cover the length of the onyx staff.\n");
    add_item(({"crystal skulls", "violet energy"}),
        "Clasped atop the onyx staff are three small crystal skulls frozen " +
        "in a terrified rictus. Violet energy crackles between them.\n");

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({50,"enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({"Summoned from the core of the Life-Tree of " +
        "Thorbardin a millenia ago by the dwarven Theiwar clan magi, this " +
        "staff enhances the spellcasting power of skilled practitioners " +
        "when held... but at a cost to their health or mental energies.\n", 25 }));

    add_prop(OBJ_S_WIZINFO, "This staff, when wielded by someone with 75+ " +
        "SS_SPELLCRAFT skill, provides a spellpower to the wielder ranging " +
        "from 51 to 59. When wielded, it will drain either 20% of the wielder's " +
        "health or mana.\n");

    set_magic_spellpower(default_spellpen);

    set_wf(TO);
    set_default_weapon(40, 20, W_POLEARM, W_BLUDGEON, W_BOTH);
    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(40, W_POLEARM));
}


void
decide_spellpower()
{
    int spellpen;
    object who = query_wielded();

    if (!objectp(who))
	return;

    if(who->query_skill(SS_SPELLCRAFT) < 75)
    {
        set_magic_spellpower(default_spellpen);
        who->update_weapon(TO);
        return;
    }

    if(random(2))
    {
        who->catch_tell("The onyx haft of the staff of skulls seems to " +
           "draw heavily on your mental energies as you grasp it.\n");
        who->add_mana( -(who->query_max_mana() / 5) );
    }
    else
    {
        who->catch_tell("The onyx haft of the staff of skulls seems to " +
           "draw heavily on your life force as you grasp it.\n");
        who->heal_hp( -(who->query_max_hp() / 5) );
    }

    spellpen = min(59, 26 + who->query_skill(SS_SPELLCRAFT) / 3);
    set_magic_spellpower(spellpen);
    who->update_weapon(TO);
}
 
mixed
wield(object what)
{
    set_alarm(1.0, 0.0, decide_spellpower);
    return 0;
}

void 
appraise_object(int num)
{
    ::appraise_object(num);
    write(item_spellpower_desc());
}

string 
stat_object() 
{
    return ::stat_object() + stat_object_spellpower();
}