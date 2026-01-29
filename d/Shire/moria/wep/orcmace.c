#include "defs.h"

inherit "/std/weapon";
inherit "/lib/keep";

inherit "/d/Shire/moria/lib/hit_msg";

void
create_weapon()
{
    set_name("mace");
    add_name("_orc_mace_");
    set_short("spiked high steel mace");
    set_pshort("spiked high steel maces");
    add_adj(({"spiked", "steel", "high", "orcish", "orc"}));
    set_long("You are now looking at a brutal looking high steel mace. This is "
	   + "a weapon which resembles an advanced club. It consists of a rod and "
	   + "a spiked metal ball linked with a chain.\n");
    add_item(({"spikes", "spiked ball", "spiked mace", "mace's ball", "ball"}),
	  "The mace's ball is at the end of a chain. It is spiked to inflict "
	+ "the enemy impaling damage as well as crushing.\n");
    add_item(({"chains", "chain", "mace's chain"}),
	  "The mace's chain is indeed a crafty work - probably art of old dwarven "
	+ "design. It is constructed with interconnecting links in a special way "
	+ "insuring full control and handling of the ball hitting a victim.\n");
    add_item(({"base", "rod", "base rod", "mace's rod"}),
	  "The rod seems to be furnished with runic engravings unknown to you, "
	+ "probably bringing luck to the wielder. It is of wood, probably some "
	+ "kind of hard wood to endure the force of combat.\n");

    set_hit(40);
    set_pen(20);
    set_wt(W_CLUB);
    set_wf(TO);
    set_dt(W_IMPALE | W_BLUDGEON);
    //  Changed the hands to both becuase weapon was illegal -Igneous-
    set_hands(W_BOTH);
}

mixed
wield(object to)
{
    object wielder = ENV(to);

    if (wielder->query_race_name() == "orc")
    {
	set_hit(80);
	set_pen(40);
    }
}

mixed
unwield()
{
    set_hit(40);
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
