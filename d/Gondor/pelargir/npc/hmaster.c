/*
 *      /d/Gondor/pelargir/npc/hmaster.c
 *
 *      The harbour master of the harbour in Pelargir.
 *
 *      Copyright (c) 1997 by Christian Markus
 *
 *      Modification log:
 *	6 June 1999, Gnadnar:	summon guards if attacked (code
 *		swiped from Elessar's mods to the old ranger),
 *		remember who killed me.
 */
#pragma strict_types

inherit "/d/Gondor/pelargir/npc/pelargir_npc.c";

#include <macros.h>
#include <money.h>
#include <state_desc.h>
#include <stdproperties.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "../lib/repair_dock.h"
#include "../lib/defs.h"

#define WEP1 "/d/Gondor/common/wep/lsword"
#define ARM1 "/d/Gondor/common/arm/studl"

#define RAT_PRICE 18

#define	PEL_GUARD	(PELAR_DIR + "npc/pelargir_guard")
#define	ADD_KILLER(x) \
    ((PELAR_DIR + "misc/pel_office")->add_killer(x, "Londhir"))
#define	QUERY_KILLER(x) \
    ((PELAR_DIR + "misc/pel_office")->query_killer(x))

int Guards_summoned;

void	do_die(object killer);
void    clone_guards();
void    attacked_by(object ob);
int     special_attack(object victim);

public void
create_pelargir_npc()
{
   int     rnd1 = random(11),
           rnd2 = random(11);

   set_title("the Harbour Master of Pelargir");
   set_name("londhir");
   add_name(({"master", "harbour master", "_Pelargir_soldier"}));
   set_race_name("human");
   set_adj("grey-haired");
   set_adj("tall");
   set_long(BSN(
       "You see a lean, grey-haired man of dunadan descent. This is "
     + "Londhir, by order of the Admiral Master of the harbour of "
     + "Pelargir. It is his duty to look after the docks, the ship "
     + "yard, and the warehouses here at the harbour, ordering repairs "
     + "to be made, and distributing the space to store goods among the "
     + "merchants and captains trading here. He might be able to "
     + "provide you with a task if you ask him."));

   default_config_npc(55 + rnd1);
   set_base_stat(SS_CON, 75 + rnd2);
   set_skill(SS_WEP_SWORD, 65);
   set_skill(SS_2H_COMBAT,35);
   set_skill(SS_PARRY,45);
   set_skill(SS_DEFENCE,55);
   set_skill(SS_SNEAK,53);
   set_skill(SS_AWARENESS,55);
   set_alignment(400);
   add_prop(NPC_M_NO_ACCEPT_GIVE,0);
   set_chat_time(7);
   add_chat("These rats are a curse!");
   add_chat("I'll pay cash for every dead rat!");
   add_chat("The merchants keep pestering me about the vermin in the warehouses.");
   add_chat("Those rats be damned!");
   add_chat("I want those rats exterminated!");
   add_chat("The sea port of Minas Tirith is Pelargir, not the Harlond.");
   add_chat("I need help, if you are interested in a job, then ask me!");
   add_cchat("Alarm!");
   add_cchat("Help! I'm being attacked by a maniac!");
   add_cchat("Ok, come on, bastard! I'll beat you up badly!");
   add_cchat("We won't give in to the enemy, killing me won't help!");
   add_cchat("You won't get away with this!");
   add_cchat("You will regret this when you are lying in chains in the prison!");
   set_default_answer(VBFC_ME("default_answer"));
   add_ask(({"help","task","quest","job"}), VBFC_ME("task_inform"));
   add_ask(({"about help","about task","about quest","about job"}), VBFC_ME("task_inform"));
   add_ask(({"for help","for task","for quest","for job"}), VBFC_ME("task_inform"));
   add_ask(({"about ithilien","ithilien"}), VBFC_ME("ask_ithilien"));
   add_ask(({"about anduin","anduin","about cross","cross"}), VBFC_ME("cross_anduin"));
   add_ask(({"about edoras","about rohan","rohan","edoras"}), VBFC_ME("ask_rohan"));
   add_ask(({"about pelargir","pelargir"}), VBFC_ME("ask_pelargir"));
   add_ask(({"harbour", "docks", "repairs", }), VBFC_ME("ask_docks"));
   add_ask(({"rat","rats","vermin"}), VBFC_ME("ask_rats"));
   add_ask(({"lebennin","about lebennin"}), VBFC_ME("ask_lebennin"));
   add_ask(({"about rat","about rats","about vermin"}), VBFC_ME("ask_rats"));
}

public void
arm_me()
{
   FIX_EUID
   clone_object(WEP1)->move(TO);
   command("wield longsword");
   clone_object(ARM1)->move(TO);
   command("wear armour");
}

public void
add_introduced(string str)
{
    object  pl;

    if (!objectp(pl = find_player(str)))
        return;

    if (!QUERY_KILLER(pl))
    {
	set_alarm(2.0, 0.0, &command("introduce myself"));
    }
}

string
task_inform()
{
    int     rank;
    object  tp = TP;

    if (QUERY_KILLER(tp))
    {
	command("glare " + OB_NAME(tp));
	command("say I want nothing to do with you, brigand!");
	return "";
    }
    if (((rank = member_array(tp->query_exp_title(), SD_AV_TITLES)) < 3) && (rank > -1))
    {
        command("say I need help killing those rats at the harbour!");
        command("say I will pay for every corpse of a rat that you can bring me.");
        command("say I pay good cash!");
    }
    else if (!tp->test_bit("Gondor", PELARGIR_REPAIR_DOCK_GROUP, PELARGIR_REPAIR_DOCK_BIT))
    {
        if (tp->query_prop(PELARGIR_I_REPAIR_DOCK) & REPAIR_TASK)
        {
            command("peer " + tp->query_real_name());
            command("say I already told you what to do, didn't I?");
            command("say Go out and check on the condition of the docks.");
            command("say And if there are any small repairs to be done, please make them on the spot.");
            return "";
        }
        command("smile " + tp->query_real_name());
        command("say As a matter of fact, I am in need of some assistance!");
        command("say One of my duties is to supervise the maintenance of the docks.");
        command("say You wouldn't believe how hard it is to get that work done sometimes!");
        command("say So could you please go out and check on the condition of the docks?");
        command("say And if there are any small repairs to be done, please make them on the spot.");
        command("say I will pay you for your efforts!");
        tp->add_prop(PELARGIR_I_REPAIR_DOCK, REPAIR_TASK);
        START_QUEST(tp, "PELARGIR REPAIR DOCK");
    }
    else if (rank > 3)
    {
        command("peer " + tp->query_real_name());
        command("say I don't have any tasks for you, I'm afraid!");
    }
    else
    {
        command("say I need help killing those rats at the harbour!");
        command("say I will pay for every corpse of a rat that you can bring me.");
        command("say I pay good cash!");
    }
    return "";
}

void
remove_rat(object rat)
{
    rat->remove_object();
}

void
reward_player(object rat, object player)
{
   int price;
   
   FIX_EUID

   if (QUERY_KILLER(player))
   {
	command("glare " + OB_NAME(player));
	command("drop " + OB_NAME(rat));
	return;
   }

   set_alarm(5.0, 0.0, &remove_rat(rat));

   switch (player->query_exp_title())
   {
   case "novice":     price = RAT_PRICE * 4; break;
   case "greenhorne": price = RAT_PRICE * 2; break;
   case "beginner":   price = RAT_PRICE;     break;
   case "apprentice": price = RAT_PRICE / 2; break;
   case "wizard":     price = 0; break;
   default:           price = 0; break;
   }

   if (!price)
   {
      command("hmm");
      command("say Thanks, but I must admit, I'm a bit surprised!");
      command("say Why does " + LANG_ADDART(player->query_exp_title()) +
         " go around killing rats?");
      command("say I usually offer this job to poor devils ");
      command("say so they can earn some cash. ");
      command("say I will not pay you for this!");
      return;
   }
   MONEY_MAKE_CC(price)->move(TO);
   command("thank " + player->query_real_name());
   command("say Thank you very much for your help!");
   command("say Here is the promised reward, "+price+" copper coins.");
   command("give " + price + " copper coins to " + player->query_real_name());
}

void
return_item(object ob, object from)
{
    if (ob->id("coin"))
    {
        command("say Why, thank you! I can always use a little tip!");
        return;
    }

    command("say What am I supposed to do with this?");
 
    if( (!present(from,ENV(TO))) || (ob->move(from)) )
    {
        ob->move(ENV(TO));
        command("emote drops "+LANG_ADDART(ob->query_name())+".");
    }
    else
    {
        if (!stringp(ob->short()))
            log_file("errors", file_name(TO)+": "+file_name(ob)+" does not define short()!\n");
        from->catch_msg(QCTNAME(TO) + " gives you the "+ob->short()+" back.\n");
        tell_room(ENV(TO), QCTNAME(TO) + " gives "+LANG_ADDART(ob->short())
          + " back to " + QTNAME(from) + ".\n", from);
    }
}
   
void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);

   if(!objectp(from) || !objectp(ob) || !living(from))
      return;
   if((ob->id("corpse of rat") && from == TP))
      set_alarm(1.0, 0.0, &reward_player(ob,from));
   else
      set_alarm(2.0, 0.0, &return_item(ob,from));
}

string
ask_ithilien()
{
    if (QUERY_KILLER(TP))
    {
	command("glare " + OB_NAME(TP));
	return "";
    }
   command("say Ithilien once was the garden of Gondor.");
   command("say It lies east of the Anduin, between the river " );
   command("say and the Ephel Duath, the Mountains of Shadow.");
   command("say Since the armies of the Evil One reign in Ithilien");
   command("say no one may enter cross the Anduin, save by ");
   command("say leave of the Steward.");
   return "";
}

string
cross_anduin()
{
    if (QUERY_KILLER(TP))
    {
	command("glare " + OB_NAME(TP));
	return "";
    }
   command("say The Anduin is the mightiest river in Middle Earth.");
   command("say It divides Gondor into two parts, Ithilien on the ");
   command("say eastern bank, and Anorien and the coastlands to the ");
   command("say There might be some ferries running across the river.");
   command("say Go to Hunthor in Minas Tirith, he might be able to help you.");
   return "";
}

string
ask_rohan()
{
    if (QUERY_KILLER(TP))
    {
	command("glare " + OB_NAME(TP));
	return "";
    }
   command("say Edoras is the capital of Rohan, the land of the Rohirrim.");
   command("say Since the times of Eorl the Young there has been ");
   command("say friendship between Gondor and Rohan!");
   command("say Rohan lies north of the Ered Nimrais, the White Mountains.");
   command("say From Minas Tirith, follow the road northward through Anorien.");
   command("say You will come to Firien Forest and the Mering Stream.");
   command("say That is the border between Gondor and Rohan.");
   return "";
}

string
ask_pelargir()
{
    if (QUERY_KILLER(TP))
    {
	command("glare " + OB_NAME(TP));
	return "";
    }
   command("say Pelargir is the sea port of Minas Tirith!");
   command("say And it is the second most important city of the realm!");
   command("say I am responsible for the harbour here.");
   return "";
}

string
ask_rats()
{
    if (QUERY_KILLER(TP))
    {
	command("glare " + OB_NAME(TP));
	return "";
    }
   command("say Like I said I'll pay cash for rat corpses.");
   command("grin");
   command("say But of course you must bring me one before I can pay.");
   return "";
}

string
ask_lebennin()
{
    if (QUERY_KILLER(TP))
    {
	command("glare " + OB_NAME(TP));
	return "";
    }
  command("say Lebennin is the land south of the White Mountains and west of the Anduin.");
  command("say Pelargir is its capital.");
  command("say It is a fair land full of wildlife and herbs.");
  return "";
}

string
default_answer()
{
    if (QUERY_KILLER(TP))
    {
	command("glare " + OB_NAME(TP));
	return "";
    }
    command("think");
    command("peer " + TP->query_real_name());
    command("say I do not know what you are talking about!");
    command("shrug");
    return "";
}

string
ask_docks()
{
    if (QUERY_KILLER(TP))
    {
	command("glare " + OB_NAME(TP));
	return "";
    }
    command("say One of my duties is the supervision of the "
        + "maintenance work for the docks here in the harbour.");
    command("It is getting harder and harder to find skilled "
        + "workers for the repairs.");
    command("sigh");
    return "";
}

public void
do_reward(object tp)
{
    int     reward;

    if (!objectp(present(tp, ENV(TO))))
        return;

    if (QUERY_KILLER(tp))
    {
	command("glare " + OB_NAME(tp));
	command("say I want nothing to do with you, brigand!");
	return;
    }

    command("smile");
    command("say Did you complete the repairs?");
    command("say Excellent! Well done!");

    reward = tp->query_exp();
    if (reward > PELARGIR_REPAIR_DOCK_EXP)
        reward = PELARGIR_REPAIR_DOCK_EXP;

    if (!tp->test_bit("Gondor", PELARGIR_REPAIR_DOCK_GROUP,
        PELARGIR_REPAIR_DOCK_BIT))
    {
        tp->set_bit(PELARGIR_REPAIR_DOCK_GROUP,
            PELARGIR_REPAIR_DOCK_BIT);
        tp->add_exp_quest(reward);
	tp->adjust_alignment(50);
        tp->catch_tell("You feel more experienced!\n");
        LOG_QUEST(tp, reward, "PELARGIR REPAIR DOCK");
    }

    MONEY_MAKE_GC(2)->move(TO);
    command("thank " + tp->query_real_name());
    command("say Thank you very much for your help!");
    command("say Here is the promised payment, two gold coins.");
    command("give two gold coins to " + tp->query_real_name());
    tp->remove_prop(PELARGIR_I_REPAIR_DOCK);
}

public void
do_remind(object tp, int value)
{
    if (!objectp(present(tp, ENV(TO))))
        return;

    if (QUERY_KILLER(tp))
    {
	command("glare " + OB_NAME(tp));
	command("say I want nothing to do with you, brigand!");
	return;
    }

    if (value & REPAIR_LAST)
    {
        if (value == REPAIR_DONE)
        {
            do_reward(tp);
        }
        else
        {
            // We have done the last stage of the quest,
            // but not all previous stages:
            command("say Ah, thank you for finishing the repairs!");
            command("thank " + tp->query_real_name());
            command("say But I can pay you only if you do all of the repairs by yourself.");
            // ... and we want them to do the steps in the right sequence:
            tp->remove_prop(PELARGIR_I_REPAIR_DOCK);
        }
    }
    else if (value & REPAIR_REPLACE)
    {
        command("say Did you finish the repairs yet?");
        command("say Perhaps you should look for a hammer and nails "
            + "to nail the plank to the dock?");
    }
    else if (value & REPAIR_PLANK)
    {
        command("say Hi, how are the repairs coming along?");
        command("say Are you looking for a saw?");
        command("say Sorry, I have no idea where the workers store "
            + "their tools.");
        command("sigh");
    }
    else if (value & REPAIR_REMOVE)
    {
        command("say Ah, did you find anything in need of repairs?");
        command("say Keep up the good work and fix that dock for me, "
            + "will you?");
        command("smile " + tp->query_real_name());
    }
}

public void
init_attack()
{
    int    value;

    ::init_attack();

    if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, TP) || objectp(query_attack()))
        return;

    if (!(value = TP->query_prop(PELARGIR_I_REPAIR_DOCK)))
        return;

    if (value == REPAIR_DONE)
    {
        set_alarm(4.0, 0.0, &do_reward(TP));
        return;
    }
    set_alarm(5.0, 0.0, &do_remind(TP, value));
}


/*
 * Function name:	do_die
 * Description	:	mask parent to mark our killer
 * Arguments	:	object killer -- cause of death
 *
 */
public void
do_die(object killer)
{
    if (interactive(killer))
    {
	ADD_KILLER(killer);
	killer->add_prop(PEL_I_DID_ATTACK, 1);
    }
    ::do_die(killer);
}



/*
 * Function name:	clone_guards
 * Description	:	clone up some protection
 */
public void
clone_guards()
{
    int n;
    object tmp;

    FIX_EUID

    n = sizeof(filter(all_inventory(ENV(TO)), &->id("_pelargir_guard")));
    if (n < 6)
    {
        tmp = clone_object(PEL_GUARD);
        tmp->arm_me();
        tmp->move_living("away", ENV(TO));
        tmp->command("say " + ONE_OF_LIST(({"Now, what's going on here?",
           "I thought I heard fighting!", "Enemies!"})));
        if (TO->query_attack())
        {
            tmp->do_attack(TO->query_attack());
            TO->query_attack()->attack_object(tmp);
        }
        set_alarm(5.0, 0.0, clone_guards);
    }
} /* clone_guards */



/*
 * Function name:	attacked_by
 * Description	:	respond to an attack
 * Arguments	:	object ob -- the attacking object
 */
public void
attacked_by(object ob)
{
    if (!Guards_summoned &&
	!present("_pelargir_guard", ENV(TO)))
    {
        clone_guards();
	Guards_summoned = 1;
    }
    ::attacked_by(ob);
} /* attacked_by */



/*
 * Function name:	special_attack
 * Description	:	Called from the external combat object's heart_beat
 *                	routine. We summon guards when attacked.
 * Arguments	:	object victim -- the person we're fighting
 * Returns	:	int -- 0 if we want this round to continue
 *			       1 if we are done with this round
 */
public int
special_attack(object victim)
{
    if (!Guards_summoned &&
	!present("_pelargir_guard", ENV(TO)))
    {
        clone_guards();
	Guards_summoned = 1;
    }
    return ::special_attack(victim);
} /* special_attack */

public void	set_guards_summoned(int g)	{ Guards_summoned = g; }
