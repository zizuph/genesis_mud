/*
 * Recruiter goblin
 * Boreaulam, April 2012
 */
#pragma save_binary
#pragma strict_types

inherit "/std/monster";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>


#include "defs.h"


/*
 * Function name:        create_monster
 * Description  :        constructor for the object
 */
void
create_monster()
{
    set_adj("busy");
    set_adj("massive");
    set_short("busy massive goblin");
    set_race_name("goblin");

    set_long("The massive goblin looks very busy. " +
             "He is striding from one corner to another " +
             "thinking about something very hard." +
             "\n");

	set_base_stat(SS_STR, 50 + random(10));
	set_base_stat(SS_DEX, 40 + random(10));
	set_base_stat(SS_CON, 50 + random(10));
	set_base_stat(SS_INT, 30 + random(10));
	set_base_stat(SS_WIS, 40 + random(10));
	set_base_stat(SS_DIS, 30 + random(10));

    set_skill(SS_WEP_SWORD, 75 + random(10));
    set_skill(SS_PARRY, 65 + random(10));
    set_skill(SS_DEFENCE, 65 + random(10));
    set_skill(SS_UNARM_COMBAT, 90 + random(10));
    set_skill(SS_BLIND_COMBAT, 60 + random(10));
    set_skill(SS_AWARENESS, 70 + random(10));

	add_ask( ({ "recruitment", "recruit", "plan"}),
	        "say We are still working on our recruitment plan.", 1);
	add_chat("We will rule the world!");
	add_chat("We still need to work on our recruitment plan.");
	add_chat("We will get those reinforcements soon.");

    add_act("emote reads some papers.");
    add_act("emote writes down something.");
    add_act("emote shuffles papers on the table.");

    add_cact("say This is why we need those reinforcements!");
    add_cact("emote tries to strike at your weak side.");
    set_chat_time(20);
    set_act_time(20);
    set_cchat_time(10);
    set_cact_time(10);

	add_ask( ({ "task", "help", "quest"}),
	        "@@ask_help", 1);
	add_ask( ({ "recruit", "join", "recruiting", "plan"}),
	        "@@ask_plan", 1);
    set_default_answer("@@varied_responses");


} /* create_monster */

/*
 * Function name:        create_monster
 * Description  :        constructor for the object
 */
void
arm_me()
{
    clone_object(EQUIP_DIR + "lsword")->move(TO);
    clone_object(EQUIP_DIR + "copper_plate")->move(TO);

    command("wield all");
    command("wear all");
} /* arm_me */

/*
 * Here we redefine the special_attack function which is called from
 * within the combat system. If we return 1 then there will be no
 * additional ordinary attack.
 *
 */
int
special_attack(object enemy)
{
    mixed *hitresult;
    string result;

	if(random(3))
	{
		return 0;
	}

    hitresult = enemy->hit_me(40 + random(30), W_BLUDGEON, TO, -1);
    switch (hitresult[0])
    {
        case 0:
            result = "misses";
            break;
        case 1..10:
            result = "it hits you lightly";
            break;
        case 11..20:
            result = "you feel some pain";
            break;
        default:
            result = "it crushes into you";
            break;
    }

    enemy->catch_tell(query_The_name(enemy) + " swings a chair at you and " +
                      result + ".\n");
    tell_watcher(QCTNAME(TO) + " swings a chair at " +
                 QTNAME(enemy) + "!\n", enemy);

    if (enemy->query_hp() <= 0)
    {
		enemy->do_die(this_object());
    }

    return 1;
} /* special_attack */

/*
 * Function name:        ask_help
 * Description  :        result for ask "help"
 */
string
ask_help()
{
	return "say I don't need your help. Leave and don't disturb me.";
} /* ask_help */

/*
 * Function name:        ask_plan
 * Description  :        result for ask "plan"
 */
string
ask_plan()
{
	return "say I am working on recruitment plan. " +
           "When it is ready we will start to recruit.";
} /* ask_plan */

/*
 * Function name:        varied_responses
 * Description  :        result for ask any else
 */
public string
varied_responses()
{
    return one_of_list( ({
        "The busy massive goblin says: You're starting to annoy me!\n",
        "The busy massive goblin says: I am working. Go bother someone else.\n",
        "The busy massive goblin says: What are You doing here? Leave!\n",
        "The busy massive goblin says: I don't want to talk about it.\n" }) );
} /* varied_responses */
