/*
* Varian - February 5, 2016
*/

inherit "/std/monster";

#include "/d/Gondor/rhovanion/mirkwood/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

int alarm_id;
string physlook();
string emotelook();
string gobname();

create_monster()
{
    if (!IS_CLONE)
        return;

    set_name(({gobname()}));
    set_race_name("goblin");
    set_adj(({emotelook(),physlook()}));
    set_stats(({140, 135, 150, 55, 55, 125}), 40);
    set_alignment(-700);

    set_skill(SS_WEP_SWORD,100);
    set_skill(SS_PARRY,100);
    set_skill(SS_DEFENCE,100);

    set_gender(G_MALE);

    set_chat_time(70);
    
    add_chat("Yer a gutless blighter you is! Get outta me way!");
    add_chat("The road to Goblintown isn't what it used to be!");
    add_chat("It might not be much, but I miss me home!");
    add_chat("Lawdy, its works all day and works all night! No rest for the " +
        "wicked they says!");
    add_chat("Get lost!");
    add_chat("Blimey, yer a right gutter aren't ye!");

    add_ask(({"task","tasks"}),VBFC_ME("ask_task"));
    add_ask(({"help", "job"}),VBFC_ME("ask_help"));
    add_ask(({"quest","quests"}),VBFC_ME("ask_quest"));
    add_ask(({"village","hargnak", "home"}),VBFC_ME("ask_harg"));
    add_ask(({"town","goblintown","road"}),VBFC_ME("ask_road"));

    set_act_time(60);

    add_act("burp");
    add_act("scratch");
    add_act("growl");
    add_act("cough");
    add_act("fart");
    add_act("stomp");
    add_act("blink");
    add_act("swear");
    add_act("roar");
    add_act("chortle");
   

    set_alarm(0.5,0.0,"arm_me");

}
string
ask_harg()
{
    command("say Hargnak?");
    command("cough");
    command("say Why do you want to know? My home it is! But a village " +
        "just like any other.");
    return "";
}

string
ask_road()
{
    command("say Bah, this road seems to be getting worse each year!");
    command("grumble");
    command("say How am I supposed to travel to Goblintown like this!");
    return "";
}

string
ask_task()
{
    command("say You want a task, do you?");
    command("grunt");
    command("say Why do you think I would be wanting a task " +
        "from a squeaker like you? Hmm?");
    return "";
}

string
ask_help()
{
    command("say Help?");
    command("laugh");
    command("say Not from the likes of you!");
    return "";
}

string
ask_quest()
{
    command("say Why yes, I am on a quest! For elven blood!");
    command("laugh evil");
    return "";
}


arm_me()
{
    object sword, leather, shield, helm;

    FIXEUID;

    switch(random(6))
	{
		case 0: sword = clone_object(GOBLINS_DIR + "wep/gobsword6");
		break;
		case 1: sword = clone_object(GOBLINS_DIR + "wep/gobsword5");
		break;
		case 2: sword = clone_object(GOBLINS_DIR + "wep/gobsword4");
		break;
		case 3: sword = clone_object(GOBLINS_DIR + "wep/gobsword3");
		break;
		case 4: sword = clone_object(GOBLINS_DIR + "wep/gobsword2");
		break;
		case 5: sword = clone_object(GOBLINS_DIR + "wep/gobsword1");
		break;
		default : sword = clone_object(GOBLINS_DIR + "wep/gobsword1");
		break;
	}
		
    FIXEUID;  

    switch(random(6))
    {
        case 0: leather = clone_object(GOBLINS_DIR + "arm/gobleather6");
        break;
        case 1: leather = clone_object(GOBLINS_DIR + "arm/gobleather5");
        break;
        case 2: leather = clone_object(GOBLINS_DIR + "arm/gobleather4");
        break;
        case 3: leather = clone_object(GOBLINS_DIR + "arm/gobleather3");
        break;
        case 4: leather = clone_object(GOBLINS_DIR + "arm/gobleather2");
        break;
        case 5: leather = clone_object(GOBLINS_DIR + "arm/gobleather1");
        break;
        default : leather = clone_object(GOBLINS_DIR + "arm/gobleather1");
        break;
    }

    FIXEUID; 

    switch(random(6))
    {
        case 0: shield = clone_object(GOBLINS_DIR + "arm/gobshield6");
        break;
        case 1: shield = clone_object(GOBLINS_DIR + "arm/gobshield5");
        break;
        case 2: shield = clone_object(GOBLINS_DIR + "arm/gobshield4");
        break;
        case 3: shield = clone_object(GOBLINS_DIR + "arm/gobshield3");
        break;
        case 4: shield = clone_object(GOBLINS_DIR + "arm/gobshield2");
        break;
        case 5: shield = clone_object(GOBLINS_DIR + "arm/gobshield1");
        break;
        default : shield = clone_object(GOBLINS_DIR + "arm/gobshield1");
        break;
    }
        
    FIXEUID;  

    switch(random(6))
    {
        case 0: helm = clone_object(GOBLINS_DIR + "arm/gobhelm6");
        break;
        case 1: helm = clone_object(GOBLINS_DIR + "arm/gobhelm5");
        break;
        case 2: helm = clone_object(GOBLINS_DIR + "arm/gobhelm4");
        break;
        case 3: helm = clone_object(GOBLINS_DIR + "arm/gobhelm3");
        break;
        case 4: helm = clone_object(GOBLINS_DIR + "arm/gobhelm2");
        break;
        case 5: helm = clone_object(GOBLINS_DIR + "arm/gobhelm1");
        break;
        default : helm = clone_object(GOBLINS_DIR + "arm/gobhelm1");
        break;
    }
    sword->move(TO);
    leather->move(TO);
    shield->move(TO);
    helm->move(TO);
    
    command("wield all");
    command("wear all");

}

void
attacked_by(object obj)
{
    ::attacked_by(obj);
    command("say Oh ho! Looky what I found here!");
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
    command("say Hah! Looks like I gots me a fresh one!");
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
gobname()
{
    string *banname;
    banname = ({"murg", "ghashk", "nurk", "helk", "belg", "bozuk",
        "dhurg", "dulzig", "fashk", "fulg", "guzga", "hashk",
        "hazka", "lurz", "lukga", "murgan", "mushkan", "gankur",
        "khamag", "kazka", "lurg", "ezgar", "narkuz", "nuzga", 
        "nashka", "olgak", "ozkat", "rashga", "ruzka", "raga",
        "skuz", "sluka", "urga", "ukrat", "zarga", "ashga", "buzgul",
        "dahkan", "durnga", "rakgan", "razolg"});
    return banname[random(sizeof(banname))];
}

string
physlook()
{
    string *physlooks;
    physlooks = ({"big", "hulking", "slender", "short", "fat", "scrawny",
        "hairy", "cross-eyed", "black-eyed", "black-haired", "bald", "smelly",
        "long-legged", "gap-toothed", "big-eared", "wall-eyed", "lithe",
        "muscled", "strong", "yellow-eyed", "greasy-haired", "snot-nosed", 
        "gigantic", "grey-skinned", "weak", "green-skinned", "dirty", "slim",
        "balding", "massive", "chubby"});
    return physlooks[random(sizeof(physlooks))];
}

string
emotelook()
{
    string *emotelooks;
    emotelooks = ({"angry", "agitated", "sad", "bloodthirsty",
        "vicious", "evil", "mean", "cruel", "deadly", "dangerous",
        "snarling", "scowling", "vindictive", "sly", "ferocious", "fierce",
        "growling", "scared", "frightened", "nervous", "insane", "mad",
        "mean", "murderous", "nasty", "grouchy", "wild", "raging",
        "savage", "sinister", "terrifying", "wicked", "loud", "watchful",
        "alert", "cautious", "silent", "psychotic"});
    return emotelooks[random(sizeof(emotelooks))];
}

