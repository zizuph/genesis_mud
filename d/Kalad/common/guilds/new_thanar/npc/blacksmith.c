/*
 *  /d/Kalad/common/guilds/new_thanar/npc/questmob_blacksmith.c
 *  Located in /d/Kalad/common/trade/cliffside/bsmith
 *
 *  For the quest Summon Thanar
 *  He wants you to help him summon Thanar to set those damned Priests
 *  straight.
 *
 *  The Medallion he gives is pretty decent a reward in and of itself.
 *  As well, this quest will act as access to be able to hire a mercenary
 *  from his brother.
 *
 *  I've added the components for remaking the Medallion which will be
 *  part of another Thanar Order Boss Fight (Pontiff) to be added down
 *  the road. Now people just get a taste and some intrigue.
 *
 *  Created April 2020, by Tim Breen ( Mirandus )
 *
 *  2021-07-14 Meton Fixed typo in line 648 (hads to hands)
 *  2021-08-14 Meton Fixed a problem in new_medallion prevented players
 *       from getting a new summon medallion if they asked help first.
 *  2021-08-15 Meton locked help/medallion if player got kill.
 */
#include "../local.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

inherit "/std/monster";
inherit "/d/Genesis/lib/intro";


#define QUEST_NAME "summon_thanar"
#define T_ASKED_HELP "_thanar_asked_help"
#define T_GO_SUMMON_THANAR "_go_summon_thanar_"
#define T_I_SUMMON_THANAR "_i_summon_thanar_"
#define I_DID_THE_SUMMON "_i_did_the_summon_"
#define I_KILLED_PRIESTS "_i_killed_priests"
#define IKNOWYOU "_i_know_you"

/* Prototypes */
public void        arm_me();
public string      default_answer();
public string      task_help();
public string      task_reward();
public string      new_medallion();
public void        quest_progress();
public void        reset_blacksmith();
public void        reward_quest();
public void        remove_fake_med();
public void        remove_notch_med();
public void        reward_quest_summon();
public void        remove_props();

/* Global variables */
string *ArrAdj1 = ({ "musclebound"});
string *ArrAdj2 = ({ "grizzly"});
string Adj1 = one_of_list(ArrAdj1);
string Adj2 = one_of_list(ArrAdj2); 
 
/* Keep track if the smith is talking or not. */
public int SMITH_IS_BUSY = 0;
 

/*
 * Function name:        create_monster
 * Description  :        The constructor for the monster
 */
public void
create_monster  ()
{   
    set_name("blacksmith");
    set_race_name("human");
    add_adj(({ Adj1, Adj2 }));

    set_short( Adj1+ " "+ Adj2 +" human");
    
    set_long("A " +Adj1 + " " + Adj2 + " human blacksmith. This"
      + " man has spent his entire life working the forge. It is apparent" 
      + " by the size of his muscles and the soot on his face. He putters" 
      + " around, mumbling to himself, and focusing on the work at hand. He"
      + " seems troubled by something and could likely use some help.\n");


    set_stats( ({ 150,150,150,150,150,150}) );
                  
    set_skill(SS_WEP_CLUB,      25);
    set_skill(SS_AWARENESS,    60);
    set_skill(SS_DEFENCE,      25);
    set_skill(SS_PARRY,        25);


    add_ask( ({ "task", "quest", "help","job" }), VBFC_ME("task_help"));
    
    add_ask( ({ "reward"}), VBFC_ME("task_reward"));
    add_ask( ({ "medallion"}), VBFC_ME("new_medallion"));
        
    add_ask( ({ "thanar", "cathedral", "priests","highlord"}),
        "say Damned Thanar priests thinking they know everything about"
        + " what Thanar wants. Walking around like they own Kalad. Bunch"
        + " of morons. If someone would help me summon Thanar I know they "
        + " would get their cumuppance. If you want to help me with those "
        + " idiots <ask blacksmith help>", 1);
  
       
      
    set_act_time(40 + random(10));
    add_act("say Damn shipment is late again.");
    add_act("say Thanar will return and those damned priests will be sorry.");
    add_act("say What is wrong with that damned high-lord.");
    add_act("emote lowers his head in prayer.");
    add_act("emote hammers out a piece of red-hot metal.");
    add_act("emote wipes sweat from his brow.");
    add_act("emote pumps the bellows."); 
    set_default_answer(VBFC_ME("default_answer"));
    
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK, 1);
  
    /* Quest master */
    add_prop(OBJ_M_NO_ATTACK,"Umm... no, You " +
     "do not have the self-discipline to dare!\n");
   
    setuid();
    seteuid(getuid());
	
    set_alarm(1.0,0.0,"arm_me");  
} /* create_monster  */


/*
 * Function name:        arm_me
 * Description  :        set up the npc with any gear it needs
 */
public void
arm_me()
{
    equip(({
        WEP + "pclub",
        ARM + "pnecklace",
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
        "Try <ask blacksmith help> if you want to help me.",
        "Ah are you here to assist me? Try <ask blacksmith help>.",
        "I will get my vengeance! <ask blacksmith help> if you want to aid me.",
        }) );

    command("say " + answer);
    return "";

} /* default_answer */
/*
 * Function name:        react_intro
 * Description  :        the npc reacts to introductions
 * Arguments    :        tp - the player
 */
void
react_intro(object tp)
{
    if (!present(tp, environment(this_object())))
    {
        command("say Another rude customer, just vanishing on me!");
        return;
    }
    
    if (this_player()->query_prop(IKNOWYOU))
    {
        command("say I already know you!");
        return;
    }

    command("say What do you want?");
    command("say Unless you are going to help me, get out of here.\n");
    this_player()->add_prop(IKNOWYOU,1);
    
}/*react_intro*/

/*
 * Function name: add_introduced
 * Description  : Called automatically from the mudlib whenever a person
 *                introduces himself to this NPC.
 * Arguments    : string name - the name of the person being introduced.
 */
 
void
add_introduced(string name)
{
    set_alarm(1.0, 0.0, &react_intro(name));
    
}/*add_introduced*/

/* 
 * Function name:       task_help
 * Description  :       settup the quest
 */
public string
task_help()
{
    
     /*You have to go to the Thanar Cathedral and kill the priests until 
       you get all four parts of the medallion. You can then attach them
       together to get the full medallion. Once done, bring it back and he
       will forge it together. You then go summon Thanar for the final piece */
    
    /* Make sure he is not already talking to someone */  
    if(SMITH_IS_BUSY == 1) {
        return "The blacksmith seems to be busy. You'd better wait a "
            + "few seconds before bothering him again.\n";
    }
    
    /* Set the SMITH_IS_BUSY is busy flag 1 */
    SMITH_IS_BUSY = 1;
    
    if (TP->test_bit("Kalad", 1, 16) && TP->test_bit("Kalad", 1, 17))
    {
        
        set_alarm(1.0, 0.0, &command("emote frowns."));
        set_alarm(3.0, 0.0, &command("say You've helped me with this "
            + "task before. Or did you forget...moron."));
                
        //Reset the blacksmith so he can talk again
        set_alarm(10.0, 0.0,reset_blacksmith); 
        return "";
           
    }

    // preventing players with the kill from getting other props.
    if (TP->query_prop(T_I_SUMMON_THANAR))
    {
        set_alarm(1.0, 0.0, &command("emote frowns."));
        set_alarm(3.0, 0.0, &command("say You already killed him. Ask "
            + "me <reward> instead.\n"));
                
        //Reset the blacksmith so he can talk again
        set_alarm(10.0, 0.0,reset_blacksmith); 
        return "";
    }

    if (TP->test_bit("Kalad", 1, 16) && !TP->query_prop(T_GO_SUMMON_THANAR))
    {
        set_alarm(3.0, 0.0, &command("say Looks like you've manged to help"
        + " with collecting the medallion, but haven't yet summoned Thanar."
        + " Let's recap and get you going."));
        set_alarm(5.0, 0.0, &command("say Take the medallion with you as"
        + " you will need it when you go summon Thanar.\n\nGo to the Cathedral "
        + " and find the ritual chamber. Use it to summon him. Let's finish this."
        + " \n\nJust be warned. This battle is mighty dangerous. Thanar does not"
        + " take lightly to those who challenge him. Be prepared for you may"
        + " be walking to certain death."));
        this_player()->add_prop(T_GO_SUMMON_THANAR, 1);
        set_alarm(7.0, 0.0,reset_blacksmith);
        return "";

    }

    /* Give a special dialog when you already asked for help */
    if(this_player()->query_prop(T_ASKED_HELP))
    {
        command("say I already told you. Go get the damned medallion and"
               + " bring it to me!\n");
	    set_alarm (1.0, 0.0, reset_blacksmith);
        return "";
    }
    
    command("emote grumbles.");
    set_alarm(1.0, 0.0, &command("say Well, I guess you might be" 
        + " able to help me. You'll probably die though."));          
    set_alarm(3.0, 0.0, &command("say Those morons in the cathedral think,"
        + " they are acting out Thanar's will."));
    set_alarm(5.5, 0.0, &command("emote scoffs and goes pffft."));
    set_alarm(11.0, 0.0, &command("say They wouldn't know Thanar's will if"
        + " it bit them in the arse. Some of those idiots are even carrying"
        + " around the pieces of the medallion used for summoning Him!"));
    set_alarm(13.0, 0.0, &command("emote shakes his head in disgust."));   
    set_alarm(16.0, 0.0, &command("say Get the four pieces of that medallion;"
        + " lower left, upper left, lower right, upper right, and put them"
        + " together. Bring it back to me. I've got the missing fifth piece"
        + " to make it whole. I'll even let you keep the medallion."));
    set_alarm(18.0, 0.0, &command("say All I ask, use it to summon Lord"
	    + " Thanar. Free him from his Avatar state by defeating him and"
        + " release his glory unto the world. That'll show those 'priests'."));
    set_alarm(22.0, 0.0, &command("say Return to me first when you have"
        + " the medallion and <ask blacksmith reward>. Then we will deal" 
        + " with the second part.\n"));
    
    /* Make sure we can speak to him again when he is done */
    set_alarm(23.0, 0.0,reset_blacksmith);
    
    /* Add a prop so the he knows that the player already asked
       him about help */
    this_player()->add_prop(T_ASKED_HELP, 1);
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
    if(SMITH_IS_BUSY == 1) {
        return "The blacksmith seems to be busy. You'd better wait a "
            + "few seconds before bothering him again.\n";
    }
    
    /* Set the SMITH_IS_BUSY is busy flag 1 */
    SMITH_IS_BUSY = 1;
    
    /* Ensure the object is recognized */

    object fullmed;

    if (TP->test_bit("Kalad", 1, 16) && TP->test_bit("Kalad", 1, 17))
    {
       set_alarm(3.0, 0.0, &command("emote frowns."));
       set_alarm(6.0, 0.0, &command("say You've helped me with this"
         + " task before. Or did you forget...moron."));
        //Reset the blacksmith so he can talk again
           set_alarm(10.0, 0.0,reset_blacksmith); 
           return "";
    }

    /* You have to have the full medallion. This means getting the
       four pieces and attaching them together. If you haven't done this
       You aren't done.*/
    
    if (!TP->test_bit("Kalad", 1, 16) &&
        !objectp(fullmed = present("_t_medallion_", this_player())))
    {
        quest_progress();
        return "";
    }
    
    /*Check if this player has the medallion and is supposed to summon 
    Thanar*/
    if(this_player()->query_prop(T_GO_SUMMON_THANAR))
    {
        command("say You haven't summoned Thanar yet! Get to it moron!\n");
	    set_alarm (1.0, 0.0, reset_blacksmith);
        return "";
    }
    
 
	/*Check if the player has summoned Thanar so they can get the right quest 
	  reward*/
    if(TP->query_prop(I_DID_THE_SUMMON) && TP->query_prop(T_I_SUMMON_THANAR))
    {
        set_alarm(1.0, 0.0, &command("emote shakes his head in wonder."));
        set_alarm(3.0, 0.0, &command("say You did it! I can feel it."));
        set_alarm(5.0, 0.0, &command("say You managed to summon Thanar!" 
            + " Even more, you defeated him and released him unto the" 
            + " world."));
        set_alarm(7.0, 0.0, &command("emote takes you in his arms."));
        set_alarm(9.0, 0.0, &command("emote releases you."));
        set_alarm(11.0, 0.0, &command("emote lowers his head in prayer, a"
            + " tear falling from his eyes."));
        set_alarm(13.0, 0.0, &command("say Thank you."));
        set_alarm(15.0, 0.0, &command("say If you ever have all the"
            + " pieces to make another medallion, just come and ask me"
            + " for the reward you've justly earned. <ask blacksmith medallion>"
            + "."));
    /* See if quest xp will be given or not */
        set_alarm(17.0, 0.0,reward_quest_summon);
        set_alarm(19.0, 0.0,reset_blacksmith);

        return "";
    }
    
    if(objectp(fullmed = present("_t_medallion_", this_player())) &&
    !TP->query_prop(I_KILLED_PRIESTS))
    {
        command("say You may have the medallion, but you didn't earn it."
            + " Come back when you've actually killed some of those "
            + " damned priests!\n");
        set_alarm (1.0, 0.0, reset_blacksmith);
        return "";
    }
    
      
    /* If we come this far it means that tihs part of the quest is done */
    set_alarm(1.0, 0.0, &command("emote smiles with great surprise."));
    set_alarm(3.0, 0.0, &command("say Wonderful! You didn't die!"));
    set_alarm(5.0, 0.0, &command("say And, you got all the pieces of the"
        + " medallion. Great job!"));
    set_alarm(7.0, 0.0, &command("emote takes the medallion from you and holds"
        + " it up to the light. He rummages through a drawer opening a small "
        + " hidden compartment. He pulls out a small notched piece that" 
        + " he fits into the medallion."));
    //Remove the incomplete medallion	  
    set_alarm(9.0, 0.0,  remove_fake_med);
    set_alarm(11.0, 0.0, &command("emote places the medallion in a vice and "
        + " grabs a vial from the furnace. He dumps the vial on the medallion "
        + " and hammers it gentle with a small tool."));
    set_alarm(13.0, 0.0, &command("emote takes a step back as the medallion"
        + " flares brightly."));
    set_alarm(15.0, 0.0, &command("say That's the only piece I've got to"
        + " make this damned thing whole. I won't be able to do it again"
        + " for you. So don't screw up. Now take this medallion with you as"
        + " you will need it when you go summon Thanar. Let's finish this.\n\n"
        + " Just be warned. This battle is mighty dangerous. Thanar does not"
        + " take lightly to those who challenge him. Be prepared for you may"
        + " be walking to certain death."));
    /* See if quest xp will be given or not */
    set_alarm(17.0, 0.0,reward_quest);
 
    set_alarm(18.0, 0.0, &command("emote smiles with glee."));
    this_player()->add_prop(T_GO_SUMMON_THANAR, 1);
    
    /* Make sure we can speak to him again when we are done */
    set_alarm(20.0, 0.0,reset_blacksmith);
    
    return "";

} /* task_reward*/

/*
 * Function name:        quest_progress
 * Description  :        reports the progress of the quest
 */
public void
quest_progress()
{   
    
    command("say What do you think I'm going to reward you for?"
        + " You're not done!");
    set_alarm(3.0, 0.0, &command("emote frowns."));
    set_alarm(6.0, 0.0, &command("say You need to get all the pieces of the"
        + " medallion and put them together. How hard is it to understand?"));
    set_alarm(7.0, 0.0, &command("say Go kill the priests, find the pieces"
        + " put them together, and come back to me."));
    set_alarm(8.0, 0.0, &command("emote waves his hand dismissivley."));

 
    /* Make sure we can speak to him again when we are done */
    set_alarm(10.0, 0.0,reset_blacksmith);    
    
    return;
    
} /* quest_progress */

/* 
 * Function name:       new_medallion
 * Description  :       Handles when someone wants to make the medallion
 *                      again.
 */
public string
new_medallion()
{
    
    object notchmed, fullmed, realmed;
    
    //Check they've done the quest already

    /* removed && !TP->query_prop(T_GO_SUMMON_THANAR).
    It blocks those who lost original medallion, if they ask help before asking for a new medallion.
    If you just solved, the !objectp(realmed = present("_thanar_medallion_", TP)) prevents the speech
    */

    /* Make sure he is not already talking to someone */  
    if(SMITH_IS_BUSY == 1) {
        return "The blacksmith seems to be busy. You'd better wait a "
            + "few seconds before bothering him again.\n";
    }
    
    /* Set the SMITH_IS_BUSY is busy flag 1 */
    SMITH_IS_BUSY = 1;

    // preventing players with the kill from getting other props.
    if (TP->query_prop(T_I_SUMMON_THANAR))
    {
        set_alarm(1.0, 0.0, &command("emote frowns."));
        set_alarm(3.0, 0.0, &command("say You already killed him. Ask "
            + "me <reward> instead.\n"));
                
        //Reset the blacksmith so he can talk again
        set_alarm(10.0, 0.0,reset_blacksmith); 
        return "";
    }
    
    if (TP->test_bit("Kalad", 1, 16) && !objectp(realmed = present("_thanar_medallion_", TP)))
    {
        set_alarm(3.0, 0.0, &command("say Looks like you've manged to help "
        + "with collecting the medallion, but haven't yet summoned Thanar. "
        + "Let's recap and get you going.\n"));
        set_alarm(5.0, 0.0, &command("say Hmm. It Seems you don't have the "
        + "medallion. Well, I can't give you another one like you've had. "
        + "I have one that might work. It's magic is weak, but it should "
        + "do the trick."));
        set_alarm(7.0, 0.0, &command("emote gives you a medallion.\n"));
        set_alarm(9.0, 0.0, &command("say Now, take the medallion with you as"
        + " you will need it when you go summon Thanar.\n\nGo to the Cathedral "
        + " and find the ritual chamber. Use this to summon him. Let's finish this."
        + " \n\nJust be warned. This battle is mighty dangerous. Thanar does not"
        + " take lightly to those who challenge him. Be prepared for you may"
        + " be walking to certain death."));
        this_player()->add_prop(T_GO_SUMMON_THANAR, 1);
        realmed = clone_object(ARM + "pnmedallion");
        realmed->move(this_player());
        set_alarm(10.0, 0.0,reset_blacksmith);
        return "";

    }

    if(this_player()->query_prop(T_GO_SUMMON_THANAR))
    {
        command("say You haven't summoned Thanar yet! Get to it moron!");
	    set_alarm (1.0, 0.0, reset_blacksmith);
        return "";
    }
    
    if (TP->test_bit("Kalad", 1, 16) && TP->tesT_bit("Kalad", 1, 17))
    {
        
        //Check if they have the full fake medallion first
        if (!objectp(fullmed = present("_t_medallion_", this_player())))
        {
            set_alarm(3.0, 0.0, &command("emote frowns."));
            set_alarm(6.0, 0.0, &command("say You've helped me with this "
                + "task before. Or did you forget...moron."));
            set_alarm(8.0, 0.0, &command("say You need the four pieces of"
                + "the medallion put together as well as the notched piece"
                + "from the Pontiff. I've explained this, or are you just"
                + " daft!"));

            //Reset the blacksmith so he can talk again
            set_alarm(10.0, 0.0,reset_blacksmith); 
            return "";
           
        }
            
        //Check they have the notched piece from the Pontiff
        if (!objectp(notchmed = present("_notch_medallion_", this_player())))
            
        {
            set_alarm(3.0, 0.0, &command("emote frowns."));
            set_alarm(6.0, 0.0, &command("say You've helped me with this"
                + "task before. Or did you forget...moron."));
            set_alarm(8.0, 0.0, &command("say I told you before. I only"
                + " had one of those notched pieces. You'll have to"
                + " find another  one if you expect me to make this"
                + " whole."));  
            set_alarm(10.0, 0.0, &command("say I've heard rumor it's carried"
                + " by the Pontiff of Thanar. He doesn't visit the"
                + " Cathedral often. When he does he is well guarded and"
                + " packs a mean punch himself. That dufus thinks he's the "
                + " only one worthy of carrying it."));
            set_alarm(12.0, 0.0, &command("say If you come across him and"
                + " manage to get the notched piece, I'll make you a new"
                + " medallion. Otherwise get your sorry arse out of here."));
            
            //Reset the blacksmith so he can talk again
           set_alarm(10.0, 0.0,reset_blacksmith); 
           return "";
        }
        
        //If they've got everything, make a new medallion.
        set_alarm(3.0, 0.0, &command("emote caclkes with glee."));
        set_alarm(6.0, 0.0, &command("say You've helped me with this"
            + "task before. But you just keep surprising me!"));
        set_alarm(8.0, 0.0, &command("say You managed to take out that"
            + " moron at the Cathedral. Ha. I would have loved to see"
            + " his face."));  
        set_alarm(10.0, 0.0, &command("say Well, give me that notched"
            + " piece of the medallion and let's make this thing whole"
            + " again."));
        set_alarm(12.0, 0.0, &command("emote He takes the small notched"
            + " piece of the medallion from you and slots it into the"
            + " medallion."));
        set_alarm(13.0, 0.0,  remove_notch_med);
        set_alarm(15.0, 0.0,  remove_fake_med);
        set_alarm(14.0, 0.0, &command("emote places the medallion in a vice and "
            + " grabs a vial from the furnace. He dumps the vial on the medallion "
            + " and hammers it gentle with a small tool."));
        set_alarm(16.0, 0.0, &command("emote takes a step back as the medallion"
            + " flares brightly."));
        realmed = clone_object(ARM + "pmedallion");
        realmed->move(this_player());
        set_alarm(18.0, 0.0, &command("say There you go. And good on ya."
            + " If you manage it again, I'll make you another one."));
        
        /* Make sure we can speak to him again when we are done */
        set_alarm(20.0, 0.0,reset_blacksmith); 
        return "";
          
    }
    
    //Otherwise tell them they need to do the quest.
    else
    {
      set_alarm(3.0, 0.0, &command("emote frowns."));
      set_alarm(6.0, 0.0, &command("say You haven't even helped me yet! "
        + "Maybe try <ask blacksmith help>."));
      
      /* Make sure we can speak to him again when we are done */
      set_alarm(8.0, 0.0,reset_blacksmith); 
      return "";
      
    }
}/*new_medallion*/

/*
 * Function name:        reset_smith
 * Description  :        resets the smith so he can speak again
 */
public void
reset_blacksmith()
{
    /* Make is to the smith can speak again. */
    SMITH_IS_BUSY = 0;
     
    return;
    
} /* reset_blacksmith */

/*
 * Function name:        remove_fake_med
 * Description  :        Removes the fake medallion
 */
public void
remove_fake_med()
{
    
    object *fakemed;

    fakemed = filter(all_inventory(this_player()), &->id("_t_medallion_"));

    //Remove the fake medallion
    fakemed->remove_object();
    
}/*remove_fake_med*/

/*
 * Function name:        remove_notch_med
 * Description  :        Removes the notch from the Pontiff
 */
public void
remove_notch_med()
{

    object *notchmed;

    notchmed = filter(all_inventory(this_player()), &->id("_notch_medallion_"));
	
    //Remove the notched piece from Pontiff
    notchmed->remove_object();
    
}/*remove_notch_med*/

/*
 * Function name:        reward_quest
 * Description  :        Rewards quest xp if its not already done
 */
 public void
 reward_quest()
 {  
 
     object realmed;
     
     
     /* See if the quest have been solved before */
     if (this_player()->test_bit("Kalad", 1, 16))
     {
         
         /* No further exp will be given */
         this_player()->catch_msg("You get a"
             + " feeling you have done this quest before.\n");   
     
     }
     
     else
     {
         /*Quest not done before give quest xp and set bit */
         this_player()-> add_exp_quest(10000);
         this_player()->set_bit(1, 16);
         this_player()->catch_msg("As the blacksmith hands you the completed"
            + " medallion, you feel more experienced!\n");
         realmed = clone_object(ARM + "pmedallion");
         realmed->move(this_player());
     
         /* Log who solves the quest */
         seteuid(getuid(TO));
         log_file(QUEST_NAME, extract(ctime(time()),4,15) + " "+
         capitalize(TP->query_real_name()) + " rewarded with 10000 xp,"+
         "<"+TP->query_average_stat()+"> average stats.\n");
     }
                 
 } /* reward_quest */
 
 /*
  * Function name:        reward_quest_summon
  * Description  :        Rewards quest xp for the second part, if not done
  */
 public void
 reward_quest_summon()
 {  
     /* See if the quest have been solved before */
 
     if (this_player()->test_bit("Kalad", 1, 17))
     {
         
         /* No further exp will be given */
         this_player()->catch_msg("You get a"
             + " feeling you have done this quest before.\n");    
     }
     
     else
     {
         /*Quest not done before give quest xp and set bit */
         this_player()-> add_exp_quest(25000);
         this_player()->set_bit(1, 17);
         this_player()->catch_msg("You feel more"
               + " experienced!\n");
     
         /* Log who solves the quest */
         seteuid(getuid(TO));
         log_file(QUEST_NAME, extract(ctime(time()),4,15) + " "+
         capitalize(TP->query_real_name()) + " rewarded with 25000 xp,"+
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
    TP->remove_prop(T_I_SUMMON_THANAR);    
    TP->remove_prop(T_ASKED_HELP);
    TP->remove_prop(I_DID_THE_SUMMON);
 
    return;
    
} /* remove_props */