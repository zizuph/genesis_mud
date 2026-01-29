/*
 *  /d/Kalad/common/farmland/camps/npc/goblin_warrior.c
 *
 *  A standard goblin warrior in the red fang camp in Kalad
 *
 *  Created October 2015, by Andreas Bergstrom ( Zignur )
 */
#pragma strict_types
#include "../defs.h"
#include "/d/Genesis/gems/gem.h"

inherit NPC_DIR + "std_redfang_camp_npc";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

/* Prototypes */
public void        create_redfang_camp_npc  ();
public void        arm_me();
public string      default_answer();
public void        add_introduced(string name);
public void        do_die(object killer);

/* Global variables */
string *ArrAdj1 = ({ "small","short","bony","scarred","brutal"});
string *ArrAdj2 = ({ "wicked","cruel","evil","nasty","ghastly" });
string Adj1 = one_of_list(ArrAdj1);
string Adj2 = one_of_list(ArrAdj2); 
 

/*
 * Function name:        create_redfang_camp_npc  
 * Description  :        The constructor for the monster
 */
public void
create_redfang_camp_npc  ()
{
    set_name("goblin");
    add_name("warrior");
    set_race_name("goblin");
    add_name(({ "goblin", "recruit","trainee", REDFANG_CAMP_NPC }));
    add_adj(({ Adj1, Adj2 }));

    set_short( Adj1+ " "+ Adj2 +" goblin");
    
    set_long("A " +Adj1 + " " + Adj2 + " goblin warrior. This must be one"
      + " of the new recruits for the Red Fang, He looks rather weak and" 
      + " is most likely not much of a fighter. He is snarling wickedly"
      + " showing several broken teeth in his hideous mouth.\n");

    set_stats( ({ NPC_GOBLIN_WARRIOR_STR,
                  NPC_GOBLIN_WARRIOR_DEX,
                  NPC_GOBLIN_WARRIOR_CON,
                  NPC_GOBLIN_WARRIOR_INT,
                  NPC_GOBLIN_WARRIOR_WIS,
                  NPC_GOBLIN_WARRIOR_DIS,
               }) );
                  
    set_skill(SS_WEP_SWORD,    25);
    set_skill(SS_WEP_AXE,      25);
    set_skill(SS_WEP_CLUB,     25);
    set_skill(SS_WEP_POLEARM,  25);
    set_skill(SS_WEP_KNIFE,    25);
    set_skill(SS_AWARENESS,    60);
    set_skill(SS_DEFENCE,      25);
    set_skill(SS_PARRY,        25);
    set_skill(SS_2H_COMBAT,    25);

    set_act_time(40 + random(10));
    add_act("emote looks around for something to eat.");
    add_act("emote laughs evilly.");
    add_act("emote snarls wickedly.");
    add_act("emote glares around angrily.");
    add_act("emote mutters quietly.");
    
    add_cact("say Stand back I will handle this one myself!");
    add_cact("emote cackles madly.");
    add_cact("say I will prove my worth by slaying you!");
    add_cact("say Your scalp will be a fine addition to my collection.");
    add_cact("say I kill you easily alone.");

    set_default_answer(VBFC_ME("default_answer"));

    setuid();
    seteuid(getuid());
} /* create_redfang_camp_npc  */


/*
 * Function name:        arm_me
 * Description  :        set up the npc with any gear it needs
 */
public void
arm_me()
{  
    /* Add the weapons */
    string  wep = one_of_list( ({ "sword",
                                  "mace",
                                  "axe",
                                  "dagger",
                                  "spear" }) );
                                  
    equip( ({ WEP_DIR + "goblin_" + wep  }));

    if (random(3)) /* 33% chance to get shield */
    {
        equip( ({ ARM_DIR + "goblin_shield" }));
    }
    else
    {
        wep = one_of_list( ({ "sword",
                              "mace",
                              "axe",
                              "spear",
                              "dagger" }) );
                              
       equip( ({ WEP_DIR + "goblin_" + wep  }));
    }
    
    /* Add the standard armours for the orc warriors */
    
    equip( ({ ARM_DIR + "goblin_armring",
              ARM_DIR + "goblin_boots",
              ARM_DIR + "goblin_gloves",
              ARM_DIR + "goblin_bracers",
              ARM_DIR + "goblin_greaves",
              ARM_DIR + "goblin_breastplate",
              ARM_DIR + "goblin_helmet" }));
   
    command("wear all");
    command("wield all");

    /* Add some gems */
    object gem;
    if(random(2)) /* 50 % chance to get slighlty common gems */
    {
        gem = RANDOM_GEM(GEM_SLIGHTLY_COMMON);
        gem->move(this_object());
    }
    else
    {
        gem = RANDOM_GEM(GEM_EXTREMELY_COMMON);
        gem->move(this_object());                   
    }
    
} /* arm_me */

/* 
 * Function name:       default_answer
 * Description  :       give the default response to questions
 */
public string
default_answer()
{
    string  answer = one_of_list( ({
        "Stop pestering me!",
        "I don't know.",
        "Go bother someone else with your questions.",
        "I am busy stop pestering me.",
        }) );

    command("emote snarls in anger.");
    command("say " + answer);
    return "";
} /* default_answer */


/*
 * Function name:        add_introduced
 * Description  :        provide responses to an introduction
 * Arguments    :        string name - the name of the player
 *
 */
public void
add_introduced(string name)
{
    command("sneer amus "+name);
    command("say I care nothing about your name!");
    
} /* add_introduced */


/*
 * Function name:       do_die
 * Description  :       Called when the npc is killed
 * Arguments    :       object killer - the killer
*/
public void
do_die(object killer)
{
    // Keep track of the number of killed warriors
    int killed;
    if (interactive(killer))
    {
        killed = killer->query_prop(RF_WARRIORS_KILLED) + 1;
        killer->add_prop(RF_WARRIORS_KILLED, killed);
    }    
    
    ::do_die(killer);
}
/* do_die */

