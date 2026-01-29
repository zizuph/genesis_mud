/* 
 * Ancient gleaming axe, it is wielded by the wandering elf leader.
 * Finwe, February 2018
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
    set_name("axe");

    set_short("ancient gleaming axe");
    set_adj(({"ancient","gleaming"}));
    set_long("This " + short() + " is made of mithril. It was forged " +
        "by elves in ancient times and is wonderully balanced. It is " +
        "lightweight despite its size. and its double blades looks " +
        "like they could slice through anything.\n");

    set_hit(42);
    set_pen(47);
    set_pm(({0,0,0}));
    set_wt(W_AXE);
    set_dt( W_SLASH | W_BLUDGEON);
    set_wf(TO);
    set_hands(W_LEFT);

    // Half normal weight
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(query_hit(), W_AXE) / 2);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT));
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(query_hit(),query_pen()) + 200 + random(100));
    add_prop(MAGIC_AM_MAGIC,(50,"enchantment"));
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON,1);

    add_prop(MAGIC_AM_ID_INFO,({"This axe is enchanted.",1,
    	"It has the ability to enhance the wielder.",20,
	    "It was forged by the elves of in ancient times.",40,
    	"It was carried out of Gondolin when that great city fell.",50}));

    add_prop(OBJ_S_WIZINFO,"This "+short()+" increases the wielder's " +
        "strength based on their dex. The higher their dexterity, the " +
        "greater ther strength wehn wielded.\n");

}

mixed
wield(object wep)
{
    object player = ENV(TO);

    gExtra_str = MAX(5, MIN(15, player->query_stat(SS_DEX) / 10));
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
