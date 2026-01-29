/*
* Varian - July, 2016
*/

inherit "/std/monster";
inherit "/d/Shire/common/auto_teaming";
inherit "/d/Gondor/common/lib/friend_or_foe.c";

#include "../../defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Gondor/common/lib/logkill.c"

int alarm_id;
string physlook();
string emotelook();
string guardname();

string *weapons = ({ AN_WEP_DIR + "sword2", AN_WEP_DIR + "axe", AN_WEP_DIR + "club", AN_WEP_DIR + "axe2"}); 
string *helmets = ({ AN_ARM_DIR + "helm", AN_ARM_DIR + "helm2" });
string *body = ({ AN_ARM_DIR + "chain", AN_ARM_DIR + "plate" });
string *arms = ({ AN_ARM_DIR + "bracer", AN_ARM_DIR + "bracer2" });
string *legs = ({ AN_ARM_DIR + "greaves", AN_ARM_DIR + "greaves2" });
string *misc = ({ AN_ARM_DIR + "brooch", AN_ARM_DIR + "bracelet", AN_ARM_DIR + "necklace" });
string *hands = ({ AN_ARM_DIR + "gloves1", AN_ARM_DIR + "gloves2" });
string *feet = ({ AN_ARM_DIR + "boots1", AN_ARM_DIR + "boots2" });

void
create_monster()
{
    if (!IS_CLONE)
        return;

    set_name(({guardname()}));
    add_name("guard");
    set_race_name("human");
    set_adj(({emotelook(),physlook()}));
    set_stats(({160, 140, 180, 55, 75, 120}), 40);
    set_alignment(500);

    set_restrain_path(({CAIRANDROS_DIR}));
    set_monster_home(({CAIRANDROS_DIR + "fort12"}));

    set_pick_up_team(({"guard"}));

    set_skill(SS_WEP_SWORD,90);
    set_skill(SS_WEP_AXE,90);
    set_skill(SS_WEP_KNIFE,90);
    set_skill(SS_WEP_CLUB,90);
    set_skill(SS_WEP_POLEARM,90);
    set_skill(SS_UNARM_COMBAT,80);
    set_skill(SS_PARRY,90);
    set_skill(SS_DEFENCE,90);
    set_skill(SS_SWIM,90);

    set_gender(G_MALE);

    set_chat_time(14);
    
    add_chat("There have been rumours of orcs out here!");
    add_chat("These are grim times, and Mordor is stirring.");
    add_chat("Gondor is a strong land, we will survive.");
    add_chat("Even if there is battle at Osgiliath, Cair Andros holds.");
    add_chat("With the way these orcs have been infesting Ithilien, it " +
        "is a good thing we have the Anduin as a barrier.");
    add_chat("Thankfully it has been quiet of late up in northern Anorien, " +
        "Osgiliath is another matter unfortunately.");
    add_chat("These orcs are nothing more than bandits and thieves!");
    add_chat("Please don't bother me right now, I have a job to do.");
    add_chat("Some of our best soldiers are now serving directly in the " +
        "contested lands of Ithilien.");
    add_chat("I cannot wait to see my family back in Minas Tirith again.");

    set_chat_time(24);

    add_cchat("say Foul servant of the east! I will see you dead!");

    add_ask(({"task","tasks"}),VBFC_ME("ask_task"));
    add_ask(({"help", "job"}),VBFC_ME("ask_help"));
    add_ask(({"quest","quests"}),VBFC_ME("ask_quest"));
    add_ask(({"money","coins","copper"}),VBFC_ME("ask_money"));
    add_ask(({"orc","orcs"}),VBFC_ME("ask_orc"));
    add_ask(({"mordor","morgul"}),VBFC_ME("ask_mordor"));
    add_ask(({"anorien","gondor","ithilien"}),VBFC_ME("ask_gondor"));
    add_ask(({"anduin", "river"}),VBFC_ME("ask_anduin"));
    add_ask(({"ruins", "battle", "osgiliath"}),VBFC_ME("ask_ruins"));
    add_ask(({"island", "cair andros", "andros"}),VBFC_ME("ask_island"));

    set_default_answer(VBFC_ME("default_answer"));

    set_act_time(16);

    add_act("emote scratches his chin in thoughtful contemplation.");
    add_act("emote turns to the east and stares off in the distance with " +
        "a grim expression on his face.");
    add_act("emote swings his hands in the air, attempting to swat a fly.");
    add_act("emote pauses to look at you, attempting to assess your " +
        "motives.");
    add_act("brood");
    add_act("cough");
    add_act("greet all");
    add_act("ponder");
    add_act("worry");

    add_prop(NPC_I_NO_UNARMED,1);
    add_prop(NPC_I_NO_FEAR,1);
    add_prop(LIVE_I_SEE_DARK,1);
   
    equip(({ 
        one_of_list(weapons),
        one_of_list(helmets),
        one_of_list(body),
        one_of_list(arms),
        one_of_list(legs),
        one_of_list(misc),
        one_of_list(hands),
        one_of_list(feet)
    }));
}

public int query_knight_prestige() { return -500; }

string
ask_task()
{
    command("say Well, I have a task.");
    command("ponder");
    command("say I must keep these lands clear of orcs, they have been " +
        "bolder of late.");
    command("smile grim");
    command("say I am sure that the strength of Gondor's soldiers will " +
        "hold against anything Mordor might throw against us.");
    return "";
}

string
ask_help()
{
    command("say Well, if you see any orcs, please let me know. Or better " +
        "yet, kill them for me!");
    command("chuckle");
    return "";
}

string
ask_quest()
{
    command("say Well, I am not much of one for quests. I just do my job " +
        "and help keep Gondor safe.");
    return "";
}

string
ask_gondor()
{
    command("say We are in the land of Gondor right now, in the province " +
        "of Anorien to be exact. The evil forces of Mordor have already " +
        "attacked us and stolen Ithilien, the land across the Anduin.");
    return "";
}

string
ask_money()
{
    command("say I don't really worry much about money, I have more " +
        "important things on my mind.");
    command("sigh");
    command("say If the forces of Mordor kill us all, what difference " +
        "would it make to have lots of money?");
    return "";
}

string
ask_orc()
{
    command("say Did you see any orcs? They have been spilling out of " +
        "Mordor in numbers I could never have imagined. I hope you " +
        "killed any of them you saw!");
    return "";
}

string
ask_mordor()
{
    command("say Mordor is a foul land, far to the east.");
    command("frown");
    command("say There are thousands of orcs living there, and men of evil " +
        "heart. Gondor will do everything possible to keep these villains " +
        "from harming innocent people.");
    return "";
}

string
ask_anduin()
{
    command("say The Anduin is also known as the great river, it flows " +
        "around us here in Anorien. On the east side of the river are " +
        "the lands of Ithilien, stolen from us by the foul forces of " +
        "Mordor.");
    command("frown");
    return "";
}

string
ask_ruins()
{
    command("say The ruins are of the great city of Osgiliath, a city of " +
        "beauty and wonder which once spanned the great river itself! But " +
        "now it lays in ruins, destroyed by the foul forces of Mordor " +
        "after years of battle.");
    return "";
}

string
ask_island()
{
    command("say The island in ther middle of the Anduin is named Cair " +
        "Andros. I serve there, helping to protect Gondor from an " +
        "invasion from Mordor.");
    return "";
}


public string
default_answer()
{
   string  answer = one_of_list( ({
        "I am busy on my patrol, I do not have time to answer questions " +
            "like that.",
        "That sounds like a question I might be able to answer later, when " +
            "I am off-duty.",
        "It might be better if you ask someone else that question.",
        "What? Can't say I know much about that, you will have to find " +
        "I'm sorry, I cannot answer that right now.",
        "Couldn't tell you much there, sorry!",
        "I am just a guard on patrol, I really cannot answer a question " +
            "like that." }) );
    command("emote scratches his chin in thoughtful contemplation.");
    command("say " + answer);
    return "";
}

void
attacked_by(object obj)
{
    ::attacked_by(obj);
    command("say What do you think you are doing?");
    command("say Foul villain! You shall pay for this!");
    command("wield all");
    command("wear all");
    command("say You will never escape here alive!");
    /*add_prop(LIVE_O_ENEMY_CLING, obj);*/
}

void
attack_object(object obj)
{
    ::attack_object(obj);
    command("say You think you can get away with that?");
    /*add_prop(LIVE_O_ENEMY_CLING, obj);*/
}

void
add_introduced(string str)
{
    if (!interactive(TP) || TP->query_met(query_name()))
        return;

    command("introduce me to " + TP->query_real_name() + "");
}

string
guardname()
{
    string *guardname;
    guardname = ({"alandir", "ardhil", "borgil", "andur", "anadur",
        "banadur", "calthor", "celedil", "beongil", "damhil", "dunmir",
        "enwil", "forgil", "filadir", "ganwir", "giladur", "handir",
        "ionwar", "landil", "lormir", "mandalor", "murdan", "nardan",
        "nolgildir","ondwar","rangil","rilamir","ronadil","sanmir",
        "soladil","sarandir","tundil","tandir","vanadil","varhir",
        "artafel","amenfil","alifur","avensil","bedrahir","barandil",
        "bolestir","cavandil","celador","diol","artil","eramil","falir",
        "goramir","feltir","fandir","gamwil","horthir","hamdur","iorwil",
        "merdil","madil","nenfir","nordur","aradan","arnidan","astordan",
        "baratan","fardan","filran","gartan","melitun","meringil","nadur",
        "olwine","arwine","orgil","perundil","pardan","pentir","revaldan",
        "rodil","santir","sodil","sanmir","turandil","tavil","telencar",
        "belcar","fanacar","velandir","vorondil","wadil","wolmir"});
    return guardname[random(sizeof(guardname))];
}

string
physlook()
{
    string *physlooks;
    physlooks = ({"tall", "blue-eyed", "grey-eyed", "brown-eyed", "imposing",
        "black-haired", "brown-haired", "grey-haired", "green-eyed", "bald",
        "long-legged", "lithe", "muscular", "slender", "strong", "massive",
        "burly", "bearded", "clean-shaven", "strong-armed", "barrel-chested", 
        "lean", "large", "thick-armed", "sturdy"});
    return physlooks[random(sizeof(physlooks))];
}

string
emotelook()
{
    string *emotelooks;
    emotelooks = ({"stern", "fierce", "stoic", "happy", "dedicated",
        "dutiful", "smiling", "grim", "experienced", "deadly", "dangerous",
        "wary", "alert", "cautious", "silent", "watchful", "fierce",
        "formidable", "trustworthy", "protective", "arrogant", "reliable"});
    return emotelooks[random(sizeof(emotelooks))];
}

void
init_living()
{
    init_team_pickup();
    ::init_living();
}
