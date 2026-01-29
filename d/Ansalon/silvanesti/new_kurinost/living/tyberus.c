/* Based on aurak_leader by Aridor */

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/silvanesti/new_kurinost/local.h"
#include "/d/Ansalon/guild/dragonarmy/guild.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>

inherit "/d/Ansalon/guild/dragonarmy/npc/da_monster";
inherit AUTO_TEAM
inherit "/lib/unique";

#define TASK_NUMBER "_kurinost_raxx_task_number"
#define TYBERUS_OBJECT "_kurinost_tyberus_object"
#define TYBERUS_KILLED "_kurinost_raxx_task_killed_tyberus"
#define SPY_DETECTED "_kurinost_raxx_task_spy_detected" 

public void remove_descr();

int standing = 1;

void
create_da_monster()
{
    set_name("tyberus");
    set_living_name("tyberus");
    set_adj(({"dark-eyed", "muscular"}));
    set_long("This human seems very powerful.  From his uniform you "+
      "can easily see that he is a member of the Green Dragonarmy.  "+
      "His medals also mark him as rather high in rank.\n");

    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_WEP_SWORD, 95);
    set_skill(SS_DEFENCE, 75);
    set_skill(SS_PARRY, 75);
    set_skill(SS_BLIND_COMBAT, 80);
    set_skill(SS_AWARENESS, 70);
    add_prop(CONT_I_WEIGHT, 55000);
    add_prop(CONT_I_HEIGHT, 165);
    set_all_hitloc_unarmed(20);
    set_alignment(-950);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_color("green");
    set_dragonarmy_rank(3, 1);

    set_act_time(10);
    add_act("emote sneers at you with contempt.");
    add_act("emote barks: Mess with the Green, and you will die by my blade!");
    add_act("assist");
    add_act("emote taps the bar once, instantly getting the bartenders attention.");
    add_act("emote adjusts his armour to fit perfectly.");

    set_cact_time(10);
    add_cact("emote yells: May Takhisis feast upon your soul!");
    add_cact("emote laughs: You dare oppose the Green Dragonarmy?");
    add_cact("emote looks for an opening to take advantage of.");

    add_ask(({"patrol","first lieutenant razogh","razogh","messenger"}),
        "say I am waiting on a message from First Lieutenant Razogh. I sent him " +
        "with a patrol of draconians and hobgoblins down to the elven forest. If " +
        "you haven't been sent by him, I have nothing further to say to you.", 1);
    set_default_answer("@@default_answer");

    set_pick_up_team(({"aurak","sivak"}));
    set_max_team_size_auto_join(4);
    arm_me();

    trig_new("%w 'introduces' %s","react_to_intro");
}

string
default_answer()
{
    command("stare disdain " +TP->query_real_name());
    command("say Unless you are the messenger from First Lieutenant " +
        "Razogh's patrol, don't talk to me.");

    return "";
}

arm_me()
{
    object ob;

    setuid();
    seteuid(getuid());

    if(random(2))
    {
	ob = clone_object("/d/Krynn/solamn/splains/obj/bbattleaxe");
    }
    else
    {
	ob = clone_unique("/d/Krynn/solamn/splains/obj/bclaymore", 5,
	  "/d/Ansalon/balifor/port_balifor/obj/claymore");
    }
    ob->add_prop(TYBERUS_OBJECT, 1);
    ob->move(TO, 1);

    if(random(3))
    {
	ob = clone_object("/d/Ansalon/balifor/flotsam/obj/armour/bplatemail");
    }
    else
    {
	ob = clone_object("/d/Krynn/solamn/splains/obj/bdragonarm");
    }
    ob->add_prop(TYBERUS_OBJECT, 1);
    ob->move(TO, 1);

    ob = clone_object("/d/Krynn/solamn/splains/obj/bdragonhelm");
    ob->add_prop(TYBERUS_OBJECT, 1);
    ob->move(TO, 1);

    ob = clone_object("/d/Krynn/solamn/splains/obj/bshinguard");
    ob->add_prop(TYBERUS_OBJECT, 1);
    ob->move(TO, 1);

    ob = clone_object("/d/Krynn/solamn/splains/obj/bheavyboots");
    ob->add_prop(TYBERUS_OBJECT, 1);
    ob->move(TO, 1);

    command("wear all");
    command("wield all");
}

void
react_to_intro(string who,string garbage)
{
    set_alarm(2.0,0.0,"return_intro",who);
}

void
return_intro(string who)
{
    who = L(who);
    if (P(who,E(TO)))
    {
	command("introduce myself");
    }
}

/*
 * Function:	attacked_by
 * Arguments:	attacker - The attacker
 * Description:	This function is called when somebody attacks this object 
 */

public void
attacked_by(object attacker)
{
    ::attacked_by(attacker);
    if(!standing)
    {
       remove_descr();
       command("say Assassins! Elven sympathisers! To me!"); 
    }
}

/*
 * Funtion Name: add_desc
 * Description : Adds extra short description.
 */

public void
add_descr(string description)
{
    add_prop(LIVE_S_EXTRA_SHORT, " " + description);
}

/*
 * Function:	remove_descr
 * Description:	Remove the extra description
 */

public void
remove_descr()
{
    remove_prop(LIVE_S_EXTRA_SHORT);
}

void
attack_object(object ob)
{
    if(!standing)
    {
       remove_descr();
       command("say Assassins! To me!");
       standing = 1;
     }

    ::attack_object(ob);
}

public void
sit_down()
{
    if(!standing) 
        return;

    command("emote leans arrogantly against the bar.");
    add_prop(LIVE_S_EXTRA_SHORT, " leaning arrogantly against the long wooden bar");
    standing = 0;
    return;
}

void
attack_intruder(object enemy)
{
    if(!CAN_SEE(TO, enemy))
    {
	return;
    }

    if(TO->query_attack())
      return;

    command("kill " +enemy->query_real_name());
    return;
}

public void
stand_up(object enemy)
{
    if(standing)
        return;
    remove_descr();

    if(enemy->query_race_name() == "elf")
    {
        command("shout Elves have infiltrated the outpost! To me!");
        set_alarm(3.0, 0.0, &attack_intruder(TP));
    }
    else
    {
        command("emote looks at you suspiciously and rises from the bar.");
        command("say What are you doing in my encampment?");
    }

    standing = 1;
    return;
}



void
give_it_back(object ob, object from)
{
    string what, who;
 
    if (ob->query_no_show())
	return;

    what = L(ob->query_short());
    who = from->query_real_name();

    command("peer suspicious " + who);
    command("emote hides the " +what+ " away deep in the shadows.");
    ob->remove_object();

}

void
return_give_message(object ob, object from)
{
    string who, what;

    what = L(ob->query_short());
    who = from->query_real_name();

    if(ob->id("_kurinost_camp_secret_satchel_"))
    {
        command("frown suspic");
        command("drop satchel");
        return;
    }

    if(ob->query_seal() && (ob->id("_kurinost_camp_secret_document_")))
    {
        command("read parchment");
        command("say A message from Razogh. Or is it? The seal is broken.");
        command("frown suspic");
        command("say Spies! To me!");
        command("kill " +who);
        ob->remove_object();
        return;
    }

    if(ob->id("_kurinost_camp_secret_document_"))
    {
        command("break seal");
        command("read parchment");
        command("say Those cursed elves! And that stupid hobgoblin!");
        command("emote tears up the parchment in fury.");
        command("say Draconians! Arm up! We are going hunting!");
        command("emote storms out of the tavern in a rage.");
        remove_object();
        return;
    }

    if(ob->query_seal() && ob->id("_kurinost_camp_fake_secret_document_"))
    {
        command("read parchment");
        command("say A message from Razogh. Or is it? The seal is broken.");
        command("frown suspic");
        command("say Spies! To me!");
        command("kill " +who);
        if(from->query_prop(TASK_NUMBER) == 5)
            from->add_prop(SPY_DETECTED, 1);
        ob->remove_object();
        return;
    }

    command("break seal");
    command("read parchment");
    command("frown");
    command("say Seems we have foiled an elven ambush. Quite a few losses.");
    command("emote takes a sip from some dwarven spirits.");
    command("say And I'll probably need to find a replacement for First " +
        "Lieutenant Razogh. Shame, he was good at keeping the hobgoblins " +
        "in line.");
    command("emote turns back to the bar.");
    command("say Barkeep! Another dwarven spirit over here!");

    if(from->query_prop(TASK_NUMBER) == 5)
        from->add_prop(TASK_NUMBER, 6);

    ob->remove_object();
    return;   
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!interactive(from))
	return;

    if(ob->query_prop(TYBERUS_OBJECT))
	return;

    if(ob->id("_kurinost_camp_secret_document_") || 
       ob->id("_kurinost_camp_secret_satchel_")  || 
       ob->id("_kurinost_camp_fake_secret_document_"))
    {
	set_alarm(1.0, 0.0, &return_give_message(ob, from));
	return;
    }

    set_alarm(1.0, 0.0, &give_it_back(ob, from));
    return;
}

void
init_living()
{
    init_team_pickup();

    if(CAN_SEE(TO, TP) && (TP->query_race_name() != "draconian"))
      set_alarm(3.0, 0.0, &stand_up(TP));

    ::init_living();
}

public void
do_die(object killer)
{
    object * teammates = killer->query_team_others();

    if (sizeof(teammates) > 0)
    {
        foreach(object mate: teammates)
        {
            if(mate->query_prop(SPY_DETECTED))
            {
                mate->add_prop(TYBERUS_KILLED, 1);
            }
        }
    }

    if(killer->query_prop(SPY_DETECTED))
    {
        killer->add_prop(TYBERUS_KILLED, 1);
    }

    ::do_die(killer);
}
