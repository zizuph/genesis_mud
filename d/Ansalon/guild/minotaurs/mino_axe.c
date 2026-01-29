// Strength calculations borrowed from Middle Earth's Khaaz.
// Who wields one-handed weapon with this strength calculation.
// This weapon is a two handed weapon with no other benefits.

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Ansalon/common/defs.h"

inherit "/std/weapon";

int gExtra_str = 0;

create_weapon()
{
    set_name("axe");
    add_name("waraxe");
    add_adj("well-balanced");
    add_adj("steel");
    add_adj("metal");
    set_short("well-balanced steel waraxe");
    set_long("Black carvings adorn the long shaft of this two-handed axe. "+
             "As you turn the axe you can see the carvings is of a minotaur raising " +
             "a two handed axe above his falling enemy. The weight of the weapon is "+
             "well balanced which, in addition to the carvings, prove that this weapon "+
             "was crafted by an expert.\n");

    set_default_weapon(50, 50, W_AXE, W_SLASH | W_BLUDGEON, W_BOTH);

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 80, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO, ({"This expertly forged blade was once given to a legendary " +
                                 "minotaur warrior Klarf by Gjuldar, cleric of the Holy Order " +
                                 "of the Stars. The enchantment it holds is said to offer the " +
                                 "wielder additional strength when he needs it. As you further " +
                                 "inspect the weapon you cannot help but notice "+
                                 "a strong detest of your magic presense.\nThe only thing the magic "+
                                 "of this axe hate more than magic is dwarves. The hated run deep due "+
                                 "to the many years of enslavement of the minotaur race.\n", 70}));
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_I_WEIGHT, 13500);
    set_wf(TO);
}

void melt_axe(object axe)
{
    axe->remove_object();
}

mixed
wield(object what)
{

    if(TP->query_skill(SS_SPELLCRAFT) > 20 || TP->query_race_name()=="dwarf")
    {
	TP->catch_msg("You feel a strong surge of power emitting from the "+short()+" as you " +
                      "attempt to wield it. It melts in your hands, burning you horribly!\n");
        TP->heal_hp(-300-random(200));
	tell_room(environment(TP), QCTNAME(TP) + "'s "+short()+" seems to melt away in "+HIS(TO)+" hands!\n", TP);
        
	if(TP->query_hp() <= 0)
	{
	    TP->do_die(TO);
	}
        set_alarm(1.0, 0.0, &melt_axe(this_object()));
	return 1;
    }
    object player = environment(this_object());

    gExtra_str = MAX(5, MIN(15, player->query_stat(SS_STR) / 10));
    player->set_stat_extra(SS_STR, player->query_stat_extra(SS_STR) + gExtra_str); 
    return 0;
}

mixed
unwield(object what)
{
    query_wielded()->set_stat_extra(SS_STR, 
                                    query_wielded()->query_stat_extra(SS_STR) - gExtra_str);
    gExtra_str = 0;
    return 0;
}
