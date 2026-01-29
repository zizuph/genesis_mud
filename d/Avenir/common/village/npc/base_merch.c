// file name:	/d/Avenir/common/village/npc/base_merch.c
// creator(s):	Lilith, Lucius
/* Revisions:
 * 	Lucius, Oct 2008: Updates for new area and craftsman.
 * 	Lucius, Apr 2018: More enhancements.
 */
#pragma strict_types

#include <macros.h>
#include <ss_types.h>

#include "../village.h"
#include "/d/Avenir/include/relation.h"

inherit "/d/Avenir/inherit/sybarite";
inherit "/d/Avenir/inherit/craftsman";
inherit "/d/Avenir/inherit/death_crier"; 
inherit "/d/Avenir/inherit/intro";


public static int alarm_id;


static string
my_long(void)	{ return ""; }

private string
pre_long(void)
{
    string str;

    if (TP->query_met(query_real_name()))
    {
	str = query_name() +" is "+ LANG_ADDART(implode(query_adjs()," ")) +
	    " "+ query_race_name() +", presenting "+ query_objective() +
	    "self as:\n"+ query_name();

	if (strlen(query_title()))
	    str += " "+ query_title() +",";

	str += " "+ query_exp_title() +", "+
	    ({"male","female","neuter"})[query_gender()] +
	    " "+ query_race_name() +".\n";
    }
    else
    {
	str = CAP(query_pronoun()) +" is "+
	    LANG_ADDART(implode(query_adjs(), " ")) +
	    " "+ query_race_name()+".\n";
    }

    return str + my_long();
}

static void
create_merchant(void)	{  }

public nomask void
create_monster(void)
{
    create_sybarite();

    default_config_npc(40 + random(60));
    set_all_hitloc_unarmed(20 + random(20));

    set_skill(SS_DEFENCE, 45);
    set_alignment(0);

    craftsman_set_sorted_attrs();
    craftsman_set_max_user_orders(3);

    prefer_speech(1);
    create_merchant();
    set_long(pre_long);
}

/*
 * check_meet enables the npc to greet players it
 * comes into contact with, according to guild.
 */
static void
check_meet(object who, string oname, int sybarite)	{  }

private void
pre_check_meet(object who)
{
    alarm_id = 0;

    if (!objectp(who) || !present(who, environment()))
	return;

    command("$introduce me");
    check_meet(who, OB_NAME(who), IS_SYBARITE(who));
}

public void
init_living(void)
{
    ::init_living();

    // add the craftsman's commands
    craftsman_init();

    if (!alarm_id && random(3) &&
	query_interactive(TP) && CAN_SEE(TO, TP))
    {
	float delay = 2.0 + itof(random(2)) + rnd();
	alarm_id = set_alarm(delay, 0.0, &pre_check_meet(TP));
    }
}

public string 
query_exp_title(void)
{
    return "sybarite "+ ::query_exp_title();
}

public int
special_attack(object victim)
{
    switch (random(10))
    {
    case 2: command("heal");
	return 0;
    case 3: command("punch");
	return 1;
    case 5: command("heal");
	return 0;
    default:
    }
    return 0;
}
