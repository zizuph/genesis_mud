/* Runed Mithril Warhammer
 *
 * Coded by none other than Igneous! a.k.a. Chad Richardson
 *
 * This is an enchanted warhammer of strength wielded by
 * Khaaz the dwarven Trollslayer ~Shire/eastroad/eastern/npc/khaaz.c
 * A difficult weapon to get, but it's worth the troble considering the
 * power of the weapon.
 *
 * Modifications:
 *
 * 09/12/2003 Palmer removed impale. Why did a club have impale?
 */
inherit "/std/weapon";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include "/d/Shire/sys/defs.h"
#include <wa_types.h>

// Global Vars
static int gExtra_str;

void
create_weapon()
{
    set_name("warhammer");
    add_name(({"hammer", "club"}));
    set_short("runed mithril warhammer");
    set_adj(({"runed","mithril"}));
    set_long("This "+short()+" is wonderfully balanced and extremely "+
      "light for a warhammer.  Made of what must be mithril silver, "+
      "this warhammer has a aura of enchantment.  You notice "+
      "a pair of runes which adorn the shaft of this weapon.\n");

    add_item(({"runes", "rune", "shaft"}),
      "Ancient runes picturing a towering figure cover the shaft of "+
      "the "+ short()+".\n");

    set_hit(42);
    set_pen(47);
    set_pm(({2,0,-2}));
    set_wt(W_CLUB);
    // set_dt(W_IMPALE | W_BLUDGEON);
    set_dt(W_BLUDGEON);
    set_wf(TO);
    set_hands(W_LEFT);
    set_likely_break(0);
    set_likely_dull(2);
    set_likely_corr(2);

    // Half normal weight
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(query_hit(), W_CLUB) / 2);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT));
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(query_hit(),query_pen()) + 200 + random(100));
    add_prop(MAGIC_AM_MAGIC,({60,"enchantment",
	20,"enhancement"}));
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
    add_prop(MAGIC_AM_ID_INFO,({"This warhammer is enchanted.",1,
	"It has the ability to enhance the wielder.",20,
	"Forged by Dwarven smiths the warhammer has been "+
	"blessed by Tulkas himself.",40,
	"Tulkas blessing is one that enhances the wielder with "+
	"great strength.",50}));
    add_prop(OBJ_S_WIZINFO,"This "+short()+" is a warhammer of "+
      "strength which increases the wielders strength by "+
      "this formula:  "+
      "MIN(5, MAX(15, (wielder->query_stat(SS_INT) / 10))) "+
      "The more intelligent you are the more atuned to the "+
      "weapon you are, so you get a bigger bonus to your strength "+
      "from wielding it.\n");
}

mixed
wield(object wep)
{
    object player = ENV(TO);

    gExtra_str = MAX(5, MIN(15, player->query_stat(SS_INT) / 10));
    player->set_stat_extra(SS_STR, 
      player->query_stat_extra(SS_STR) + gExtra_str); 
    return 0;
}

mixed
unwield(object wep)
{
    query_wielded()->set_stat_extra(SS_STR, 
      query_wielded()->query_stat_extra(SS_STR) - gExtra_str);
    gExtra_str = 0;
    return 0;
}

string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + query_keep_recover();
}

void
init_recover(string arg)
{
    init_wep_recover(arg);
    init_keep_recover(arg);
}
