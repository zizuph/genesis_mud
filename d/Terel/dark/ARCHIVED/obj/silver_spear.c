/*
 * Magical Spear wielded by the Captain of the Calathin Guard
 * Coded by Shinto 020700
 *
 * Modified: 30 Apr 2003, by Bleys
 *     - fixed a typo in the set_long()
 *
 */

#include "/d/Terel/include/Terel.h"
inherit STDWEAPON;
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name(({"spear","polearm"}));
    set_adj("wooden");
    set_adj("silver-tipped");
    set_short("wooden silver-tipped spear");
    set_pshort("wooden silver-tipped spears");
    set_long("A sturdy steel spear. The blade is about a foot long "+
             "and just close to three and a half inches wide. The shaft "+
             "is long and unadorned.\n");
    set_default_weapon(45, 50, W_POLEARM, W_IMPALE, W_BOTH, TO);
    add_prop(OBJ_I_WEIGHT, 4500);
    add_prop(OBJ_I_VALUE, 800);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({"enchantment", 60}));
    add_prop(OBJ_S_WIZINFO, "A powerful spear wielded by the Warrior of the "+
                   "Dark Elves. 45 hit, 50 pen. Does extra damage to all giants.\n");
    add_prop(MAGIC_AM_ID_INFO, ({"The "+short()+" is enchanted to be a potent "+
                   "weapon.\n", 25, 
                   "The "+short()+" holds the power to slay any race of giant.\n", 60}));

}


public varargs int
did_hit (int aid, string hdesc, int phurt, object enemy, int dt,
      int phit, int dam)
{
    object wielder;

    if ((phurt >= 0) &&
        (enemy->query_race_name() == "giant"))
    {
        wielder = query_wielded();
        enemy->heal_hp(- ((random(dam/2)) + dam / 3));
        enemy->catch_tell("The "+short()+" flashes silver as it "+
                     "connects with your body.\n");
        wielder->catch_tell("The "+short()+" flashes silver as it "+
            "connects with "+enemy->query_the_name(wielder) + ".\n");
        wielder->tell_watcher("The "+short()+" flashes silver as it connects "+
             "with "+QTNAME(enemy)+".\n", enemy);
    }

    return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}


