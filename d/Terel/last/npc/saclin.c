
/*
 * doctor.c
 *
 * Revisions: Lilith Jan 2022: updated for healing the bone
 *                  breaks from Benton. Also, increased cost
 *                  for scry reveal from 2 plats to 5. Added
 *                  plague purge for 10 plats.
 *                  Cleaned up the code and added logging.
 * 
 */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;
inherit "/d/Terel/include/log_asks";

inherit "/lib/trade";

#include <ss_types.h>
#include <wa_types.h>
#include <language.h>
#include <composite.h>
#include <money.h>
#include <wa_types.h>
 
#define NUM             4
#define BONE_FEE        43200 /* 25 Plats */
#define PLAGUE_FEE      17280 /* 10 Plats */
#define SCRY_FEE        8640  /* 5  Plats */
#define HEAL_LOG        "/d/Terel/last/log/saclin_heals"

string ask_quest();
string ask_heal();
string ask_fees();
string ask_plague();
string ask_scry();
string ask_wound();
string ask_poison();

mapping mended_arms = ([]);

void
create_monster()
{
    if (!IS_CLONE) return;
    set_name("saclin");
    set_living_name("saclin");
    set_title("Sirvan, Healer of the Town of Last");
    add_name("healer");
    set_long("An elderly man of average height, white hair and blocky " +
        "build. He can probably help you with problems relating " +
        "to broken bones and illnesses, and possibly answer questions.\n");
    set_race_name("human");
    set_adj("elderly");
    set_gender(MALE);
    set_alignment(100);
    add_prop(OBJ_I_NO_ATTACK, 1); 

    set_stats(({95, 75, 90, 50, 50, 95}));

    set_skill(SS_WEP_CLUB, 90);
    set_skill(SS_2H_COMBAT, 90);
    set_skill(SS_BLIND_COMBAT, 90);
    set_skill(SS_AWARENESS, 90);
    set_skill(SS_LANGUAGE, 60);
    set_skill(SS_DEFENCE,91);
    set_skill(SS_HERBALISM,70);
    
    set_skill(SS_UNARM_COMBAT, 93);
    set_skill(SS_SPELLCRAFT, 90);
    set_skill(SS_WEP_SWORD, 80);
    set_skill(SS_DEFENCE, 80);
    set_skill(SS_PARRY, 85);
	
    set_all_hitloc_unarmed(33);
    set_all_attack_unarmed(75,25);
	
    config_default_trade();
    set_money_give_reduce( ({ 0, 2, 3, 3 }) );
    set_money_accept( ({0, 0, 0, 1}) );

    set_cact_time(5);

    set_act_time(5);
    add_act(({"smile", "say Want me to set any broken bones?"}));
	add_act("say I can read your aura and see who last scried you.");
	add_act("say I can heal broken bones, for a fee.");
	add_act("say The scrier always leaves a trace of themselves behind, "+
        "did you know that?");
	add_act("say Healing is a delicate business. It requires a fair "+
        "amound of skill, and those skills don't come cheap.");
	add_act("say I can purge you of the plague, too, just ask me "+
        "about it.");
    add_act("say I found the cure to that terrible plague.");
	
		
    set_default_answer("say I don't have an answer for that.", 1);
    add_ask(({"[about] [how] [do] [i] 'pay'"}), "say Try 'pay fee'.", 1);
    add_ask(({"[about] / [for] 'help'"}), "say Do you need healing? "+
        "If you do, just ask me about that.", 1);	
    add_ask(({"[for] / [about] [a] 'quest' / 'quests' / 'task'"}),
        ask_quest);
    add_ask(({"[about] / [for] 'mend' / 'heal' / 'set' / 'healing' "+
        "[my] [broken] [bone] / [bones]"}), 
		ask_heal); 	 
    add_ask(({"[about] / [for] [mend] / [heal] / [set] / [healing] "+
        "[my] [broken] 'bone' / 'bones'"}), 
		ask_heal); 	 
    add_ask(({"[about] [the] 'fee' / 'fees'"}), 
	    ask_fees);
    add_ask(({"[about] [purge] [me] / [my] [of] [the] 'plague'"}),
        ask_plague);
    add_ask(({"[about] [the] 'cure' [for] [the] [plague]"}),
        ask_plague);
    add_ask(({"'reveal' [the] [one] [who] [scried] [me]"}), 
	    ask_scry);		
    add_ask(({"[about] [who] 'scried' / 'scry' / 'scrier' [me]"}),
		ask_scry);		
    add_ask(({"[about] 'wound' / 'wounds'"}),
        ask_wound);
    add_ask(({"[about] 'poison' / 'poisons'"}),
        ask_poison);
		
	
	add_prop(LIVE_I_SEE_DARK,3);
    add_prop(LIVE_I_SEE_INVIS,2);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    trig_new("%s 'introduces' %s", "intro_me");
}


string ask_quest()
{
    command("say Have you been to the gypsy camp? Also, I " +
        "think the old mansion might be a good place to look.\n");
    return "";
}

string ask_heal()
{
    command("ponder");
    command("say I can set broken bones. I charge a large fee "+
        "of "+ (BONE_FEE / 1728) +" plats though. Try 'pay fee' "+
        "if you want treatment.");
	command("say I can also purge the plague, so ask me about "+
        "that if you want to know more.");
    command("say Otherwise, most injuries heal on their own "+
        "without my help.");
    command("say Try some healing herbs to hurry it along.");
    return "";
}

string ask_plague()
{
    command("nod");
    command("says Yes, I can purge you of the plague. I charge a "+
        "reasonable fee of "+ (PLAGUE_FEE / 1728) +" plats to do so.");
    command("say Try 'pay fee' if you want me to purge you of "+
        "the plague.");	
    TP->add_prop("ask_for_plague_purge", 1);	
}

string ask_fees()
{
    command("grin");
    command("say It's just a trifle, just " + (BONE_FEE / 1728) +
        " plats to mend broken bones, "+ (PLAGUE_FEE / 1728) +" plats to "+
        "purge the plague, and "+ (SCRY_FEE / 1728) +" plats to determine "+
        "who scried you.");
}	
	
string ask_scry()
{
    command("ponder");
    TP->add_prop("ask_for_scry_info", 1);
    command("say to " + TP->query_real_name() + " Pay the fee of " +
        (SCRY_FEE / 1728) +" plats and I'll see what I can do to "+
        "reveal the one who scried you...\n");	
	return "";
}

string ask_wound()
{
    command("say Most wounds heal on their own. Just give it some time.");
    command("say And don't pick at it!");
	return "";
}

string ask_poison()
{
    command("say Healing poisons isn't my specialty, sorry.");
    command("say So many people either recover eventually, or die fast, "+
        "so it is difficult to learn enough to make a difference.");	
}	
void fix_fracture(object player, int arm)
{
    if (player)
    {
        player->fracture_fixed(arm);    
        mended_arms[player] -= arm;
    }

}

int do_pay(string str)
{
    string  what, for_c, get_c, change, scrier;
    int *result, price, price2;
    object note, plague;
    int broken_arms;

    if (sscanf(str, "%s with %s and get %s", what, for_c, get_c) != 3)
    if (sscanf(str, "%s with %s", what, for_c) != 2)
    what = str;

    if (!str) return 0;

    if (what == "fee")
    {
        if (TP->query_prop("ask_for_scry_info"))
	    {	
            TP->remove_prop("ask_for_scry_info");
            scrier = TP->query_prop("_live_i_scried_by");
            if (scrier)
            {				           	
                price = SCRY_FEE;
                set_money_give_out(what_coins(TO));
                result = pay(price, TP, for_c, 0, TO, get_c);
                if (sizeof(result) == 1)
                  return 0; /* Pay() handles notify_fail if we want to. */
                write("You pay " + text(result[0 .. NUM - 1]) + ".\n");
                change = text(result[NUM .. 2 * NUM - 1]);
                if (change)
			    {
                  write("You get, " + change + " as change.\n");
                  say(QCTNAME(TP) + " gives some money to the healer.\n");
                }
     		    command("emote examines the air for a moment.");
                command("say It was " + 
                capitalize(scrier->query_real_name()) + 
                " who scried you.\n");
                write_file(HEAL_LOG, TP->query_cap_name() +
	            " paid for scry info " + ctime(time()) + "\n");
                return 1;
            }
		    else
            {			
                command("say As far as I can tell, you were not scried "+
                "recently.\n");
                return 1;	
	        }
        }
        if (TP->query_prop("ask_for_plague_purge"))
		{
			TP->remove_prop("ask_for_plague_purge");
			plague = present("nasty_sickness", TP); 
			if (plague)
			{
                price = PLAGUE_FEE;
                set_money_give_out(what_coins(TO));
                result = pay(price, TP, for_c, 0, TO, get_c);
                if (sizeof(result) == 1)
                return 0; /* Pay() handles notify_fail if we want to. */
                write("You pay " + text(result[0 .. NUM - 1]) + ".\n");
                write_file(HEAL_LOG, TP->query_cap_name() +
	              " paid for plague purge " + ctime(time()) + "\n");				  				
                change = text(result[NUM .. 2 * NUM - 1]);
                if (change)
                {
                  write("You get, " + change + " as change.\n");
                  say(QCTNAME(TP) + " gives some money to the healer.\n");
                }
				command("emote opens a jar and sets something alight in it.");
				command("say This should draw the plague out of you.");
				plague->cure_poison(({"all"}), 999);
				plague->timeout();
                return 1;
			}
			else
			{
               command("say I don't detect any plague upon you.");
               return 1;
            }
        }

        broken_arms = TP->query_broken_arms();
        broken_arms -= mended_arms[TP];
        if (!broken_arms)
        {
            NF("The healer says: You don't seem to have any issue that "+
            "needs my help.\n");
            return 0;
        }
		
        price = BONE_FEE;
        set_money_give_out(what_coins(TO));
        result = pay(price, TP, for_c, 0, TO, get_c);
        if (sizeof(result) == 1)
        return 0; /* Pay() handles notify_fail if we want to. */
        write("You pay " + text(result[0 .. NUM - 1]) + ".\n");
        write_file(HEAL_LOG, TP->query_cap_name() +
            " paid to fix broken arm " + ctime(time()) + "\n");				  
        change = text(result[NUM .. 2 * NUM - 1]);
        if (change)
        {
            write("You get, " + change + " as change.\n");
            say(QCTNAME(TP) + " gives some money to the healer.\n");
        }

	    int arm;
        string arm_name;
		if (broken_arms & W_LEFT)
        {
            arm_name = "left";
            arm = W_LEFT;
		}
        else 
        {
            arm_name = "right";
            arm = W_RIGHT;
        }	
		
        mended_arms[TP] += arm;
            
        say(BS("With a deft movement of his hands, the healer sets " +
            QCNAME(TP)+"'s broken " + arm_name + " arm.\n"));
        write("With a deft movement of his hands the healer sets " +
            "your broken " + arm_name + " arm.\n");
        command("say Remember, it takes a while for a set bone to heal.");
        set_alarm(200.0, 0.0, &fix_fracture(TP, arm));
        return 1;
    }
		
    command("say I'm not sure what you want me to do for you.");
    command("say I can mend broken bones, purge the plague, and "+
       "tell you who scried you recently.");
    command("say Ask me about these things if you want my help.");
    return 1;
}

void do_intro()
{
  TO->command("introduce myself");
}

void intro_me(string s1, string s2)
{
  set_alarm(2.0, -1.0, "do_intro");
}

public void add_introduced(string s_who)
{
    object o_who = find_player(s_who);

    if(o_who && !o_who->query_met(this_object()))
        set_alarm(itof(random(5) + 1), 0.0, "command",
            "introduce myself to "+ s_who);

}

init_living()
{
    ::init_living();
    add_action("do_pay", "pay");
}