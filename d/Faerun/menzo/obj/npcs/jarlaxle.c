/*
 * /d/Faerun/bootcamp/npc/jarlaxle.c
 *
 * Jarlaxle NPC/Entrance quest Underdark city
 * Clyptas, July, 2017
 */
inherit "/std/monster";
inherit "/std/act/asking";

#include "/d/Faerun/defs.h"
#include <macros.h>
#include <stdproperties.h>

#define OBJ "/d/Faerun/bootcamp/obj/"
#define QUEST_NAME_PROP "_missing_wineskin"


create_monster()
{
    seteuid(getuid());
    set_name("jarlaxle");
    
    set_title("Baenre, Commander of the Bregan D'aerthe");

    set_race_name("drow");

    set_adj( ({"stoic","pompous"}) );

    set_stats( ({190, 210, 210, 210, 210, 210}) );

    set_alignment(0);

    set_gender(G_MALE);
    
    remove_prop(LIVE_M_NO_ACCEPT_GIVE);

    set_skill(SS_UNARM_COMBAT,55);
    set_skill(SS_DEFENCE,70);
    set_skill(SS_WEP_AXE,50);
    set_skill(SS_WEP_SWORD,85);
    set_skill(SS_WEP_KNIFE,65);
    set_skill(SS_PARRY, 70);
    set_skill(SS_AWARENESS, 50);
    set_skill(SS_2H_COMBAT, 50);
    
    set_act_time(10);
    set_cact_time(10);
    add_act("emote sctratches his chin with his fingers.");
    add_act("emote places his hands on his hips and looks around.");
    add_act("emote smirks, his eyes calculating and dangerous.");
    add_act("emote smiles slyly, and tips his hat.");
    add_act("emote plays idly with the silver whistle hanging at his hip.");
   
    set_chat_time(25);
    add_chat("What do you seek here?");
    add_chat("You may be of interest to me.");

    set_cchat_time(5);
    add_cchat("Die, coward!");
    add_cchat("I will gladly put you in your place.");
    add_cchat("You think you can best me?");
	add_cchat("An illusion can kill you, if you believe it to be real.");
      
        equip(({ 
          (OBJ + "j_hat"),
          (OBJ + "j_rapier"),
          (OBJ + "j_cape"),
          (OBJ + "j_boots"),
          (OBJ + "j_bracelets"),
          (OBJ + "j_breeches"),
          (OBJ + "j_vest")}));


	add_ask(({"wine", "task", "help", "quest", "wineskin"}),
         VBFC_ME("ask_quest"));

/* don't add this to your quest npc. It's here just for testing. 
 * it resets you bit so you can redo the quest for testing purposes.
 */
    add_ask("clear bit", VBFC_ME("clearbit"));
	
}


void
add_introduced(string str)
{
if (!interactive(TP) || TP->query_met(query_name()))
return;

command("emote studies your face, evaluating you carefully.");
command("introduce me to " + TP->query_objective() + "");
}


 /*public void
add_introduced(string name)
{
	set_alarm(1.0, 0.0, &command("introduce me to "+ name));
}

public string
query_long(void)
{
	
    string res;

    if (!notmet_me(TP))
    {
	res = TO->query_name() + " is " +
	    LANG_ADDART(TO->query_nonmet_name()) +
	    ", presenting " + TO->query_objective() + "self as:\n" +
	    TO->query_presentation() + ".\n";
    }
    else if (!(TO->short(TP)))
    {
	return TO->query_name() + "is" +
	     LANG_ADDART(TO->query_nonmet_name()) +
		 ",presenting" + TO->query_objective() + "self as:\n" +
		 TO->query_presentation() + ".\n";
    }
    else
    {	
	res = CAP(TO->query_pronoun()) + " is " +
	    LANG_ADDART(TO->short(TP)) +".\n";
    }	

    if (obj_long)
	res += check_call(obj_long);

    return res;
}

static void
check_meet(object who, string oname)	{  }
	
private nomask void
init_living 
{
	::init_meet(object who);
    check_alarm = 0;	

    if (objectp(who) && present(who, environment()));
	check_meet(who, OB_NAME(who))
}

public void
init_living(void)
{
    ::init_living();

    if (!check_alarm &&
	query_interactive(TP) && CAN_SEE(TO, TP))
    {
	float delay = 1.5 + itof(random(2));
	check_alarm = set_alarm(delay, 1.0.0, &init_meet(TP));
    } */


string ask_quest()
{

    if(TP->test_bit(DOMAIN, JARLAXLE_QUEST_GROUP, JARLAXLE_QUEST_BIT))
    {
        command("emote smiles thankfully.");
	    command("say Thanks for asking, but you helped me already.");
	    return "";
    }
    

    if(TP->test_bit(DOMAIN, JARLAXLE_QUEST_GROUP, JARLAXLE_QUEST_BIT))
    {
        command("emote looks slyly at you.");
	    command("say Perhaps there'll be something in the future, but for now " +
		     "begone.");
	    return "";
    }


    if (TP->query_prop(QUEST_NAME_PROP))
    {
	    command("say Have you brought the wine?");
	    command("say Begone, until you fetch the wine!");
	    return "";
    }

    command("say Perhaps if you fetch me a skin of wine, I'd properly thank " + 
	    "you.");
    command("say I have faith that you can find it.");

// the test below is commented out for test purposes.
    TP->add_prop(QUEST_NAME_PROP,1);
    return "";

}

void
test_quest(object player, object obj)
{

    if(player->test_bit(DOMAIN, JARLAXLE_QUEST_GROUP, JARLAXLE_QUEST_BIT))
    {
	    command("say Thanks for the offer, but you helped me already.");
	    return;
    }


    if (!player->query_prop(QUEST_NAME_PROP))
    {
        command("say I didn't ask you to find this for me.");
        return;
    }

    command("eyeloo slyly at you");
    command("say You certainly took your time.");
    command("emote uncorks the wineskin and drinks heartily.");
    obj->remove_object();


    player->remove_prop(QUEST_NAME_PROP);

    tell_object(player,"You feel more experienced!\n");
    say(QCTNAME(player) + " was rewarded.\n");

    player->set_bit(JARLAXLE_QUEST_GROUP, JARLAXLE_QUEST_BIT);

    player->add_exp_quest(JARLAXLE_QUEST_EXP);

    QUEST_LOG_FILE(JARLAXLE_QUEST_LNG, JARLAXLE_QUEST_EXP);
//    obj->remove_object();
}

/* "Jarlaxle removes his hat, brushing the daytrama feather 
against the ground as he introduces himself*/

void
return_object(object from, object obj)
{
    string  obname = OB_NAME(from);

    if (obj->id("coin"))
    {
        command("emote smirks at you, pocketing the coins.");
        return;
    }

    command("say I did not ask for this!");
    command("emote gives it back to you.\n");
    obj->move(from);
    return;
}

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    if (!living(from))
	    return;

    if (obj->id("_jarlaxle_quest_item_"))
	    set_alarm(1.0,0.0, &test_quest(from, obj));
    else
    {
	    set_alarm(1.0,0.0, &return_object(from, obj));
	    return;
    }
}

void
clearbit()
{
    TP->clear_bit(JARLAXLE_QUEST_GROUP, JARLAXLE_QUEST_BIT);
    write("Bit cleared. \n");
}
