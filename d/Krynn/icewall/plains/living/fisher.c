/* Created by Macker 07/17/94 */
/* Reduced max alarm load, Aridor 12/96 */

#include "/d/Krynn/common/defs.h"
#include <ss_types.h>
#include <macros.h>
#include "/sys/money.h"
#include "/d/Krynn/icewall/local.h"
#include <filter_funs.h> 
inherit "/std/act/domove";
inherit "/std/act/action";


inherit M_FILE

int no_yell = 0;

void
create_krynn_monster()
{
    int i;

    set_name("fisherman");
    add_name("human");
    set_pname("fishermen");
    set_pshort("ice folk fishermen");
    set_race_name("fisherman");
    set_living_name("ice folk fisherman");
    set_adj("folk");
    set_adj("ice");

    set_long("This is one of the ice folk fishermen. As you would guess, " +
	     "there isn't much plant life around. Therefore, the ice folk " +
	     "depend on the fishermen and the hunters to maintain their " +
	     "food supply.\n");

    set_monster_home(VILLAGE + "gathering.c");
    set_restrain_path(VILLAGE);
    set_random_move(15 + random(15));


    for(i=0; i<6; i++)
      set_base_stat(i, 40 + random(10));
    set_skill(SS_DEFENCE, 20 + random(20));
    set_skill(SS_WEP_KNIFE, 30 + random(30));
    set_skill(SS_WEP_POLEARM, 10 + random(30));

    set_alignment(300);
    set_knight_prestige(-2);

    NEVERKNOWN;

    set_all_attack_unarmed(30, 40);
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
    (VILLAGE + "gathering")->remove_fisher(TO);
    return 0;
}

void
arm_me()
{
    seteuid(getuid(this_object()));
    tell_room(E(TO), "An ice folk fisherman arrives.\n");
    clone_object(PLAINS_O + "icy_knife.c")->move(TO);
    clone_object(ICE_CAST_O + "pole")->move(TO);
    MONEY_MAKE_CC(random(3)+3)->move(TO);
    command("wield weapon");
}

void
ok_to_yell_again()
{
    no_yell = 0;
}

void
attacked_by(object ob)
{
    object * helpers;
    if (!no_yell)
    {
	set_alarm(1.0, 0.0, "command", "ack");
	set_alarm(1.2, 0.0, "command", "shout Help! This " +
		  ob->query_nonmet_name() + " " +
		  "is attacking the village!");
	no_yell = set_alarm(10.0, 0.0, "ok_to_yell_again");
    }
    helpers = FILTER_OTHER_LIVE(all_inventory(E(TO)));
    helpers = helpers - ({ TO });
    helpers->aid_folk(ob);

    ::attacked_by(ob);
}

no_aggression()
{
    set_aggressive(0);
}

init_attack()
{
    if((TP->query_short() == "polar bear")&&
       (sizeof(FILTER_PLAYERS(all_inventory(E(TO)))) > 0))
    {
	command("gasp");
	command("say An ice bear graces our humble village " +
		"with " + TP->query_possessive() + " " +
		"presence!!");
	command("bow bear");
	return;
    }
	
    return (::init_attack());
}

