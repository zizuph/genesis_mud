//-*-C++-*-
// file name:     
// creator(s):    Lilith   07/23/03
// purpose:       Inquisitors for the bazaar admin area.
// note:          
// last update:   Lilith   04/05/97
// bug(s):
// to-do:

inherit "/d/Avenir/inherit/sybarite";
inherit "/d/Avenir/inherit/helper";
inherit "/d/Avenir/common/bazaar/NPCS/call_for_help";
inherit "/d/Avenir/inherit/log_asks";
inherit "/d/Avenir/inherit/quest";

#include "/d/Avenir/include/relation.h"
#include "/d/Avenir/include/defs.h"
#include "/d/Avenir/include/paths.h"
#include "/d/Avenir/include/guilds.h"
#include "/d/Avenir/common/bazaar/admin/admin.h"

#include <composite.h>
#include <macros.h>
#include <stdproperties.h>
#include <money.h>
#include <language.h>
#include <ss_types.h>

string *Sadj1 = ({ "angry","frowning","impatient","sincere","composed", 
                  "grim", "displeased","unpleasant","enthusiastic",
                  "pleased","agitated","smug","callous","impassive",
                  "grinning" });
string *Sadj2 = ({ "impressive","vehement","imposing","deep-chested",
                  "zealous","long-armed","impersonal","fastidious",
                  "cold-eyed","muscular","lithe","slender" }); 
string *Seyes = ({ "dark-brown","angry blue","dark green","leaf green",
                  "intense gray","thrilling black","serene blue",
                  "sparkling black","blue-black","coal-black",
                  "steel-gray","gray-green" });
string *Shair = ({ "gray-streaked","caramel-coloured","ebony black",
                  "fiery-red","silky dark","silky black","curly dark",
                  "unusual milk-white","wavy brown","mahogany brown",
                  "light brown","chestnut brown","blue-black",
                  "deep auburn","chocolate brown" });
int alarm_id;
string eyes, hair, adj1, adj2;
string query_eyes()   {    return eyes;      }
string query_hair()   {    return hair;      }
void set_eyes(string str)   {    eyes = str;      }
void set_hair(string str)   {    hair = str;      }
void set_helper();
string my_long();



/* 
 * set_morph sets the various attributes of the 
 * npc, making it unique 10 different ways.
 */
void
set_morph()
{
    if (random(2))
        set_race_name("shadow-elf");
    else
        set_race_name("half-elf");       
    set_adj(Sadj1[random(sizeof(Sadj1))]);
    add_adj(Sadj2[random(sizeof(Sadj2))]);
    set_eyes(Seyes[random(sizeof(Seyes))]);
    set_hair(Shair[random(sizeof(Shair))]);
    set_gender(random(2));
}

/* Create the npc */
void
create_monster()
{
    /* if I'm not a clone, do not proceed */
    if (!IS_CLONE)
        return;
    ::create_monster();
    /* Make sure sybarite stuff is initialized */
    ::create_sybarite();

    /* You're all individuals! */
    set_morph();

    set_name("inquisitor");
    set_long(my_long);
    add_name(({"questioner", "official", "noble", "elf"}));
    set_alignment(0);

    set_knight_prestige(500);   

    MAKE_SYBARITE; 
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_leftover("/d/Avenir/inherit/leftover", "heart",1, "", 0,0);
    add_leftover("/d/Avenir/inherit/leftover", "intestine",1, "", 0,0);    

    set_skill(SS_DEFENCE, random(20) + 60);
    set_skill(SS_2H_COMBAT, random(20) + 60);
    set_skill(SS_WEP_SWORD, random(20) + 60);
    set_skill(SS_AWARENESS, random(40)+ 60);
    set_skill(SS_WEP_KNIFE, random(20) + 70);
    set_skill(SS_BLIND_COMBAT, random(20)+ 40);
    set_all_attack_unarmed(30, 30);
    set_all_hitloc_unarmed(15);
    set_appearance_offset(-10); // always good-looking

    default_config_npc(random(60) + 100);

    set_act_time(3);
      add_act("sigh .");
      add_act("smile grim");
      add_act("emote smiles to "+ OBJECTIVE(TO) +"self over some "+
          "private amusement.");
      add_act("emote looks as though "+ PRONOUN(TO) +" is prepared "+
          "to eviscerate you on the spot.");
      add_act("emote looks at you from the corner of "+ POSSESS(TO) +
          " eyes.");
    set_cact_time(7);
      add_cact("glare mercilessly enemy");
      add_cact("slaugh");
      add_cact("say Flee from me and I will not follow. You are not "+
          "a foe worthy of giving chase.");
      add_cact("say From whence thou came, so shall I return you.");
      add_cact("say I will feed your corpse to a troloby!");

    set_default_answer(VBFC_ME("what_me"));
    add_ask(({"task", "job", "quest", "help", "coin"}), 
        VBFC_ME("give_task"));
    add_ask(({"brum", "is brum the most qualified",
        "if brum is the most qualified",
        "is it brum", "if it is brum"}), 
        VBFC_ME("brum_check"));
    add_ask(({ "dibron", "is dibron the most qualified", 
        "if dibron is the most qualified",
        "is it dibron", "if it is dibron"}), 
        VBFC_ME("dibron_check"));
    add_ask(({"maxild", "is maxild the most qualified", 
        "if maxild is the most qualified",
        "is it maxild", "if it is maxild"}), 
        VBFC_ME("maxild_check"));
    add_ask(({ "norlayo", "is norlayo the most qualified", 
        "if norlayo is the most qualified",
        "is it norlayo", "if it is norlayo"}), 
        VBFC_ME("norlayo_check"));


    /* So we help other sybarite npcs in combat */
    set_helper();
}

string
my_long()
{
    string  str, poss;
    poss =TO->query_possessive(); 

    str =  capitalize(TO->query_pronoun()) +" is "+ 
           LANG_ADDART(implode(query_adjs(), " ")) +" "+
           query_race_name()+".\n";

    str += capitalize(TO->query_pronoun()) +" has the grace and "+
           "dignity of bearing characteristic of shadow-elves. "+
           capitalize(poss) +" skin is so pale and translucent "+
           "it is tinted blue in some places by "+ poss +" veins.\n"+
           capitalize(TO->query_pronoun()) +" appears to be "+ 
           "an inquisitor, charged with finding answers.\n"+ 
           capitalize(poss) +" long, "+ query_hair() +" hair is "+
           "held at "+ poss +" nape by a gold trefoil clasp.\n"+
           capitalize(TO->query_pronoun()) +" has "+ query_eyes() 
           +" eyes.\n";
    return str;
}

/*
 * equip_me is called in the npc when it is cloned by the 
 * placer module.
 */
void 
equip_me()
{
    object armour, baldric, boots, cane, codpiece, dagger;
    int i;

    seteuid(getuid());

    i = random(10);
    MONEY_MAKE_SC(i)->move(TO);
    MONEY_MAKE_PC(random(3))->move(TO);

    armour = clone_object(HOLM + "obj/armour");
    armour->move(TO);

    boots = clone_object(HOLM + "obj/boots");
    boots->move(TO);

    cane = clone_object(BAZAAR +"Obj/wield/cane");
    cane->move(TO);

    if (TO->query_gender == G_MALE)
    {
        codpiece = clone_object(BAZAAR +"Obj/worn/codpiece");
        codpiece->move(TO);
    }
    else
    {
        codpiece = clone_object(BAZAAR +"Obj/worn/jpants");
        codpiece->move(TO);
    }

    dagger = clone_object(COM +"obj/knife");
    dagger->move(TO);
    
    command("wear all");
    command("wield all");

    refresh_living();
}

/* quest code*/
string
give_repair_quest(object player)
{
    set_alarm(2.0, 0.0, &command("smile thoughtf"));
    set_alarm(4.0, 0.0, &command("say How good are you at deductive reasoning?"));
    set_alarm(6.0, 0.0, &command("say These four craftsmen were recommended to "+
        "do the repairs to the Statue of the High Inquisitor."));
    set_alarm(8.0, 0.0, &command("say When it was discovered that some of "+
        "their statements were not truthful, they were brought before me."));
    set_alarm(9.0, 0.0, &command("emote smiles at the prisoners."));
    set_alarm(10.0, 0.0, &command("say I have determined that each "+
        "of them makes two true statements and one false statement."));
    set_alarm(12.0, 0.0, &command("say You are welcome to question "+
        "them and determine who is most qualified."));
    set_alarm(16.0, 0.0, &command("say When you think you know, ask me "+
        "if that person is the most qualified."));
    return "";
}

void
give_token(object from)
{
    object token;
    string str;

    token = clone_object("/d/Avenir/common/obj/syb_coin");
    token->move(from);
    str = token->short();
    from->catch_msg(QCTNAME(TO) + " flips you " + str + ".\n");
    tell_room(ENV(TO), QCTNAME(TO) + " flips "+
        str +" to " + QTNAME(from) + ".\n", ({ from }));
}


void
reward_repair_quest(object player)
{
    reward_quest("Repair Statue", player, KESTARES_GROUP, REPAIR, R_EXP);

    seteuid(getuid(TO));
 
    SCROLLING_LOG(QUEST_FILE, QCTNAME(player) +
        " determined who could repair the statue and was rewarded "+
        R_EXP+" exp." );
    tell_object(player,"You feel a bit more experienced!\n");
    say(QCTNAME(player) + " got a nice reward.\n");
    give_token(player);
}

string
norlayo_check()
{
    object player;
    int qnum;
    player = this_player();
    qnum = QNUM(TP);

    if (player->test_bit("Avenir",KESTARES_GROUP,REPAIR))
    {
        set_alarm (2.0, 0.0, &command("say Hmm...yes, you've "+
            "told me before."));
        return "";
    }
    if (player->query_prop(REPAIR_QUESTOR))
    {
        set_alarm (2.0, 0.0, &command("say I'm not interested "+
            "in guesses. Think about it and try me another day."));
        return "";            
    }
    if (QNUM(TP) == 1)
    {
        set_alarm (2.0, 0.0, &command("smile admir"));
        set_alarm (3.0, 0.0, &command("say You are a bright one."));
        set_alarm (4.0, 0.0, &reward_repair_quest(player));
        return "";
    }
    else
    {
        player->add_prop(REPAIR_QUESTOR, 1);
        set_alarm (2.0, 0.0, &command("sneer"));
        set_alarm (3.0, 0.0, &command("say You're not very strong "+
            "on logic, are you?."));
        return "";
    }        
}

string
brum_check()
{
    object player;
    int qnum;
    player = this_player();
    qnum = QNUM(TP);

    if (player->test_bit("Avenir",KESTARES_GROUP,REPAIR))
    {
        set_alarm (2.0, 0.0, &command("say Hmm...yes, you've "+
            "told me before."));
        return "";
    }
    if (player->query_prop(REPAIR_QUESTOR))
    {
        set_alarm (2.0, 0.0, &command("say I'm not interested "+
            "in guesses. Think about it and try me another day."));
        return "";            
    }
    if (QNUM(TP) == 2)
    {
        set_alarm (2.0, 0.0, &command("smile admir"));
        set_alarm (3.0, 0.0, &command("say You are a bright one."));
        set_alarm (4.0, 0.0, &reward_repair_quest(player));
        return "";
    }
    else
    {
        player->add_prop(REPAIR_QUESTOR, 1);
        set_alarm (2.0, 0.0, &command("sneer"));
        set_alarm (3.0, 0.0, &command("say You're not very strong "+
            "on logic, are you?."));
        return "";
    }        
}

string
dibron_check()
{
    object player;
    int qnum;
    player = this_player();
    qnum = QNUM(TP);


    if (player->test_bit("Avenir",KESTARES_GROUP,REPAIR))
    {
        set_alarm (2.0, 0.0, &command("say Hmm...yes, you've "+
            "told me before."));
        return "";
    }
    if (player->query_prop(REPAIR_QUESTOR))
    {
        set_alarm (2.0, 0.0, &command("say I'm not interested "+
            "in guesses. Think about it and try me another day."));
        return "";            
    }
    if (QNUM(TP) == 3)
    {
        set_alarm (2.0, 0.0, &command("smile admir"));
        set_alarm (3.0, 0.0, &command("say You are a bright one."));
        set_alarm (4.0, 0.0, &reward_repair_quest(player));
        return "";
    }
    else
    {
        player->add_prop(REPAIR_QUESTOR, 1);
        set_alarm (2.0, 0.0, &command("sneer"));
        set_alarm (3.0, 0.0, &command("say You're not very strong "+
            "on logic, are you?."));
        return "";
    }        
}

string
maxild_check()
{
    object player;
    int qnum;
    player = this_player();
    qnum = QNUM(TP);

    if (player->test_bit("Avenir",KESTARES_GROUP,REPAIR))
    {
        set_alarm (2.0, 0.0, &command("say Hmm...yes, you've "+
            "told me before."));
        return "";
    }
    if (player->query_prop(REPAIR_QUESTOR))
    {
        set_alarm (2.0, 0.0, &command("say I'm not interested "+
            "in guesses. Think about it and try me another day."));
        return "";            
    }
    if (QNUM(TP) == 4)
    {
        set_alarm (2.0, 0.0, &command("smile admir"));
        set_alarm (3.0, 0.0, &command("say You are a bright one."));
        set_alarm (4.0, 0.0, &reward_repair_quest(player));
        return "";
    }
    else
    {
        player->add_prop(REPAIR_QUESTOR, 1);
        set_alarm (2.0, 0.0, &command("sneer"));
        set_alarm (3.0, 0.0, &command("say You're not very strong "+
            "on logic, are you?."));
        return "";
    }        
}

string
give_task()
{
    int qnum;
    qnum = QNUM(TP);

    QDB(this_player()->query_name() +", defile, "+ qnum);

    if (!CAN_SEE(TO, TP))
    {
        command("emote looks around suspiciously");
        command("say The air speaks not in the voice of a "+
            "God.");
        command("say You are the spawn of a coward and a thief!");
        return "";
    }
    if(!TP->test_bit("Avenir",KESTARES_GROUP,REPAIR))
    {
        give_repair_quest(TP);
        return "";
    }
    if (IS_SYBARITE(TP))
    {
        command("say to "+ TP->query_real_name() + 
            " I require no further assistance.");
        return "";
    }
    else     
    {
        command("say What are you doing here?");
        command("say Leave!");
        return "";
    }
}

string
what_me()
{
    if (!CAN_SEE(TO, TP))
    {
        command("emote looks angrily about.");        
        return "";
    }
    switch(random(4))
    {
        case 0:
            command("say -I- ask the questions here!");
            break;
        case 1:
            command("say You are not permitted to ask that question.");
            break;
        case 2:
            command("emote laughs the chilling laugh of one who has "+
                "known total fear and no longer fears anything.");
            break;
        case 3:
            command("say You dare ask questions of an Inquisitor?!");
            break;
    }
    return "";    
}

void
check_meet(object tp)
{
    string  occ;
    int     i;
    i = random(6);
    alarm_id = 0;

    if (!present(tp, environment(TO)))
        return;

    if (IS_SYBARITE(tp))
    {
        command("say to "+ tp->query_real_name() +
            " Your business will have to wait, friend. Please leave.");
        return;
    }
    else
    {    
        if (i > 3)
        {
            command("say to "+ tp->query_real_name() +
                " Leave, or I'll have you whipped at the pillory.");
            return;
        }
    }
}

void
init_living()
{
    ::init_living();

    if (interactive(TP) && CAN_SEE(TO, TP))
    {
        if (alarm_id)
            return;
        else
            alarm_id = set_alarm(2.0, 0.0, &check_meet(TP));
        return;
    }
}  

void
set_helper()
{
    string *actions = ({ "shout Guards! Get this vermin out of here!",
                         "say It sounds like there's trouble nearby!",
                         "say Just as I suspected!",
                         "Let us dance 'til death." });

    set_helper_friends( ({ "adjudicator", "inquistor" }) );
}

int
special_attack(object victim)
{
    switch (random(10))
    {
        case 2: command("heal");
            return 0;        
        case 3: command("neck");
            return 1;
        case 4: command("neck");
            return 1;
        case 5: command("skick");
            return 1;
        case 6: command("skick");
            return 1;
        case 9: command("cure");
            return 0;
        default: 
    }
    return 0;
}

