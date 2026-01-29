/*
 * Jan 19, 2019, Finwe: Fixed race check bug for quest
 */

#include "/d/Shire/sys/defs.h"
#include "../local.h"
#include <formulas.h>
#include "/sys/macros.h"
#include "/d/Shire/rivendell/npc/elfmaker.h"

inherit "/d/Shire/rivendell/npc/elfmaker.c";

#define ELLADAN_QUEST    "forest"

void
create_elf()
{
    set_race_name("human");
    set_name("elladan");
    set_living_name("elladan");
    set_adj(({"cautious","grim"}));

    set_learn_pref(({ 0,0,0,1,1,1 }));


    set_stats(({
        90+random(20),
        90+random(20),
        90+random(20), 
	     90+random(20), 
        90+random(20), 
        90+random(20)}));

    set_alignment(700 +random(300));

    set_base_stat(SS_OCCUP, query_average_stat()+random(20));
    set_skill(SS_WEP_SWORD,                  90);
    set_skill(SS_2H_COMBAT,                  90);
    set_skill(SS_DEFENCE,                    70);
    set_skill(SS_PARRY,                      70);
    set_skill(SS_AWARENESS,                  70);
    set_skill(SS_SPELLCRAFT,                100);
    set_skill(SS_ELEMENT_EARTH,              80);
    set_skill(SS_ELEMENT_LIFE,               80);
    set_skill(SS_ELEMENT_FIRE,               80);
    set_skill(SS_FORM_CONJURATION,   80);
    set_skill(SS_FORM_ABJURATION,    80);
    set_skill(SS_FORM_DIVINATION,    90);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop(CONT_I_WEIGHT, 100*1000);
    add_prop(CONT_I_HEIGHT, 190);
    add_prop(LIVE_I_SEE_DARK, 20);

    add_prop(LIVE_I_QUICKNESS, 150); /* speed up attacks */
    set_long("This human looks grim and cautious. His features " +
        "are fair yet seems to be part human. He seems to be " +
        "watching for something while hidden here " +
        "in the forest. ");

    set_act_time(NPC_TELL_TIME);
    set_cact_time(200);

    add_act("say Orcs and trolls have been seen here.");
    add_act("say The trolls are becoming bolder.");
    add_act("say We have reports the trolls are raiding villages now.");
    add_act("say It gets lonely hidden here.");
    add_act("emote peers into the distance.");
    add_act("emote listens intently to something in the distance");
    add_act("emote motions you to be quiet.");
    add_act("emote looks at the road below.");
    add_act("emote looks to the west and sighs forlornly.");

    add_cact("say Begone foul one!");
    add_cact("shout You shall pay dearly for this folly!");
    add_cact("say How dare you attack me!");
    add_cact("emote stares at you in disbelief.");
    add_cact("emote prays to Elbereth for strength.");
    add_cact("emote grips his sword and attacks you with renewed courage.");

    set_alarm(1.0,0.0,"arm_me");  

    add_ask(({"reports", "report", "help"}), "@@ask_reports");
//    add_ask("quest", "@@ask_quest");

}


void
arm_me()
{
    object sword, bracers, greaves, chainmail, shield;

    FIXEUID;
    sword = clone_object(RWEP_DIR+"longsword");
    sword->move(TO);

    bracers = clone_object(RARM_DIR+"bracers");
    bracers->move(TO);

    greaves = clone_object(RARM_DIR+"greaves");
    greaves->move(TO);

    chainmail = clone_object(RARM_DIR+"chainmail");
    chainmail->move(TO);

    shield = clone_object(RARM_DIR+"shield");
    shield->move(TO);

    command("wield all");
    command("wear all");
  }




public int
special_attack(object enemy)
{
    if (!present("_imladris_elf_paralyze_", enemy) && !random(10)) 
    { 
	clone_object(ROBJ_DIR + "stun.c")->move(enemy, 1); 
	enemy->catch_tell("\nYou are hit on the head by " + short()+".\n"+
	  "You are knocked unconcious!\n\n");
    }  
}

string ask_reports()
{
    object report;
 
// these players can't do the quest    
//    if (TP->query_race() == "goblin")
    if(TP->query_race_name() == "goblin")
    {
        command("say Begone foul creature!");
	    return "";
    }
    // Check alignment 
    if (TP->query_alignment() <= -150)
    {
        command("say Your heart is dark and can't be trusted");
	    return "";
    }

    // Check if undead
    if (TP->query_prop(LIVE_I_UNDEAD))
    {
        command("say Minion of the Dark One, begone now!");
	    return "";
    }

/*
    if (TP->query_prop("_elladan_quest_"))
    {
        command("say I don't know what you are talking about.");
        return "";
    }

*/

    if(TP->query_prop("_elladan_report_given_"))
    {
        command("say I have given you my report already. Have you " +
            "lost it? Worse, did it fall into the wrong hands? " +
            "Begone! I shall not help you further. You have " +
            "betrayed our trust!");
        return "";

    }

    if (TP->query_prop("_elladan_quest_"))
    {
        command("say Hail in the name of the Free peoples!");
        command("say Orcs, trolls and other servants of the " +
            "Dark One have been travelling this way with more " +
            "frequency. Fortunately, Elbereth has smiled on us " +
            "here and kept us hidden from them. Nonetheless, I " +
            "fear they may soon attack.");
        command("emote sighs sadly at the thought.");
        command("say however, I have kept a log of what enemies " +
            "have passed this way, and need to have this log " +
            "returned to Elrond. Since he has sent you, I " +
            "believe you are trustworthy for he would not send " +
            "enemies out to assist our cause.");
        command ("say Return with haste and don't let this " +
            "report fall into the wrong hands. May your " +
            "journies be safe and may Elbereth light your path!");
        command("emote looks to the west and sighs deeply.");
        report = clone_object(ROBJ_DIR + "report");
        report->move(TP);
        write("Elladan gives you something.\n");
        TP->add_prop("_elladan_report_given_", 1);
        return "";
    }

    if (CHECK_QUEST(TP, ELLADAN_QUEST))
    {
        command("say Thank you for your offer, we need all " +
            "the strength we can muster but you have already " +
            "assisted us.");
        return "";
    }

    command("emote motions you to be silent.");
    return "";
}
/*
string ask_quest()
{
    command{"say I do not know what you are talking about.");
    return "";
}
*/