/*
* Varian - February 20, 2016
* Borrowed from my bandits in Sparkle but also added some from Shire orcmaker
*/

inherit "/std/monster";
inherit "/d/Shire/common/auto_teaming";
inherit "/std/act/attack";

#include "/d/Shire/hollin/defs.h"
#include "/d/Shire/common/lib/evilkill.h"
#include "/d/Shire/prestige.h"
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <macros.h>
#include <options.h>

#define LIVE_I_KILL_ORCS  "_live_i_kill_shire_orcs"


int alarm_id;
int  my_aggressive();
string physlook();
string emotelook();
string orcname();
void arm_me();

void
create_monster()
{
    if (!IS_CLONE)
        return;

    set_name(({orcname()}));
    set_race_name("orc");
    set_adj(({emotelook(),physlook()}));
    set_stats(({45, 45, 50, 25, 25, 35}), 40);
    set_alignment(-200);

    set_pick_up_team(({"orc"}));
    set_max_team_size_auto_join(6);

    set_skill(SS_WEP_SWORD,70);
    set_skill(SS_WEP_POLEARM,70);
    set_skill(SS_WEP_CLUB,70);
    set_skill(SS_WEP_KNIFE,70);
    set_skill(SS_WEP_AXE,70);
    set_skill(SS_UNARM_COMBAT,70);
    set_skill(SS_PARRY,70);
    set_skill(SS_DEFENCE,70);
    set_skill(SS_AWARENESS,30);

    set_gender(G_MALE);

    set_chat_time(50);
    
    add_chat("I hate it out here, but it's better than working the mines!");
    add_chat("We have to keep those stinking dwarves off the road!");
    add_chat("Those pathetic dwarves thought they could steal our home!");
    add_chat("These patrols are a nasty business, but those dwarves " +
        "are worse!");
    add_chat("Get lost!");
    add_chat("What are you doing here?");
    add_chat("I hope we can plunder those pathetic humans next!");
    add_chat("If there is one thing I hate, it's an elf!");
    add_chat("Perhaps it's time to move up north.");

    add_ask(({"task","tasks"}),VBFC_ME("ask_task"));
    add_ask(({"help", "job"}),VBFC_ME("ask_help"));
    add_ask(({"quest","quests"}),VBFC_ME("ask_quest"));
    add_ask(({"path","road"}),VBFC_ME("ask_road"));
    add_ask(({"mines","moria","home"}),VBFC_ME("ask_moria"));
    add_ask(({"north","angmar","gundabad","army"}),VBFC_ME("ask_north"));
    add_ask(({"elf","elves"}),VBFC_ME("ask_elf"));
    add_ask(({"dwarf","dwarves","runts", "runt"}),VBFC_ME("ask_dwarf"));
    add_ask(({"human","humans","bree","dunland"}),VBFC_ME("ask_human"));


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

    set_intoxicated(500);
    set_aggressive(my_aggressive);
    add_prop(LIVE_I_SEE_DARK, 50 ); 

}

int
my_aggressive()
{
    string race = TP->query_race();
    // Leave the poor wizards alone.
    if (TP->query_wiz_level())
    return 0;
    // Oooh bad orc killer, we have to kill this bastard
    if (TP->query_prop(LIVE_I_KILL_ORCS))
    return 1;
    // Hmmm Dinner!!
    if (race == "hobbit" || race == "elf" || race== "dwarf")
    return 1;
    // Goblins and ogres are our friends
    if (race == "goblin" || race == "ogre" || race == "orc")
    return 0;
    // So are evil folk
    if (TP->query_alignment() <= -500)
    return 0;
    // Kill the rest and let the Vala sort them out ;-)
    return 1;
}

string
ask_moria()
{
    command("say My home is in the mines of Moria.");
    command("grin evil");
    command("say Perhaps you should come and visit us!");
    return "";
}

string
ask_road()
{
    command("say Every now and then we find one of those stinking " +
        "dwarves using our road!");
    command("spit");
    command("say They want to steal away our home!");
    return "";
}

string
ask_task()
{
    command("say I might be able to think of a task for you!");
    command("smirk");
    command("say Find me a nice juicy elf to eat! Hah!");
    return "";
}

string
ask_help()
{
    command("say You need my help do you?");
    command("laugh");
    command("say Well that ain't gonna happen! I worry about me and me only!");
    return "";
}

string
ask_quest()
{
    command("say Why yes, I am on a quest! For elven blood!");
    command("laugh evil");
    return "";
}

string
ask_north()
{
    command("say I'm thinking about moving up north to Gundabad, I hear " +
        "they are building quite the army up there!");
    command("laugh evil");
    return "";
}

string
ask_elf()
{
    command("say I hate elves!");
    command("think");
    command("say Unless we are talking about eating them!");
    return "";
}

string
ask_dwarf()
{
    command("say Every time I see a dwarf, I want to squeeze it's stubby " +
        "neck until its eyes pop!");
    command("laugh evil");
    return "";
}

string
ask_human()
{
    command("say There are too many humans these days! Those men of Bree " +
        "to the north, and those savages from Dunland to the south. It's " +
        "as if we are surrounded!");
    command("frown");
    return "";
}

void
arm_me()
{
    object wep, body, shield, helm, arm, leg;

    FIXEUID;

    switch(random(15))
	{
		case 0: wep = clone_object(WEP_DIR + "orcaxe3");
		break;
		case 1: wep = clone_object(WEP_DIR + "orcaxe2");
		break;
		case 2: wep = clone_object(WEP_DIR + "orcaxe1");
		break;
		case 3: wep = clone_object(WEP_DIR + "orcsword3");
		break;
		case 4: wep = clone_object(WEP_DIR + "orcsword2");
		break;
		case 5: wep = clone_object(WEP_DIR + "orcsword1");
		break;
        case 6: wep = clone_object(WEP_DIR + "orcpole3");
        break;
        case 7: wep = clone_object(WEP_DIR + "orcpole2");
        break;
        case 8: wep = clone_object(WEP_DIR + "orcpole1");
        break;
        case 9: wep = clone_object(WEP_DIR + "orcknife3");
        break;
        case 10: wep = clone_object(WEP_DIR + "orcknife2");
        break;
        case 11: wep = clone_object(WEP_DIR + "orcknife1");
        break;
        case 12: wep = clone_object(WEP_DIR + "orcclub3");
        break;
        case 13: wep = clone_object(WEP_DIR + "orcclub2");
        break;
        case 14: wep = clone_object(WEP_DIR + "orcclub1");
        break;
		default : wep = clone_object(WEP_DIR + "orcsword1");
		break;
	}
		
    FIXEUID;  

    switch(random(6))
    {
        case 0: body = clone_object(ARM_DIR + "orcchain3");
        break;
        case 1: body = clone_object(ARM_DIR + "orcchain2");
        break;
        case 2: body = clone_object(ARM_DIR + "orcchain1");
        break;
        case 3: body = clone_object(ARM_DIR + "orcleather3");
        break;
        case 4: body = clone_object(ARM_DIR + "orcleather2");
        break;
        case 5: body = clone_object(ARM_DIR + "orcleather1");
        break;
        default : body = clone_object(ARM_DIR + "orcleather1");
        break;
    }

    FIXEUID; 

    switch(random(3))
    {
        case 0: shield = clone_object(ARM_DIR + "orcshield1");
        break;
        case 1: shield = clone_object(ARM_DIR + "orcshield2");
        break;
        case 2: shield = clone_object(ARM_DIR + "orcshield3");
        break;
        default : shield = clone_object(ARM_DIR + "orcshield1");
        break;
    }
        
    FIXEUID;  

    switch(random(3))
    {
        case 0: helm = clone_object(ARM_DIR + "orchelm1");
        break;
        case 1: helm = clone_object(ARM_DIR + "orchelm2");
        break;
        case 2: helm = clone_object(ARM_DIR + "orchelm3");
        break;
        default : helm = clone_object(ARM_DIR + "orchelm1");
        break;
    }

    FIXEUID;  

    switch(random(3))
    {
        case 0: arm = clone_object(ARM_DIR + "orcguard1");
        break;
        case 1: arm = clone_object(ARM_DIR + "orcguard2");
        break;
        case 2: arm = clone_object(ARM_DIR + "orcguard3");
        break;
        default : arm = clone_object(ARM_DIR + "orcguard1");
        break;
    }

    FIXEUID;  

    switch(random(3))
    {
        case 0: leg = clone_object(ARM_DIR + "orcgreaves1");
        break;
        case 1: leg = clone_object(ARM_DIR + "orcgreaves2");
        break;
        case 2: leg = clone_object(ARM_DIR + "orcgreaves3");
        break;
        default : leg = clone_object(ARM_DIR + "orcgreaves1");
        break;
    }

    wep->move(TO);
    body->move(TO);
    shield->move(TO);
    helm->move(TO);
    arm->move(TO);
    leg->move(TO);
    
    TO->command("wield sword");
    TO->command("wear helm");

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
orcname()
{
    string *orcname;
    orcname = ({"azkug", "akush", "bukzag", "batkaz", "chagnak", "dizgat",
        "dwaknar", "ezkag", "emkhar", "furg", "fashna", "gurnak",
        "gazmak", "hursk", "hagnar", "iknar", "kanyuz", "kaztat",
        "lurzga", "lugmat", "mazkat", "muzburt", "naznak", "nukgar", 
        "ozgan", "olgak", "pazkir", "pugnat", "ragnuk", "ruzgat",
        "snaka", "sagka", "tuzhka", "taknir", "ungak", "uglak", "vakla",
        "vaghkit", "wazgut", "yagun", "yuzka", "zugnak", "zatmuk"});
    return orcname[random(sizeof(orcname))];
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
        "balding", "massive", "chubby", "black-skinned", "black",
        "brown-skinned", "grey-skinned", "scarred", "heavy", "dead-eyed"});
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
        "alert", "cautious", "silent", "psychotic", "crazy"});
    return emotelooks[random(sizeof(emotelooks))];
}

public void
do_die(object killer)
{
    killer->add_prop(LIVE_I_KILL_ORCS, 1);
    return ::do_die(killer);
}

void
init_living()
{
    init_team_pickup();
    ::init_living();
}