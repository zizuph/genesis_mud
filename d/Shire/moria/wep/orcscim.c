#include "defs.h"

inherit "/std/weapon";
inherit "/lib/keep";

inherit "/d/Shire/moria/lib/hit_msg";

void
create_weapon()
{
    set_name("scimitar");
    add_name("_orc_scim_");
    set_short("curved high steel scimitar");
    set_pshort("curved high steel scimitars");
    add_adj(({"curved", "steel", "high", "orcish", "orc"}));
    set_long("This is a curved mithril scimitar reforged by orcs from dwarven "
      + "high steel in Moria, a typical weapon for the orcish hoards "
      + "within that place.\n");
    set_hit(34);
    set_pen(30);
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

    if (wielder->query_race_name() == "orc")
    {
	set_hit(68);
	set_pen(60);
    }
}

mixed
unwield()
{
    set_hit(34);
    set_pen(20);
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
