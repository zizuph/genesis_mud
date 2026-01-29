/*Created by Macker 07/17/94 */

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <ss_types.h>
#include <macros.h>
#include "/sys/money.h"
#include <filter_funs.h>

inherit "/std/act/domove";
inherit "/std/act/action";
inherit M_FILE


void
create_krynn_monster()
{
    int i;
   
    set_name("villager");
    add_name("human");
    set_race_name("villager");
    set_living_name("ice folk villager");
    set_adj("ice");
    add_adj("folk");
    set_gender(random(2));
    set_long("This is one of the ice folk villagers. " +
	     C(PRONOUN(TO)) + " is wrapped tightly in hides from various animals. " +
	     C(POSSESSIVE(TO)) + " face looks worn from the years spent " +
	     "in this harsh environment. You can't tell exactly what " +
	     POSSESSIVE(TO) + " function is in this primitive society.\n");
   
   
    set_monster_home(VILLAGE + "gathering.c");
    set_restrain_path(VILLAGE);
    set_random_move(15 + random(15));
    for(i=0; i<6; i++)
      set_base_stat(i, 35 + random(20));
    set_skill(SS_DEFENCE, 20 + random(10));
    set_skill(SS_WEP_KNIFE, 10 + random(40));
   
    set_alignment(300);
    set_knight_prestige(-2);
   
    NEVERKNOWN;
   
    set_all_attack_unarmed(20, 20);
    set_all_hitloc_unarmed(30);
   
   
   
   
    if (IS_CLONE)
    {
	set_alarm(1.0,0.0,"arm_me");
	set_alarm(10.0,0.0,"no_aggression");
    }
   
}


public int
second_life(object killer)
{
    (VILLAGE + "gathering")->remove_villager(TO);
    return 0;
}

void
arm_me()
{
    seteuid(getuid(this_object()));
    tell_room(E(TO), "An ice folk villager arrives.\n");
    clone_object(PLAINS_O + "icy_knife.c")->move(TO);
    MONEY_MAKE_CC(random(3)+3)->move(TO);
    command("wield weapon");
}


no_aggression()
{
    set_aggressive(0);
}

attacked_by(object ob)
{
    object * helpers;
    set_alarm(1.0, 0.0, "command", "ack");
    set_alarm(1.2, 0.0, "command", "shout Help! This " +
	      ob->query_nonmet_name() + " " +
	      "is attacking the village!");
    helpers = FILTER_OTHER_LIVE(all_inventory(E(TO)));
    helpers = helpers - ({ TO });
    helpers->aid_folk(ob);

    return(::attacked_by(ob));
}

init_attack()
{
    if((TP->query_short() == "polar bear")&&
       (sizeof(FILTER_PLAYERS(all_inventory(E(TO)))) > 0))
    {
	command("gasp");
	command("say An ice bear graces our humble village "
		+
		"with " + TP->query_possessive() + " " +  
		"presence!!");
	command("bow bear");
	return;
    }

    return (::init_attack());
}
