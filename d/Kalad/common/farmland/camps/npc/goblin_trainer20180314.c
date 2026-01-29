/*
 *  /d/Kalad/common/farmland/camps/npc/goblin_trainer.c
 *
 *  A red fang trainer, a slightly tougher monster
 *  in the Red Fang camp in Kalad
 *
 *  Created October 2015, by Andreas Bergstrom ( Zignur )
 */
#pragma strict_types
#include "../defs.h"
inherit NPC_DIR + "std_redfang_camp_npc";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Genesis/gems/gem.h"


/* Prototypes */
public void        create_redfang_camp_npc  ();
public void        arm_me();
public string      default_answer();
public void        add_introduced(string name);
public void        do_die(object killer);

/* Global variables */
string *ArrAdj1 = ({ "horrible","wicked","scary","fearsome","large"});
string *ArrAdj2 = ({ "tall","massive","strong","brutal","foul" });
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
    add_name("trainer");
    set_race_name("goblin");
    add_name(({ "goblin", "warrior","trainer", REDFANG_CAMP_NPC }));
    add_adj(({ Adj1, Adj2 }));

    set_short( Adj1+ " "+ Adj2 +" goblin");
    
    set_long("A " +Adj1 + " " + Adj2 + " goblin warrior. This must"
      + " be one of the trainers of the Red Fang, that are" 
      + " teaching the new recruits how to fight. His dominating"
      + " presence and the way he moves clearly shows that"
      + " you should think twice before attacking him.\n");

    set_stats( ({ NPC_GOBLIN_TRAINER_STR,
                  NPC_GOBLIN_TRAINER_DEX,
                  NPC_GOBLIN_TRAINER_CON,
                  NPC_GOBLIN_TRAINER_INT,
                  NPC_GOBLIN_TRAINER_WIS,
                  NPC_GOBLIN_TRAINER_DIS,
               }) );
                  
    set_skill(SS_WEP_SWORD,    50);
    set_skill(SS_WEP_AXE,      50);
    set_skill(SS_WEP_CLUB,     50);
    set_skill(SS_WEP_POLEARM,  50);
    set_skill(SS_WEP_KNIFE,    50);
    set_skill(SS_AWARENESS,    60);
    set_skill(SS_DEFENCE,      50);
    set_skill(SS_PARRY,        50);
    set_skill(SS_2H_COMBAT,    50);

    set_act_time(40 + random(20));
    add_act("emote barks a command to nearby trainee.");
    add_act("emote scans the camp for threats.");
    add_act("emote looks over his armours for dents.");
    add_act("emote mends a piece of broken equipment.");
    add_cact("say I will teach you filth how to fight!");
    add_cact("emote laughs evilly.");
    add_cact("emote snorts wickedly.");
    add_cact("say I will deal with you easily on my own!");
    add_cact("say Stand back! I will deal with this myself");
    
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
    
    equip( ({ ARM_DIR + "goblin_trainer_armring",
              ARM_DIR + "goblin_boots",
              ARM_DIR + "goblin_gloves",
              ARM_DIR + "goblin_bracers",
              ARM_DIR + "goblin_greaves",
              ARM_DIR + "goblin_breastplate",
              ARM_DIR + "goblin_helmet" }));
   
    command("wear all");
    command("wield all");
    
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
    // Keep track of the number of killed trainers
    int killed;
    if (interactive(killer))
    {
        killed = killer->query_prop(RF_TRAINERS_KILLED) + 1;
        killer->add_prop(RF_TRAINERS_KILLED, killed);
    }    
    
    ::do_die(killer);
}
/* do_die */

