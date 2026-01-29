/*
* Varian - October 5, 2015
*/

inherit "/std/monster";
inherit "/d/Shire/common/auto_teaming";

#include "../wild.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Shire/common/make_money.h"

int alarm_id;
string physlook();
string emotelook();

create_monster()
{
    if (!IS_CLONE)
        return;

    set_name("origan");
    add_name("bandit");
    set_race_name("human");
    set_adj(({emotelook(),physlook()}));
    set_stats(({65, 65, 85, 30, 30, 55}), 10);
    MAKE_MONEY;
    set_alignment(-500);

    set_pick_up_team(({"bandit"}));

    set_skill(SS_WEP_SWORD,80);
    set_skill(SS_PARRY,80);
    set_skill(SS_DEFENCE,80);

    set_gender(G_MALE);

    set_chat_time(7);
    
    add_chat("What do you think you are doing here runt?");
    add_chat("I make the decisions around here!");
    add_chat("I think we need to target more of those merchants in Sparkle, " +
        "I'll bet there is some good loot there.");
    add_chat("You don't look so tough to me.");
    add_chat("Do I smell something funny in the air? Oh, it's probably just " +
        "you.");
    add_chat("Get out before I throw you out! How did you get in here " +
        "anyways?");
    add_chat("Nothing like a good brawl to get the day started.");
    add_chat("I think we need to expand our operations here a little.");
    add_chat("Coppers! Again! You would think these merchants would have a " +
        "little silver or gold on them, right?");
    add_chat("What a day, I think I need to crack some heads.");

    add_ask(({"task","tasks"}),VBFC_ME("ask_task"));
    add_ask(({"help", "job"}),VBFC_ME("ask_help"));
    add_ask(({"quest","quests"}),VBFC_ME("ask_quest"));
    add_ask(({"money","coins","copper","gold","silver"}),VBFC_ME("ask_money"));
    add_ask(({"sparkle","people"}),VBFC_ME("ask_sparkle"));
    add_ask(({"smell","stink"}),VBFC_ME("ask_smell"));
    add_ask(({"brawl","fight","crack", "tough"}),VBFC_ME("ask_brawl"));
    add_ask(({"merchant", "merchants"}),VBFC_ME("ask_merchant"));
    add_ask(({"bandit","thief","highwayman", "decide", "leader",
        "decisions"}),VBFC_ME("ask_bandit"));

    set_act_time(10);

    add_act("stab sword");
    add_act("emote scratches his chin, obviously deep in thought.");
    add_act("emote slaps his hand down on the table in frustration.");
    add_act("emote scowls at you menacingly, perhaps he is looking " +
        "for a fight.");
    add_act("emote squints his eyes, looking at you suspiciously.");
    add_act("stretch");
    add_act("cough");
    add_act("laugh");
    add_act("blink");
   

    set_alarm(0.5,0.0,"arm_me");

}

string
ask_task()
{
    command("say So you want a task eh?");
    command("frown");
    command("say Well, how about this?");
    command("emote gives you an evil looking grin.");
    command("say Give me everything you own and then maybe I'll let you live!");
    return "";
}

string
ask_help()
{
    command("say You want to help me, like, as in a job? You don't look " +
        "like much of a bandit to me!");
    command("laugh");
    return "";
}

string
ask_quest()
{
    command("say Quests are for idiots, leave me alone.");
    return "";
}

string
ask_smell()
{
    command("say Yeah, that's just you. You stink!");
    return "";
}

string
ask_money()
{
    command("say Once upon a time, the merchants had gold and silver in " +
        "their purses.");
    command("sigh");
    command("say Now, it's nothing but copper. Pathetic!");
    return "";
}

string
ask_sparkle()
{
    command("say I hate Sparkle and all the idiots who live there! I'm " +
        "gonna burn that place to the ground one day!");
    return "";
}

string
ask_brawl()
{
    command("say Oh yeah! I love a good brawl!");
    command("emote cracks his knuckles.");
    command("say You ready to dance stranger?");
    return "";
}

string
ask_merchant()
{
    command("say I like merchants, they are fat cowards with lots of money! " +
        "Easy meat!");
    command("laugh");
    return "";
}

string
ask_bandit()
{
    command("say A bandit?");
    command("scratch head");
    command("say Of course we're bandits! And I'm their leader! That " +
        "means that I call the shots around here!");
    return "";
}

arm_me()
{
    object sword, leather;

    FIXEUID;

    switch(random(6))
	{
		case 0: sword = clone_object(WEP_DIR + "bansword6");
		break;
		case 1: sword = clone_object(WEP_DIR + "bansword5");
		break;
		case 2: sword = clone_object(WEP_DIR + "bansword4");
		break;
		case 3: sword = clone_object(WEP_DIR + "bansword3");
		break;
		case 4: sword = clone_object(WEP_DIR + "bansword2");
		break;
		case 5: sword = clone_object(MIRKWOOD_OBJ_DIR + "wep/avoris.c");
        break;
		default : sword = clone_object(WEP_DIR + "bansword");
		break;
	}

    FIXEUID;  

    switch(random(6))
    {
        case 0: leather = clone_object(ARM_DIR + "banleather6");
        break;
        case 1: leather = clone_object(ARM_DIR + "banleather5");
        break;
        case 2: leather = clone_object(ARM_DIR + "banleather4");
        break;
        case 3: leather = clone_object(ARM_DIR + "banleather3");
        break;
        case 4: leather = clone_object(ARM_DIR + "banleather2");
        break;
        case 5: leather = clone_object(ARM_DIR + "banleather1");
        break;
        default : leather = clone_object(ARM_DIR + "banleather");
        break;
    }
		

    sword->move(TO);
    leather->move(TO);
    
    command("wear all");
    command("wield all");

}

void
attacked_by(object obj)
{
    ::attacked_by(obj);
    command("say You think you are ready to take me on?");
    command("stab sword");
    command("wield all");
    command("wear all");
    command("say I'm ready if you are!");

    alarm_id = set_alarm(0.5,0.0,"before_attack");
}

void
before_attack()
{
    if(TO->query_attack())
    {
        return;
    }
    command("stab sword");
    command("say Hah! You aren't so tough!");
    remove_alarm(alarm_id);
}


void
add_introduced(string str)
{
    if (!interactive(TP) || TP->query_met(query_name()))
        return;

    command("introduce me to " + TP->query_real_name() + "");
}

string
physlook()
{
    string *physlooks;
    physlooks = ({"big", "hulking", "slender", "hairy", "blue-eyed", 
        "black-eyed", "red-haired", "bald", "cross-eyed",
        "long-legged", "gap-toothed", "big-eared", "lithe", "muscled", "strong", 
        "brown-eyed", "brown-haired", "bearded", "grey-haired", "green-eyed", 
        "balding", "long-legged"});
    return physlooks[random(sizeof(physlooks))];
}

string
emotelook()
{
    string *emotelooks;
    emotelooks = ({"angry", "happy", "sad", "bloodthirsty",
        "vicious", "smiling", "mean", "cruel", "deadly", "dangerous",
        "snarling", "scowling", "laughing", "evil", "ferocious", "fierce",
        "growling", "mean", "murderous", "nasty", "thoughtful", "vindictive", 
        "raging", "savage", "sinister", "terrifying", "wicked", "loud", 
        "watchful", "alert", "cautious", "silent", "grouchy"});
    return emotelooks[random(sizeof(emotelooks))];
}

void
init_living()
{
    init_team_pickup();
    ::init_living();
}