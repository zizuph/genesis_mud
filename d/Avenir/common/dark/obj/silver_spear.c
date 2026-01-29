/*
 * Magical Spear wielded by the Captain of the Calathin Guard
 * Coded by Shinto 020700
 *
 * Modified: 30 Apr 2003, by Bleys
 *     - fixed a typo in the set_long()
 *
 * Lucius May 2009: Cleaned and updated, moved from /d/Terel/dark/
 */
#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>

public void
create_weapon(void)
{
    set_keep(1);
    set_name(({ "spear","polearm" }));
    set_adj(({ "wooden", "silver-tipped" }));
    set_short("wooden silver-tipped spear");
    set_pshort("wooden silver-tipped spears");
    set_long("A sturdy steel spear. The blade is about a foot long "+
	"and just close to three and a half inches wide. The shaft "+
	"is long and unadorned.\n");

    set_default_weapon(45, 50, W_POLEARM, W_IMPALE, W_BOTH, this_object());

    add_prop(OBJ_I_VALUE, 800);
    add_prop(OBJ_I_WEIGHT, 4500);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({"enchantment", 60}));
    add_prop(MAGIC_AM_ID_INFO, ({
	"The "+short()+" is enchanted to be a potent weapon.\n", 25,
	"The "+short()+" holds the power to slay any race of giant.\n", 60
    }));
    add_prop(OBJ_S_WIZINFO, "A powerful spear wielded by the Warrior of the "+
	"Dark Elves. 45 hit, 50 pen. Does extra damage to all giants.\n");
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
	int phit, int dam, int hid)
{
    if ((phurt >= 0) &&
	(enemy->query_race_name() == "giant"))
    {
        enemy->heal_hp(-(random(dam / 2) + (dam / 3)));

        wielder->catch_tell("The "+short()+" flashes silver as it "+
            "connects with "+enemy->query_the_name(wielder) + ".\n");
        enemy->catch_tell("The "+short()+" flashes silver as it "+
                     "connects with your body.\n");
        wielder->tell_watcher("The "+QSHORT(this_object())+
	    " flashes silver as it connects with "+
	    QTNAME(enemy)+".\n", enemy);
    }

    return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam, hid);
}

