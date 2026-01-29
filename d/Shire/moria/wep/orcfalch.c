#include "defs.h"

inherit "/std/weapon";
inherit "/lib/keep";

inherit "/d/Shire/moria/lib/hit_msg";

void
create_weapon()
{
    set_name("falchion");
    add_name("_orc_falchion_");
    add_name("sword");
    set_short("iron falchion");
    set_pshort("iron falchions");
    add_adj(({"iron", "orcish", "orc"}));
    set_long("You are examining an iron falchion (a sword) made of iron. "
	   + "It seems to be forged by dwarven smiths of Moria a long time ago.\n");
    set_hit(32);
    set_pen(28);
    set_pm(({0, 0, 0}));
    set_wt(W_SWORD);
    set_wf(TO);
    set_dt(W_SLASH);
    set_hands(W_ANYH);
}

mixed
wield(object to)
{
    object wielder = ENV(to);

    if (wielder->query_race() == "orc")
    {
	set_hit(32 * 2);
	set_pen(28 * 2);
    }
}

mixed
unwield()
{
    set_hit(32);
    set_pen(28);
}

int
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{     
    produce_msg(enemy, hdesc, phurt, dt);
    return 1;
}
 
string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + query_keep_recover();
}
 
void
init_reocver(string arg)
{
    init_wep_recover(arg);
 
    init_keep_recover(arg);
}
