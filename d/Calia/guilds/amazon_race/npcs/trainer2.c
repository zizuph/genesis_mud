/*
 *    trainer.c  
 *
 * This is the trainer for the Amazon racial guild.
 *
 * Baldacin@Genesis, Nov 2003.
 *
 */

#include "../defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
inherit LIB+"trainer.c";
inherit LIB+"equip";

void write_training_text(object who, int snum);
int do_skill_raise(int snum, int level, int steps, int cost, string skill, object who);

object gBusy;  //Contains the player currently training.

void
create_trainer()
{
	string *equipment = ({ARM+"brown_pants",ARM+"camo_cloak",ARM+"leather_armour",ARM+"leather_boots", WEP+"spear"});

    add_name("azealia");
    add_name("trainer_");
    set_race_name("human");
    set_adj("tall");
    add_adj("fierce");
    set_title("the Legendary Amazon of the Silent Forest and Expert Trainer");
    set_long("Tall and fierce is the first things that come into "+
		"mind when looking at this Amazon warrior. Her duty amongst the "+
		"amazons is training the inhabitants of the settlement. They start "+
		"their training very early, even children get some basic defensive "+
		"education here.\n");
    set_gender(G_FEMALE);
    set_stats(({ 156, 156, 156, 156, 156, 156}));
    set_talk_skill_list(0);
    add_ask(({"leave", "leave guild"}),"say Yes, it is possible to leave "+
      "the Amazons in this room, just issue 'depart from guild'.", 1);
    add_ask(({"join", "join guild"}), "say Yes, It is possible to 'affiliate' "+
      "yourself with the Amazons in this room.\n", 1);
	add_ask(({"skills", "train","improve","learn"}), "say It is possible for "+
		"the Amazons to 'learn' and 'improve' some skills here.", 1);
    add_ask(({"token", "obtain token"}), "say You can get a new token if you "+
      "lost it. Just 'obtain' one here.", 1);
      
    set_default_answer(VBFC_ME("def_answer"));
	equip_this(equipment);
}

int
can_npc_see(object player)
{
	if (CAN_SEE(TO, player) && CAN_SEE_IN_ROOM(TO))
		return 1;
	return 0;
}

string
def_answer()
{
	if (!can_npc_see(TP))
	{
	    command("say What?! Who's there!");  
		return "";
	}

    command("say to "+TP->query_name()+" I have no idea what you are talking about.");
    command("shrug");
    return "";
}

void
initiate_training()
{
    sk_add_train(SS_DEFENCE, ({"defend yourself", "defend "+HIM(TP)+"self"}), "defence", 0, 30);
    sk_add_train(SS_WEP_MISSILE, ({"use the bow and arrow", "use the bow and arrow"}), "missiles", 0, 40);
    sk_add_train(SS_WEP_POLEARM, ({"stab with a spear", "stab with a spear"}), "polearm", 0, 50);    
    sk_add_train(SS_TRACKING, ({"search for tracks", "search for tracks"}), "tracking", 0, 30);
    sk_add_train(SS_HUNTING, ({"hunt for food", "hunt for food"}), "hunting", 0, 30);
    sk_add_train(SS_AWARENESS, ({"be more aware of your surroundings", "be more aware of "+
                                HIS(TP)+ "surroundings"}), "awareness", 0, 40);
    sk_add_train(SS_ANI_HANDL, ({"handle animals", "handle animals"}), "animal handling", 0, 30);
    sk_add_train(SS_LOC_SENSE, ({"locate your surrounding", "locate "+HIS(TP)+" surrounding"}), "location sense", 0, 30);
    sk_add_train(SS_CLIMB, ({"climb trees", "climb trees"}), "climb", 0, 40);
    sk_add_train(SS_APPR_MON, ({"appraise enemies", "appraise enemies"}), "appraise enemy", 0, 30);
}

public void
add_introduced(string name)
{
    command("introduce me to " + name);
}

int
sk_hook_allow_train(object who, string str, string verb)
{
    if (IS_MEMBER(who))
        return 1;
    
    if (who->query_wiz_level())
    {
        who->catch_tell("NOTICE: Only members may train "+
          "here, but since you are a wizard you are allowed too.\n");
        return 1;
    }
    
    return 0;
}

/*
 * Function name: sk_improve
 * Description:   Function called when player tries to do the improve command
 * Arguments:     str - The rest of the command player made
 * Returns:       1/0
 * Modifications: Modified to have a training delay.
 */
int
sk_improve(string str)
{
    int steps, *guild_sk, *known_sk, snum, level, cost, i = 0, delay = 2;
    string skill, verb, *tmp, skillgroup;

	if (!can_npc_see(TP))
	{
	    command("say What?! Who's there!");  
		return 1;
	}

	if (gBusy)
	{
		if (gBusy == TP)
		{
		    command("say to "+TP->query_name()+" Have patient, you can't train "+
				"all that on the same time.");
			return 1;
		}
		else
		{
			command("say to "+TP->query_name()+" Have patient, I will get to "+
				"you as soon as I am done with "+QTNAME(gBusy)+".");
			return 1;
		}
	
	}

    if (!sk_hook_allow_train(this_player(), str, query_verb()))
        return sk_hook_not_allow_train();

    if (!str || sscanf(str, "%d", steps))
        return sk_list(steps);

    tmp = explode(str, " ");
    if (sscanf(tmp[sizeof(tmp) - 1], "%d", steps) == 1 && sizeof(tmp) > 1)
        skill = implode(tmp[0 .. sizeof(tmp) - 2], " ");
    else
    {
        skill = str;
        steps = 1;
    }

    guild_sk = sk_query_train();
    known_sk = this_player()->query_all_skill_types();
    if (!known_sk)
    {
        known_sk = ({ });
    }

    verb = query_verb();
    if ((snum = sk_find_skill(skill)) < 0)
        return sk_hook_unknown_skill(skill, verb);

    level = this_player()->query_base_skill(snum);

    if (!sk_hook_allow_train_skill(this_player(), skill, level + steps))
        return sk_hook_not_allow_train_skill(skill);
    if (!level && verb == "improve")
        return sk_hook_improve_unknown(skill);
    if (level && verb == "learn")
        return sk_hook_learn_known(skill);
    if (level + steps > sk_query_max(snum))
        return sk_hook_improved_max(skill);

	if (!sk_do_train(snum, this_player(), level + steps))
	{
		command("say to "+TP->query_name()+" I don't think you are ready "+
			"to train that high, come back when you've grown a bit.");
			return 1;
	}

    cost = sk_cost(snum, level, level + steps);
    if (!MONEY_ADD(this_player(), -cost))
    {
        /* Set the skill back to what it was before since he cant pay. */
        this_player()->set_skill(snum, level);
        return sk_hook_cant_pay(skill, level + steps, cost);
    }

	gBusy = TP;

    switch(snum)
    {
      case SS_WEP_POLEARM: 
        set_alarm(0.5, 0.0, &write("You get a spear from the "+
          "trainer and ready yourself for practice.\n"));
        set_alarm(0.5, 0.0, &say(QCTNAME(TP)+" gets a "+
          "spear from the trainer and ready "+HIM(TP)+"self "+
          "for practice.\n"));
      break;
      case SS_WEP_MISSILE: 
        set_alarm(0.5, 0.0, &write("You get a bow and some arrows from the "+
          "trainer and ready yourslef for practice.\n"));
        set_alarm(0.5, 0.0, &say(QCTNAME(TP)+" gets a "+
          "bow and some arrows from the trainer and ready "+HIM(TP)+"self "+
          "for practice.\n"));
      break;
      default:
        set_alarm(0.5, 0.0, &write("You take a deep breath and ready yourself for a "+
          "lesson to "+sk_tdesc[snum][0]+".\n"));
        set_alarm(0.5, 0.0, &say(QCTNAME(TP)+" ready "+HIM(TP)+"self "+
          "for a lesson to "+sk_tdesc[snum][1]+".\n"));
      break;

    }
      
    while (i < steps)
    {
    	i++;
    	set_alarm(itof(delay), 0.0, &write_training_text(TP, snum));
    	delay += 2;
    	
    	if (i == steps)
    	    set_alarm(itof(delay), 0.0, &do_skill_raise(snum, level, steps, cost, skill, this_player()));
    }

    return 1;
}

int
do_skill_raise(int snum, int level, int steps, int cost, string skill, object who)
{
    set_this_player(who);
    gBusy = 0;
    if (!sk_do_train(snum, this_player(), level + steps))
        return sk_hook_cant_train(skill, level + steps);
        
    sk_hook_raise_rank(snum, level + steps, cost);
    return 1;
}



void 
write_training_text(object who, int snum)
{
    string *training_text = ({ });
    string *watcher_text = ({ });
    
    switch(snum)
    {
      case SS_WEP_POLEARM:
          training_text += ({"You watch as "+QTNAME(TO)+" instructs you "+
            "in using the "+sk_query_name(snum)+"."});
          training_text += ({"You study "+QTNAME(TO)+", following "+HIS(TO)+
            " every move."});
          training_text += ({"Following the instructions you swing around "+
            "with the spear, stabbing rapidly in the air."});
            
          watcher_text += ({QTNAME(who)+" watches as "+QTNAME(TO)+" instructs "+
            HIM(who)+" in using the "+sk_query_name(snum)+"."});
          watcher_text += ({QTNAME(who)+" studies "+QTNAME(TO)+", following "+
            HIS(TO)+" every move."});
          watcher_text += ({"Following the instructions "+QTNAME(who)+" swings "+
            HIS(who)+" spear, stabbing it rapidly in the air."});
      break;

      case SS_WEP_MISSILE:
          training_text += ({"You watch as "+QTNAME(TO)+" instructs you "+
            "in using the "+sk_query_name(snum)+"."});
          watcher_text += ({QTNAME(who)+" watches as "+QTNAME(TO)+" instructs "+
            HIM(who)+" in using the "+sk_query_name(snum)+"."});
      break;
            
      default:
          training_text += ({"You watch as "+QTNAME(TO)+" instructs you "+
            "how to "+sk_tdesc[snum][0]+"."});
          watcher_text += ({QTNAME(who)+" watches as "+QTNAME(TO)+" gets instructions "+
            "of how to "+sk_tdesc[snum][1]+"."});
      break;
    }
    who->catch_msg(one_of_list(training_text) + "\n");
    say(one_of_list(watcher_text) + "\n");
}
