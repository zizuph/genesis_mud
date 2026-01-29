/*
 *  /d/Kalad/common/farmland/camps/npc/goblin_commander.c
 *
 *  The commander of the Red fang training camp is the
 *  hardest monster in the camp.
 *  Created October 2015, by Andreas Bergstrom ( Zignur )
 * 
 * Cotillion - 2019-02-21 
 * - Take rarity into account when distributing gems
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

/* Global variables */
string *ArrAdj1 = ({ "huge"});
string *ArrAdj2 = ({ "massive"});
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
    add_name("commander");
    set_race_name("goblin");
    add_name(({ "goblin", "warrior","commander", REDFANG_CAMP_NPC }));
    add_adj(({ Adj1, Adj2 }));

    set_short( Adj1+ " "+ Adj2 +" goblin");
    
    set_long("A " +Adj1 + " " + Adj2 + " goblin. This is a very"
      + " formidable fighter, he is clearly the commander of this" 
      + " camp. You get a feeling that this is the right person"
      + " to to slay if you want to deliver a brutal blow to the Red Fang."
      + " It might not be the smartest move to attack this fearsome"
      + " fighter though.\n");

    set_stats( ({ NPC_GOBLIN_COMMANDER_STR,
                  NPC_GOBLIN_COMMANDER_DEX,
                  NPC_GOBLIN_COMMANDER_CON,
                  NPC_GOBLIN_COMMANDER_INT,
                  NPC_GOBLIN_COMMANDER_WIS,
                  NPC_GOBLIN_COMMANDER_DIS,
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
    add_act("say Death to the filthy Thanars!");
    add_act("emote barks a command.");
    add_act("emote looks around for something to kill");
    
    add_cact("say Robbing that miner sure was rewarding!");
    add_cact("emote laughs evilly.");
    add_cact("emote snorts wickedly.");

    set_default_answer(VBFC_ME("default_answer"));
    remove_prop(LIVE_M_NO_ACCEPT_GIVE);

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

    /* Add some gems */
    object gem;
    /* This is the boss mob in the camp so we give him good gems */
    
    if (random(10)) /* 10% chance to get a ext rare gem */
    {
        gem = RANDOM_GEM(GEM_EXTREMELY_RARE);
        gem->move(this_object());
    }
    
    gem = RANDOM_GEM_BY_RARITY(GEM_VERY_RARE);
    gem->move(this_object());                   
    
    gem = RANDOM_GEM_BY_RARITY(GEM_SOMEWHAT_RARE);
    gem->move(this_object());
    
    gem = RANDOM_GEM_BY_RARITY(GEM_SLIGHTLY_RARE);
    gem->move(this_object());                   
    
    gem = RANDOM_GEM_BY_RARITY(GEM_SLIGHTLY_COMMON);
    gem->move(this_object());                   
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
    // Keep track of the number of killed commanders
    int killed;
    if (interactive(killer))
    {
        killed = killer->query_prop(RF_COMMANDER_KILLED) + 1;
        killer->add_prop(RF_COMMANDER_KILLED, killed);
    }    
    
    ::do_die(killer);
}
/* do_die */

