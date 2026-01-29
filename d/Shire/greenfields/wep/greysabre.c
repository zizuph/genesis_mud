/*
 * Dull Grey Sabre
 * by Jaypeg Brandybuck aka Peter Lambert
 * March 2000
 *
 * This is an attempt at a true cavalry weapon, a heavy and
 * effective sword for hacking at people from horseback.
 *
 * Does extra damage when wielder is mounted.
 * On a random(12)>4, it will do additional damage.
 * Extra damage goes from 133%, 150% to maximum 200%
 *
 * Added check for skill/wisdom req.
 *
 * Removed the magical properties since this complements the JBS
 * when that sword isn't cloned. Original hit/pen was 41/49,
 * respectively. Reduced weight of sword, and min wield requirement
 * from 57 to 50.
 * -- Finwe, February 2001
 *
 *
 */

inherit "/std/weapon";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <options.h>
#include <macros.h>
#include <filter_funs.h>
#include <tasks.h>
#include "/d/Shire/sys/defs.h"

#define MIN_WIELD 50

// Global Vars
int     given_away;
string  dropped_by_wiz,
        cloned_by_wiz;


void
create_weapon()
{
    set_name("sabre");
    set_pname("sabres");
    add_name(({"sword"}));
    set_short("dull grey sabre");
    set_adj(({"dull","grey"}));
    set_long(
      "This "+short()+" is a heavy, single-edged sword with a "+
      "gently curving blade, a style favoured by cavalry "+
      "warriors for its superior strength and penetration from "+
      "horseback. Contrary to most weapons, the blade has a "+
      "dull grey finish, and the hilt, gleaming and polished.\n");

    add_item(({"blade", "grey blade"}),
      "The blade of this "+short()+" is typical of a sabre style, "+
      "a long and gently curving blade on the convex side, and a "+
      "thick and heavy spine on the concave. The blade's finish "+
      "is dull, grey, and almost porous; unadorned save for a few "+
      "tiny Tengwar at the tang.\n");
    add_item(({"tang","letters","tengwar","elven letters"}),
      "You believe the intricate Tengwar lettering spells the word "+
      "'crist'.\n");
    add_item(({"hilt","polished hilt","gleaming hilt"}),
      "The finish of the hilt is unlike that of the blade, being "+
      "polished to a gleam, and a mirror-like surface. Like the "+
      "blade, the metal used is not obvious. You notice the "+
      "absence of any battle marks or nicks.\n");

    set_hit(58);
    set_pen(37);
    set_pm(({3,0,1}));
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
    set_wf(TO);
    set_hands(W_ANYH);
    set_likely_break(0);
    set_likely_dull(1);
    set_likely_corr(1);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(query_hit(),query_pen()) - random(200));
    add_prop(OBJ_I_VOLUME,1041);
    add_prop(OBJ_I_WEIGHT,6500);

    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
    add_prop(MAGIC_AM_ID_INFO,({"This sabre is enchanted.",1,
        "It has superior penetration.",20,
        "The weapon is most effective from horseback.",40}));
    add_prop(OBJ_S_WIZINFO,"This "+short()+" is enchanted to enhance "+
        "its already effective penetration when the wielder is mounted.\n");
}


public varargs int
did_hit (int aid, string hdesc, int phurt, object enemy, int dt,
      int phit, int dam)
{
    object wielder;
    string mounted;

    wielder = query_wielded();
    mounted = wielder->query_prop("_live_o_steed");

    if ((phurt > 0) && (mounted) && (random(12) > 4))
    {
      enemy->heal_hp(-(dam / (random(3)+1) ));
    }

    return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}

mixed
wield(object what)
{

    int success;

    /* Broken */
    if (query_prop(OBJ_I_BROKEN))
        return "It is of no use, the blade is too far gone.\n";

    /* Stat checks */
    success = TP->query_stat(SS_WIS) / 3;
    success += TP->query_skill(SS_WEP_SWORD) / 3;
    if (success < MIN_WIELD && TP->query_race() != "orc")
        return "You do not feel confident enough to wield this "+
               "weighty and awkward blade.\n";

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

void
enter_env(object to, object from)
{
  ::enter_env(to, from);
  seteuid(getuid(this_object()));
  if (!from && TP->query_wiz_level()) {
    cloned_by_wiz = CAP(TP->query_real_name());
    if (!living(to)) write_file("/d/Shire/log/items",TP->query_name()+" cloned the GreySabre into "+file_name(ENV(TO))+". "+ctime(time())+".\n");
    else write_file("/d/Shire/log/items",TP->query_name()+" cloned the GreySabre."+ctime(time())+".\n");
    }
  else if (given_away && from->query_wiz_level())
  {
    write_file("/d/Shire/log/items",from->query_name()+" gave the GreySabre to "+to->query_name()+". "+ctime(time())+".\n");
  given_away = 0;
  }
  if (!living(from) && strlen(dropped_by_wiz)) {
    write_file("/d/Shire/log/items",TP->query_name()+" picked up the GreySabre dropped by "+dropped_by_wiz+" in "+file_name(ENV(TP))+". "+ctime(time())+".\n");
    }
  else if (!living(from) && strlen(cloned_by_wiz)) {
    write_file("/d/Shire/log/items",TP->query_name()+" picked up the GreySabre cloned by "+cloned_by_wiz+" in "+file_name(ENV(TP))+". "+ctime(time())+".\n");
  }
}

