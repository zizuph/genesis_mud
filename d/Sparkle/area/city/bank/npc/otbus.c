/*
 * /w/Sparkle/area/city/bank/npc/otbus.c
 *
 * Otbus the Hobbit employee of Gnomes of Genesis: Main Branch.
 * 
 * Created March 2008, by Aeg (Matthew Morin)
 */
 
#pragma strict_types

/* Inheritance */
inherit "/d/Sparkle/area/city/npc/sparkle_npc";
inherit "/d/Genesis/lib/intro"; /* Get him to intro */ 

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
public void     building_answer();
public void     bank_answer();
public void     service_answer();
public void     pay_answer();
public void     corp_answer();
public void     benefit_answer();
public void     cost_answer();
public void     world_answer();
public void     lollipop_answer();
public void     family_answer();
public void     orvin_answer();
public void     school_answer();
public void     give_lollipop(object who);
public void     manual_answer();


/* 
 * Function name:           create_sparkle_npc
 * Description  :           Creates NPC with Sparkle settings
 */
public void
create_sparkle_npc()
{
    set_name("otbus");
    add_name( ({"otbus", "greeter", "worker"}) );
    set_race_name("hobbit");
    set_adj( ({"overworked", "portly"}) );
    set_title("the Greeter of the Bank");
    set_gender(G_MALE);
    set_long("This poor hobbit looks overworked and very tired. His "
        + "slow movements must mean he has been working a double, or "
        + "triple shift. His purpose is to greet people, guide them to "
        + "their appropriate spot and hand out lollipops.\n");

    /* Stats!    STR, CON, DEX, INT, WIS, DIS */
    set_stats(({ 50,  50,  60,  60,  60,  30 }));
    set_hp(20000); /* Heal it */
    
    /* skills */
    set_skill(SS_DEFENCE,      20);
    set_skill(SS_UNARM_COMBAT, 20);
    
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
    
    /* No naked hobbits allowed */
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
    add_ask( ({ "service", "amenities", "actions" }),
        VBFC_ME("service_answer") );
    add_ask( ({ "pay", "wage", "wages", "earnings" }),
        VBFC_ME("pay_answer") );
    add_ask( ({ "corporation", "corporations", "commercial corporation" }),
        VBFC_ME("corp_answer") );
    add_ask( ({ "benefits", "perks", "benefit" }),
        VBFC_ME("benefit_answer") );
    add_ask( ({"cost", "costs", "sacrifices" }),
        VBFC_ME("cost_answer") );
    add_ask( ({"world", "perfect", "perfect world" }),
        VBFC_ME("world_answer") );
    add_ask( ({"lollipop", "lolli", "candy", "food", "feed me" }),
        VBFC_ME("lollipop_answer") );
    add_ask( ({"family", "home", "free time" }),
        VBFC_ME("family_answer") );
    add_ask( ({"orvin", "Orvin", "son", "kid", "child", "offspring" }),
        VBFC_ME("orvin_answer") );
    add_ask( ({"school"}),
        VBFC_ME("school_answer") );
    add_ask( ({"manual", "employee manual"}),
        VBFC_ME("manual_answer") );
    add_ask( ({"busy", "tiring", "tired", "pooped", "overworked"}),
        VBFC_ME("busy_answer") );
    add_ask( ({"deposit", "withdraw", "minimize", "minimize coins",
               "change", "change coins", "deposit coins",
               "withdraw coins"}),
        VBFC_ME("commands_answer") );
    add_ask( ({"OrderAndProgress", "orderandprogress", "order",
               "progress", "order and progress"}),
        VBFC_ME("order_answer") );
 
} /* add_bank_asks */


/* 
 * Function name:       default_answer
 * Description  :       give the default response to questions
 */
public string
default_answer()
{
    command("sneeze");
    command("excuse me");
    command("say I'm sorry. What was that?");
    return "";
} /* default_answer */


/*
 * Function name:       swear_word_answer
 * Description  :       response for cursing at NPCs
 */
public string
swear_word_answer()
{
    command("mumble What does my employee manual say about situations "
        + "like this?");
    command("emote flips though a small manual.");
    command("smile ambi");
    
    return "";
} /* swear_word_answer */


/*
 * Function name:       job_answer
 * Description  :       response to player asking 'job'
 */
public string
job_answer()
{
    command("say My job? It's a good, steady job. Sure is tiring "
            + "though. The gnomes keep me busy at all hours, but the "
            + "pay is good!");
    
    return "";
} /* job_answer */


/* 
 * Function name:       gnome_answer
 * Description  :       give response to asking about gnomes
 */
public string
gnome_answer()
{
    
    command("say Gnomes? Yeah, they own the place. 'Commercial corporation' "
        + "amongst the bunch of 'em, they say. I donno what it is, or how "
        + "it works, but I know it does.");    
    command("smile brie");
    
    return "";
} /* gnome_answer */


/* 
 * Function name:       building_answer
 * Description  :       give response to asking about building
 */
public string
building_answer()
{
    command("smile joy");
    command("say Beautiful building, isn't it? I just love the architecture "
        + "of this place.");
    command("emote looks toward the high ceiling and says: The gnomes "
        + "wanted this to be the most grand and ornate bank in all the "
        + "world. Artisans from across the donut were hired for their "
        + "assistance in it's construction. It was very expensive.");
        
    return "";
} /* building_answer */


/* 
 * Function name:       bank_answer
 * Description  :       give response to asking about bank
 */
public string
bank_answer()
{
    command("say A bank is a place where you can safely store your coins, "
        + "to avoid having to carry them around. The main branch is a "
        + "full service bank, which allows you all the amenities you may "
        + "need for your banking experience.");
    command("smile profes");
    command("say Ask me for a lollipop, if you want one!");
    
    return "";
} /* bank_answer */


/* 
 * Function name:       service_answer
 * Description  :       give response to asking about service
 */
public string
service_answer()
{
    command("emote gestures to the large plaque.");
    command("say You may <deposit>, <withdraw>, check your <account>, "
        + "<minimize> your coins, or <change> your coins.");
    
    return "";
} /* service_answer */


/* 
 * Function name:       pay_answer
 * Description  :       give response to asking about pay
 */
public string
pay_answer()
{
    command("smile simpl");
    command("say The gnomes pay competitive rates, but they expect a lot "
        + "out of you. The gnomes take their jobs very seriously. We have "
        + "employment opportunities, if you are in need of work.");
    
    return "";
} /* pay_answer */


/* 
 * Function name:       corp_answer
 * Description  :       give response to asking about corporations
 */
public string
corp_answer()
{
    command("say Corporations?");
    command("gesture unknow");
    command("say They say that it gives each gnome the benefit of "
        + "ownership without the risk of ownership. Gnomes sure are "
        + "complicated.");
        
    return "";
} /* corp_answer */


/* 
 * Function name:       benefit_answer
 * Description  :       give response to asking about benefits
 */
public string
benefit_answer()
{
    command("nod thoughtfully");
    command("say The gnomes talk a lot about making a perfect world and "
        + "the cost for doing so.");
        
    return "";
} /* benefit_answer */

/* 
 * Function name:       cost_answer
 * Description  :       give response to asking about costs
 */
public string
cost_answer()
{
    command("hmm");
    command("say They never really go into the costs of making a perfect "
        + "world... I assume they mean monetary cost.");
        
    return "";
} /* cost_answer */

/* 
 * Function name:       world_answer
 * Description  :       give response to asking about world
 */
public string
world_answer()
{
    command("say Eh? Something about 'OrderAndProgress.'");
    
    return "";
}


/* 
 * Function name:       lollipop_answer
 * Description  :       give response to asking about lollipops
 */
public string
lollipop_answer()
{
    command("smile");
    command("say Here! Enjoy this gift from the Gnomes of Genesis!");
    give_lollipop(this_player());
    
    return "";
} /* lollipop_answer */


/* 
 * Function name:       family_answer
 * Description  :       give response to asking about family
 */
public string
family_answer()
{
    command("grin tired");
    command("say I work long hours to send my son, Orvin, to school "
        + "in town.");
    
    return "";
} /* family_answer */


/* 
 * Function name:       orvin_answer
 * Description  :       give response to asking about Orvin (npc)
 */
public string
orvin_answer()
{
    command("smile concernedly");
    command("say I want the best for him, but school in town is too "
        + "expensive. I just want to give him a good education and keep "
        + "him off the streets.");
    
    return "";
} /* orvin_answer */


/* 
 * Function name:       school_answer
 * Description  :       give response to asking about school
 */
public string
school_answer()
{
    command("say I wish to enroll Orvin, my son, in the local school, but "
        + "it is too expensive.");
    
    return "";
} /* school_answer*/


/*
 * Function name:        give_lollipop
 * Description  :        have the hobbit give the player a lollipop
 * Arguments    :        object who - the player
 */
public void
give_lollipop(object who)
{
    object  lollipop;

    command("emote wiggles his fingers as if he is performing a magic "
        + "trick.\n"
        + "He pulls a lollipop out of nothingness!\n");
    lollipop = clone_object(BANK_OBJ + "lollipop");
    lollipop->move(this_object());
    command("give " + OB_NAME(lollipop) + " to "
      + who->query_real_name());
      
} /* give_lollipop */


/*
 * Function name:        manual_answer
 * Description  :        give a response to being asked about his manual.
 */
public string
manual_answer()
{
    command("emote points to a mundane gray book that he carries.");
    command("say It explains how I should react to any situation... The "
        + "gnomes are very detailed and particular about these things.");
        
    return "";
} /* manual_answer() */


/*
 * Function name:        busy_answer
 * Description  :        give a response to being asked about being busy.
 */
public string
busy_answer()
{
    command("smile tired");
    command("say Yeah, I'm pooped.");

    return "";
} /* busy_answer */


/*
 * Function name:        commands_answer
 * Description  :        give a response to being asked about banking
 *                       commands.
 */
public string
commands_answer()
{
    command("emote points to the large plaque.");
    command("smile helpful");

    return "";
} /* command_answer */

/*
 * Function name:        sparkle_answer
 * Description  :        give a response to being asked about Sparkle
 */
public string
sparkle_answer()
{
    command("say This has always been my home. I love this city!");
    command("smile lovi");
    
    return "";
} /* sparkle_answer */


/*
 * Function name:        order_answer
 * Description  :        give a response to OrderAndProgress
 */
public string
order_answer()
{
    command("shrug");
    
    return"";
} /* order_answer */


/*
 * Function name:        help_answer
 * Description  :        give a response to asking help
 */
public string
help_answer()
{
    command("say There are job opportunites here in the bank! Ask around "
        + "for them!");
        
    return "";
} /* help_answer */