/*
* Varian - October 5, 2015
*/

inherit "/std/monster";

#include "../wild.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Shire/common/make_money.h"

int alarm_id;
string physlook();
string emotelook();
string banname();

create_monster()
{
    if (!IS_CLONE)
        return;

    set_name(({banname()}));
    set_race_name("human");
    set_adj(({emotelook(),physlook()}));
    set_stats(({55, 55, 55, 45, 45, 55}), 40);
    MAKE_MONEY;
    set_alignment(-200);

    set_skill(SS_WEP_SWORD,50);
    set_skill(SS_PARRY,40);
    set_skill(SS_DEFENCE,40);

    set_gender(G_MALE);

    set_chat_time(7);
    
    add_chat("Give me all your money! Or else!");
    add_chat("There just isn't enough work for a hard-working bandit " +
        "like me these days.");
    add_chat("Those idiots in Sparkle think they are so smart!");
    add_chat("Hah! Would you believe there are some people out there who " +
        "call themselves 'adventurers'? Me, instead of wasting my time " +
        "running around the world, I'll just stay here and take the money " +
        "from any moron stupid enough to wander off the road!");
    add_chat("My mother wanted me to become a doctor.");
    add_chat("Well, you're an ugly one aren't ya!");
    add_chat("What are you looking at!");
    add_chat("Don't get any funny ideas now!");
    add_chat("You would think people would have more than just a few coppers " +
        "these days!");
    add_chat("I work smarter, not harder! Now give me all that money " +
        "you worked so hard for!");

    add_ask(({"task","tasks"}),VBFC_ME("ask_task"));
    add_ask(({"help", "job"}),VBFC_ME("ask_help"));
    add_ask(({"quest","quests"}),VBFC_ME("ask_quest"));
    add_ask(({"money","coins","copper"}),VBFC_ME("ask_money"));
    add_ask(({"sparkle","people"}),VBFC_ME("ask_sparkle"));
    add_ask(({"adventurer","adventurers"}),VBFC_ME("ask_adventurers"));
    add_ask(({"live","living","life"}),VBFC_ME("ask_live"));
    add_ask(({"doctor", "mother"}),VBFC_ME("ask_mother"));
    add_ask(({"bandit", "thief", "highwayman"}),VBFC_ME("ask_bandit"));

    set_act_time(10);

    add_act("stab sword");
    add_act("emote scratches his bottom.");
    add_act("emote picks his nose and then stares at his finger.");
    add_act("emote swings his hands in the air, attempting to swat a fly.");
    add_act("emote squints his eyes, looking at you suspiciously.");
    add_act("fart");
    add_act("cough");
    add_act("laugh");
    add_act("burp");
   

    set_alarm(0.5,0.0,"arm_me");

}

string
ask_task()
{
    command("say Hmm, a task?");
    command("think");
    command("say Yeah, I think I can find one for you.");
    command("smile evil");
    command("say Go find lots of money, come back here and give it all to me!");
    return "";
}

string
ask_help()
{
    command("say You want a job to help me out? Just give me all your " +
        "money! That will help!");
    command("laugh");
    return "";
}

string
ask_quest()
{
    command("say I'm on a sacred quest to rob the rich! and everyone else!");
    return "";
}

string
ask_live()
{
    command("say Oh yes, the bandit's life is the life for me!");
    return "";
}

string
ask_money()
{
    command("say I can always use more money! You have any coins on you?");
    command("sigh");
    command("say Seems like everyone just has coppers these days!");
    return "";
}

string
ask_sparkle()
{
    command("say I hate Sparkle and all the idiots who live there!");
    return "";
}

string
ask_adventurers()
{
    command("say Yeah, I can't believe those idiots.");
    command("laugh");
    command("say much easier to wait for them to bring their money to me!");
    return "";
}

string
ask_mother()
{
    command("say She wanted me to be a doctor, what business is it of yours?");
    command("frown");
    return "";
}

string
ask_bandit()
{
    command("say A bandit?");
    command("scratch head");
    command("say Yup! That's me! Now give me your money or else!");
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
		case 5: sword = clone_object(WEP_DIR + "bansword1");
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
    command("say You think you are ready to take me on? This won't even make " +
        "me break a sweat!");
    command("stab sword");
    command("wield all");
    command("wear all");
    command("say I'm ready if you are!");

    alarm_id = set_alarm(10.0,20.0,"before_attack");
}

void
before_attack()
{
    if(TO->query_attack())
    {
        return;
    }
    command("stab sword");
    command("say I can take you by myself with one hand tied behind " +
        "my back! Ok, let's do this!");
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
banname()
{
    string *banname;
    banname = ({"alva", "antol", "barus", "beswan", "botta", "capla",
        "certus", "clete", "clotar", "darvan", "delus", "donno",
        "farus", "fetlan", "frum", "garius", "glovian", "gurthan",
        "hardan", "heltus", "indalo", "jaka", "jurgos", "keltan", 
        "laros", "linthan", "logar", "margan", "medral", "nardus",
        "nudril", "oda", "pavor", "pradigan", "rafla", "retus", "sol",
        "talios", "terghan", "travor", "vantil"});
    return banname[random(sizeof(banname))];
}

string
physlook()
{
    string *physlooks;
    physlooks = ({"big", "hulking", "slender", "short", "fat", "scrawny",
        "hairy", "blue-eyed", "black-eyed", "red-haired", "bald", "cross-eyed",
        "long-legged", "gap-toothed", "big-eared", "wall-eyed", "lithe",
        "muscled", "strong", "brown-eyed", "brown-haired", "snot-nosed", 
        "bearded", "grey-haired", "weak", "green-eyed", "dirty", "slim",
        "balding", "long-legged", "chubby"});
    return physlooks[random(sizeof(physlooks))];
}

string
emotelook()
{
    string *emotelooks;
    emotelooks = ({"angry", "happy", "sad", "bloodthirsty",
        "vicious", "smiling", "mean", "cruel", "deadly", "dangerous",
        "snarling", "scowling", "laughing", "evil", "ferocious", "fierce",
        "growling", "scared", "frightened", "nervous", "insane", "mad",
        "mean", "murderous", "nasty", "thoughtful", "vindictive", "raging",
        "savage", "sinister", "terrifying", "wicked", "loud", "watchful",
        "alert", "cautious", "silent", "grouchy"});
    return emotelooks[random(sizeof(emotelooks))];
}

