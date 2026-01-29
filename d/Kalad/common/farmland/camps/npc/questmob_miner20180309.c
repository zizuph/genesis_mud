/*
 *  /d/Kalad/common/farmland/camps/npc/questmob_miner.c
 *
 *  For the quest Miner's revenge
 *  A vengeful miner that got robbed by the Red Fangs.
 *  He will offer one quest for adventurers that wish to 
 *  help him get his revenge.
 *
 *  Created Feb 2016, by Andreas Bergstrom ( Zignur )
 *  2018-02-06 Zignur Changed some things based on Gorboths feedback.
 */
#include "../defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include "../defs.h"
#include "/d/Kalad/defs.h"
#include <language.h>

inherit "/std/monster";


#define QUEST_NAME "miners_revenge"
#define RF_ASKED_HELP "_rf_asked_help"


/* Prototypes */
public void        arm_me();
public string      default_answer();
public string      task_help();
public string      task_reward();
public void        quest_progress();
public void        reset_miner();
public void        reward_quest();
public void        remove_props();

/* Global variables */
string *ArrAdj1 = ({ "bruised"});
string *ArrAdj2 = ({ "bloody"});
string Adj1 = one_of_list(ArrAdj1);
string Adj2 = one_of_list(ArrAdj2); 
  
 /* Variables used for the quest */
int burnedCamp = 0;
int killedWarriors =0;
int killedTrainers =0;
int killedCommanders =0;
int killedWolves =0;
/* Keep track if the miner is talking or not. */
public int MINER_IS_BUSY = 0;
 

/*
 * Function name:        create_monster
 * Description  :        The constructor for the monster
 */
public void
create_monster  ()
{   
    set_name("miner");
    set_race_name("half-dwarf");
    add_adj(({ Adj1, Adj2 }));

    set_short( Adj1+ " "+ Adj2 +" half-dwarf");
    
    set_long("A " +Adj1 + " " + Adj2 + " half-dwarven miner. This"
      + " poor half-dwarf seems to have been beated and robbed. His" 
      + " face is bruised and bleeding. There is emotion in the eyes of" 
      + " this fellow that betrays a deep need for revenge. You wonder"
      + " if perhaps, he might appreciate being asked for help.\n");


    set_stats( ({ 50,50,50,50,50,50}) );
                  
    set_skill(SS_WEP_AXE,      25);
    set_skill(SS_AWARENESS,    60);
    set_skill(SS_DEFENCE,      25);
    set_skill(SS_PARRY,        25);


    add_ask( ({ "task", "quest", "help","job" }), VBFC_ME("task_help"));
    
    add_ask( ({ "reward"}), VBFC_ME("task_reward"));
        
    add_ask( ({ "goblins", "redfang", "redfangs","camp"}),
        "say Those filthy redfangs robbed me! They have a camp northwest"
      + " from here. I want them to pay for what they did,"
      + " I want all of them dead and their camp burned to the ground!"
      + " If you want to assist me in this just <ask miner help>", 1);
        
    add_ask( ({ "robbed", "robbery", "beaten"}),
        "say Those filthy redfangs robbed me! They beat me up and stole"
      + " all of my precious gems. I want them to pay for what they did,"
      + " I want all of them dead and their camp burned to the ground!"
      + " if you want to assist me in this just <ask miner help>", 1);
        
    add_ask( ({ "gem", "gems", "loot"}),
        "say Those filthy creates stole all my hard earned gems!"
      + " If you help me get my revenge, I will let you keep any"
      + " any gems you find. If you want to assist me in this"
      + " just <ask miner help>", 1);
          
      
    set_act_time(40 + random(10));
    add_act("emote curses the redfangs that robbed him.");
    add_act("emote looks around for someone to help him.");
    add_act("emote winces in pain.");
    add_act("emote tends to one of his bruises.");
    add_act("Will you help me?");
    add_act("say Im looking for someone to help me get revenge.");
    add_act("say Those filthy goblins will pay for that they did!");
    add_act("say They stole all my gems, filthy creatures!"); 
    set_default_answer(VBFC_ME("default_answer"));
    
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK, 1);
  
    /* Quest master */
    add_prop(OBJ_M_NO_ATTACK,"Umm... no, You " +
     "do not have the self-discipline to dare!\n");
   
    setuid();
    seteuid(getuid());
} /* create_monster  */


/*
 * Function name:        arm_me
 * Description  :        set up the npc with any gear it needs
 */
public void
arm_me()
{
    equip(({
        WEP_DIR + "miner_hatchet",
        ARM_DIR + "miner_chest",
        ARM_DIR + "miner_cloak",
       }));         
    command("wear all");
    command("wield all");
    
} /* arm_me */

/* 
 * Function name:       default_answer
 * Description  :       give the default response to questions
 */
public string
default_answer()
{
    string  answer = one_of_list( ({
        "Try <ask miner help> if you want to help me.",
        "Ah are you here to assist me? Try <ask miner help>.",
        "I will get my vengeance! <ask miner help> if you want to aid me.",
        }) );

    command("say " + answer);
    return "";

} /* default_answer */

/* 
 * Function name:       task_help
 * Description  :       settup the quest
 */
public string
task_help()
{
    
     /* You have to kill 50 warriors, 10 trainers,5 wolves 
     1 commander and burn down the camp to finish the quest
     if this isnt done the quest_progress function will be
     called and it will report the status on the quest */
    
    /* Make sure he is not already talking to someone */  
    if(MINER_IS_BUSY == 1) {
        return "";
    }
    
    /* Set the MINER_IS_BUSY is busy flag 1 */
    MINER_IS_BUSY = 1;
    
    /* Give a special dialog when you already asked for help */
    if(this_player()->query_prop(RF_ASKED_HELP))
    {
        command("say Didn't we go over this already? Listen closely"
               + " this time!\n");
    }
    
    command("emote nods slowly.");
    set_alarm(1.0, 0.0, &command("say Excellent! Now listen up, this" 
          + " is what I need you to do."));          
    set_alarm(3.0, 0.0, &command("say Those foul goblins robbed me,"
          + " they stole my gems! Make them to suffer for what they" 
          + " have done."));
    set_alarm(5.5, 0.0, &command("emote wipes away some blood from"
          + " his broken lips."));
    set_alarm(11.0, 0.0, &command("say Kill ALL of them, I want you"
          + " to seek out the Red Fang camp. It's located northwest"
          + " of here, once there I want you to slaughter and burn"
          + " all of them!"));
    set_alarm(13.0, 0.0, &command("emote pauses and tries to catch"
          + " his breath."));   
    set_alarm(16.0, 0.0, &command("say Slay fifty warriors, ten"
          + " trainers, and five wolves. Butcher their commander"
          + " and finally burn their wretched camp to the ground."));
    set_alarm(18.0, 0.0, &command("emote cackles bloodthirstily."));
    set_alarm(22.0, 0.0, &command("say Return to me and <ask miner"
         + " reward> when this is done. Show no mercy, slay them all"
         + " my friend."));
    
    /* Make sure we can speak to him again when he is done */
    set_alarm(23.0, 0.0,reset_miner);
    
    /* Add a prop so the he knows that the player already asked
       him about help */
    this_player()->add_prop(RF_ASKED_HELP, 1);
    return "";

} /* task_help */

/* 
 * Function name:       task_reward
 * Description  :       Handles the reward part of the quest
 */
public string
task_reward()
{
    /* Make sure he is not already talking to someone */  
    if(MINER_IS_BUSY == 1) {
        return "";
    }
    
    /* Set the MINER_IS_BUSY is busy flag 1 */
    MINER_IS_BUSY = 1;
    
    /* Reset the quest variables */
    burnedCamp = 0;
    killedWarriors =0;
    killedTrainers =0;
    killedCommanders =0;
    killedWolves =0;
    
    /* Get all the quest related props */
    
    burnedCamp = this_player()->query_prop(RF_CAMP_BURNED);    
    killedWarriors = this_player()->query_prop(RF_WARRIORS_KILLED);
    killedTrainers = this_player()->query_prop(RF_TRAINERS_KILLED);
    killedCommanders = this_player()->query_prop(RF_COMMANDER_KILLED);
    killedWolves = this_player()->query_prop(RF_WOLVES_KILLED);
    
    
    /* See how much of the quest that is done */
    
    /* You have to kill 50 warriors, 10 trainers,5 wolves 
    1 commander and burn down the camp to finish the quest
    if this isnt done the quest_progress function will be
    called and it will report the status on the quest */
    
    if(burnedCamp ==0)
    {
        quest_progress();
        return "";
    }
   
    if(killedWarriors < 49)
    {
        quest_progress();
        return "";
    }
   
    if(killedTrainers < 9)
    {
        quest_progress();
        return "";
    }
    
    if(killedCommanders == 0)
    {
        quest_progress();
        return "";
    }
   
    if(killedWolves < 4)
    {
        quest_progress();
        return "";
    }
   
    /* If we come this far it means that the quest is done */
    set_alarm(1.0, 0.0, &command("emote smiles showing several"
          + " smashed teeth."));
    set_alarm(3.0, 0.0, &command("say Wonderful! You sure showed"
          + " those bastards!"));
    set_alarm(5.0, 0.0, &command("say I hope they suffered"
          + " greatly."));
    set_alarm(7.0, 0.0, &command("emote winces in pain as he coughs"
          + " loudly."));
    /* See if quest xp will be given or not */
    set_alarm(10.0, 0.0,reward_quest);
 
    set_alarm(13.0, 0.0, &command("say I am forever in your debt, be" 
          + " my well friend."));
    set_alarm(16.0, 0.0, &command("emote smiles thankfully."));
    
    /* Make sure we can speak to him again when we are done */
    set_alarm(20.0, 0.0,reset_miner);
    
    return "";

} /* task_reward*/

/*
 * Function name:        quest_progress
 * Description  :        reports the progress of the quest
 */
public void
quest_progress()
{   
    command("say You are not yet finished my friend.");
    set_alarm(3.0, 0.0, &command("emote coughs up a mouthful blood"
          + " and spits it out."));
    set_alarm(6.0, 0.0, &command("say I have watched your progress"
          + " and so far... "));
    set_alarm(7.0, 0.0, &command("say You have killed:"));
    set_alarm(8.0, 0.0, &command("say " + LANG_NUM2WORD(killedWarriors) + 
        " warriors."));
    set_alarm(9.0, 0.0, &command("say " + LANG_NUM2WORD(killedTrainers) + 
        " trainers."));
    set_alarm(10.0, 0.0, &command("say " + LANG_NUM2WORD(killedWolves) + 
        " wolves."));
    set_alarm(12.0, 0.0, &command("emote seems to struggle to catch"
          + " his breath."));
              
    if(killedCommanders == 0)
    {
         set_alarm(15.0, 0.0, &command("say You have yet not killed"
               + " the filthy commander."));
    }
    else
    {
         set_alarm(15.0, 0.0, &command("say The wretched commander"
               + " has been slain."));
    }        
    
    command("emote groans in pain and touches one of his broken ribs.");
    
    if(burnedCamp == 0)
    {
         set_alarm(17.0, 0.0, &command("say You have to make them"
               + " burn! Burn the camp down!"));
    }
    else
    {
         set_alarm(17.0, 0.0, &command("say Excellent you have burned"
               + " down the camp, now finish the job!"));
    }  

    /* Make sure we can speak to him again when we are done */
    set_alarm(18.0, 0.0,reset_miner);    
    
    return;
    
} /* quest_progress */


/*
 * Function name:        reset_miner
 * Description  :        resets the miner so he can speak again
 */
public void
reset_miner()
{
    /* Make is to the miner can speak again. */
    MINER_IS_BUSY = 0;
     
    return;
    
} /* reset_miner */


/*
 * Function name:        reward_quest
 * Description  :        Rewards quest xp if its not already done
 */
public void
reward_quest()
{  
    /* See if the quest have been solved before */

    if (this_player()->test_bit("Kalad", 1, 15))
    {
        
        /* No further exp will be given */
        this_player()->catch_msg("You get a"
             + " feeling you have done this quest before.\n");    
    }
    else
    {
        /*Quest not done before give quest xp and set bit */
        this_player()-> add_exp_quest(1500);
        this_player()->set_bit(1, 15);
        this_player()->catch_msg("You feel more"
              + " experienced!\n");
    
        /* Log who solves the quest */
        seteuid(getuid(TO));
        log_file(QUEST_NAME, extract(ctime(time()),4,15) + " "+
        capitalize(TP->query_real_name()) + " rewarded with 1500 xp,"+
        "<"+TP->query_average_stat()+"> average stats.\n");
    }
    
    /* Remove all the quest props from the player */
    remove_props();
    
} /* reward_quest */


 /*
 * Function name:        remove_props
 * Description  :        remove the quest props in the player when the
 *                       quest is done
 */
public void
remove_props()
{
    /* Remove all the quest props from the player */
    this_player()->remove_prop(RF_CAMP_BURNED);    
    this_player()->remove_prop(RF_WARRIORS_KILLED);
    this_player()->remove_prop(RF_TRAINERS_KILLED);
    this_player()->remove_prop(RF_COMMANDER_KILLED);
    this_player()->remove_prop(RF_WOLVES_KILLED);
 
    return;
    
} /* remove_props */


