/*
 * /w/Sparkle/area/city/bank/npc/guard.c
 *
 * Standard guard for the bank
 * 
 * Created October 2010, by Aeg (Matthew Morin)
 */
 
#pragma strict_types

/* Inheritance */
inherit "/d/Sparkle/area/city/npc/sparkle_npc";

/* Includes */
#include "../defs.h" 
#include <macros.h>         /* General purpose  */
#include <stdproperties.h>  /* References       */
#include <ss_types.h>       /* Skills           */
#include <wa_types.h>       /* Attack+Hitloc    */
#include <cmdparse.h>       /* actions          */
#include <money.h>          /* money            */

/* prototypes */
public void     create_sparkle_npc();
public void     arm_me();
public void     add_bank_asks();
public void     gnome_answer();
public void     bank_answer();
public void     pay_answer();
public void     world_answer();
public void     family_answer();
public void     manual_answer();


/* 
 * Function name:           create_sparkle_npc
 * Description  :           Creates NPC with Sparkle settings
 */
public void
create_sparkle_npc()
{
    set_name("guard");
    set_race_name("gnome");
    set_adj( ({"caffinated", "vigilant"}) );
    set_gender(G_MALE);
    set_long("This guard protects the interests of the Gnomes of "
		+ "Genesis. He is armed with cutting edge technology and not "
		+ "afraid to use it.\n");
	add_prop(OBJ_M_NO_ATTACK, "Just as you are about to attack the "
		+ "gnome, a horribly loud alarm sounds, bells and whistles "
		+ "begin to shriek, and a large mechanical arm extends from "
		+ "a nearby wall and slaps you silly!\n");


    /* Stats!    STR, CON, DEX, INT, WIS, DIS */
    set_stats(({ 200,  150,  200,  200,  100, 200 }));
    set_hp(20000); /* Heal it */
    
    /* skills */
    set_skill(SS_DEFENCE,      70);
    set_skill(SS_UNARM_COMBAT, 70);
    
    /* Chatter */
    set_chat_time(30); /* chatter every 5 'beats' */
    add_chat("Welcome! Welcome! The Main Branch of the Gnomes of "
        + "Genesis welcomes you!");
    add_chat("Merchants to line one!");
    add_chat("Adventurers to line two!");
    add_chat("Locals, please use line three!");
    add_chat("Thank you for banking with us!");
    add_chat("Oh, Hi! Welcome to the bank!");
    add_chat("Beautiful building, isn't it?");
    
    /* Actions */
    set_act_time(45); /* action every 5 'beats' */
    add_act("emote greets and welcomes some patrons as they enter the "
        + "door.");
    add_act("emote guides a man to line two.");
    add_act("emote smiles and says: Ask me for a lollipop! Complements "
        + "of the Gnomes of Genesis!");
    add_act("emote guides some women to line three.");
    add_act("emote polishes the large plaque with a rag.");
    add_act("emote rests briefly, he must think nobody is watching.");
    add_act("emote quickly counts the lollipops that he has in his pocket.");
    add_act("emote waves to a small child as she leaves with her mother.");
    
    /* Combat Actions */
    set_cact_time(10); /* combat action every 2 'beats' */
    add_cact("shout Help! Somebody call the guards!");
    add_cact("shout I don't carry coins! All I have are lollipops!");
    
    /* asking details */
    set_default_answer(VBFC_ME("default_answer"));
    add_bank_asks();
    
    /* No naked guards allowed */
    arm_me();
    
        
} /* create_sparkle_npc */

/*
 * Function name:       arm_me
 * Description  :       gives npc items and wields/wears them
 * Arguments    :       None
 * Returns      :       None
 */
public void 
arm_me() 
{
    seteuid(getuid()); 
    clone_object(BANK_OBJ + "bank_hat")->move(this_object());
    clone_object(BANK_OBJ + "bank_vest")->move(this_object());
    clone_object(BANK_OBJ + "bank_manual")->move(this_object());
    clone_object(BANK_OBJ + "bank_pants")->move(this_object());
    command("wear all");
    command("wield all");
    MONEY_MAKE_CC(15 + random(15))->move(this_object());
    MONEY_MAKE_SC(15 + random(10))->move(this_object());  
} /* Arm me */

/*
 * Function name:       add_bank_asks
 * Description  :       gives bank workers a set of answers to questions.
 * Arguments    :       None
 * Returns      :       None
 */
public void
add_bank_asks()
{
    add_ask( ({ "gnomes", "gnome" }),
        VBFC_ME("gnome_answer") );
    add_ask( ({ "building", "architecture" }),
        VBFC_ME("building_answer") );
    add_ask( ({ "bank", "banks" }),
        VBFC_ME("bank_answer") );
    add_ask( ({ "pay", "wage", "wages", "earnings" }),
        VBFC_ME("pay_answer") );
    add_ask( ({"world", "perfect", "perfect world" }),
        VBFC_ME("world_answer") );
    add_ask( ({"family", "home", "free time" }),
        VBFC_ME("family_answer") );
    add_ask( ({"manual", "employee manual"}),
        VBFC_ME("manual_answer") );
 
} /* add_bank_asks */


/* 
 * Function name:       default_answer
 * Description  :       give the default response to questions
 */
public string
default_answer()
{
    command("sneer");
    command("say Bah!StopWastingMyTime!");
	
    return "";
} /* default_answer */


/*
 * Function name:       swear_word_answer
 * Description  :       response for cursing at NPCs
 */
public string
swear_word_answer()
{
    command("emote mumbles to a nearby gnome: SomeoneTellThisApeThatIWill"
		  + "NotBelittleMyselfByResponding?");
    command("emote stares at you silently.");
    
    return "";
} /* swear_word_answer */


/*
 * Function name:       job_answer
 * Description  :       response to player asking 'job'
 */
public string
job_answer()
{
    command("say MyJob?ToKeepYouInLine.BuggerOff!");
    
    return "";
} /* job_answer */


/* 
 * Function name:       gnome_answer
 * Description  :       give response to asking about gnomes
 */
public string
gnome_answer()
{
    
    command("say Clearly,TheMostEvolvedOfTheRaces.");    
    command("smile gnomishly");
    
    return "";
} /* gnome_answer */


/* 
 * Function name:       building_answer
 * Description  :       give response to asking about building
 */
public string
building_answer()
{
    command("emote narrows his eyes suspiciously.");
    command("say Safe,VerySafe.");       
    
	return "";
} /* building_answer */


/* 
 * Function name:       bank_answer
 * Description  :       give response to asking about bank
 */
public string
bank_answer()
{
    command("say AskTheGreeter.I'mBusy.");
    command("smile profes");
    
    return "";
} /* bank_answer */


/* 
 * Function name:       pay_answer
 * Description  :       give response to asking about pay
 */
public string
pay_answer()
{
    command("smile cautiou");
    command("say TheBankPaysBetterThanYouCan.BuggerOff!");
    
    return "";
} /* pay_answer */


/* 
 * Function name:       world_answer
 * Description  :       give response to asking about world
 */
public string
world_answer()
{
    command("say Mmmm.Donuts.'");
    
    return "";
}

/* 
 * Function name:       family_answer
 * Description  :       give response to asking about family
 */
public string
family_answer()
{
    command("sneer");
    command("say MindYourBusiness.BuggerOff!");
    
    return "";
} /* family_answer */


/*
 * Function name:        manual_answer
 * Description  :        give a response to being asked about his manual.
 */
public string
manual_answer()
{
    command("emote points to a mundane gray book that he carries.");
    command("say ItSaysThatIDoNotTalkToAsylumResidents...");
	command("emote stares at you silently.");
        
    return "";
} /* manual_answer() */

/*
 * Function name:        busy_answer
 * Description  :        give a response to being asked about being busy.
 */
public string
busy_answer()
{
    command("grin tired");

    return "";
} /* busy_answer */

/*
 * Function name:        sparkle_answer
 * Description  :        give a response to being asked about Sparkle
 */
public string
sparkle_answer()
{
    command("say HeadquartersOfTheBank.AllICare.BuggerOff!");
    command("sneer");
    
    return "";
} /* sparkle_answer */


/*
 * Function name:        help_answer
 * Description  :        give a response to asking help
 */
public string
help_answer()
{
    command("say Beh!IDonno.BuggerOff!");
        
    return "";
} /* help_answer */