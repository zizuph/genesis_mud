/*
 * /w/Sparkle/area/city/bank/npc/hapertacosh.c
 *
 * Hapertacosh is the gnomish mechanic of Gnomes of Genesis: Main Branch.
 * 
 * Created March 2009, by Aeg (Matthew Morin)
 */
 
#pragma strict_types

/* Inheritance */
inherit "/d/Sparkle/area/city/npc/sparkle_npc";
inherit "/d/Genesis/lib/intro"; /* Get him to intro */ 

/* Includes */
#include <macros.h>         /* General purpose  */
#include <stdproperties.h>  /* References       */
#include <ss_types.h>       /* Skills           */
#include <wa_types.h>       /* Attack+Hitloc    */
#include <cmdparse.h>       /* actions          */
#include <money.h>          /* money            */
#include "/d/Sparkle/sys/quests.h"
#include "../defs.h" 

/* prototypes */
public void     create_sparkle_npc();
public void     arm_me();
public void     return_object(object obj, object to);
public void     react_hammer(object obj, object to);

/* 
 * Function name:           create_sparkle_npc
 * Description  :           Creates NPC with Sparkle settings
 */
public void
create_sparkle_npc()
{
    set_name("hapertacosh");
    add_name( ({"hapertacosh", "mechanic", "worker"}) );
    set_race_name("gnome");
    set_adj( ({"gray-bearded", "greasy"}) );
    set_title("the ChiefMechanicOfArmedVehiclesOfTheMainBranchOfTheGnomes"
        + "OfGenesisBank");
    set_gender(G_MALE);
    set_long("This greasy gnome appears to be the gnome in charge of the "
        + "armoured cart of the bank. He is a mechanic, one who tinkers in "
        + "bowels of the machine. He is covered in grease and dirt and "
        + "appears very busy.\n");

    /* Stats!    STR, CON, DEX, INT, WIS, DIS */
    set_stats(({ 50,  50,  60,  60,  60,  30 }));
    set_hp(20000); /* Heal it */
    
    /* skills */
    set_skill(SS_DEFENCE,      20);
    set_skill(SS_UNARM_COMBAT, 20);
    
    /* Chatter */
    set_chat_time(30); /* chatter every 5 'beats' */
    add_chat("OutOfMyWay!IHaveMoreThingsToDoThanYouCanCount!");
    add_chat("OoooohWhatIWouldDoForAnAssistant!");
    add_chat("ThatLastExplosionWasNothingOutOfTheOrdinary...");
    add_chat("...AddMoreBellsTheySay...I'llAddSeven!");
    add_chat("ThisArmouredCartIsTheBestInventionEver!HowCouldITopIt?");
    add_chat("WhereIsThatHammer?");
    add_chat("DamnOwlrats!TheyAreAlwaysPeckingAndWhoing!IBetTheyStoleMy"
        + "Wrench!");
    add_chat("ISetTrapsForThoseDamnOwlratVermin!ICan'tWaitToCatchOne!");
    add_chat("WhereIsThatDamnedAssistantOfMine?SomeoneFetchThatWorthless"
        + "Goblin!");
    
    /* Actions */
    set_act_time(45); /* action every 5 'beats' */
    add_act("emote grumbles and snorts about some missing tools.");
    add_act("emote clenches his fists in frustration.");
    add_act("emote beams with joy as he hears a loud snap and a faint: "
          + "'Whoo-Ho.oo..o...'");
    add_act("emote peers uneasily at the drain.");
    add_act("emote peers uneasily at the northwest corner of the room.");
    add_act("emote runs around the garage in a frantic and seemingly senselss "
          + "fashion.");
    add_act("emote drops something down the drain and swears loudly.");
    add_act("emote drops some bait into an owlrat trap.");
    add_act("emote tinkers away at something on his workbench.");
    add_act("emote fixes a gizmo.");
    add_act("emote enters a fiery rage as he breaks a gizmo or... whatever "
          + "that was.");
    add_act("emote mumbles something about idiotic humans.");
    add_act("emote rummages through his toolbox, obviously looking for "
          + "something.");
    add_act("emote rummages through some scrap metal on the floor.");
    add_act("emote adjusts his blast goggles.");
    add_act("emote wipes some grease on his blast apron.");
    add_act("emote pushes past you and mumbles: OutOfMyWay!");
    add_act("emote looks frustrated.");
    
    
    /* Combat Actions */
    set_cact_time(10); /* combat action every 2 'beats' */
    add_cact("shout Ohhh!YouOwlratBastard!I'llShowYouAThingOrTwo!");
    add_cact("shout KillingMeWillOnlyHurtYourKind.YourKindLoses100YearsOf"
        + "TechnologyWithEveryGnomeYouKill!");
    add_cact("shout Fool!YouWillNeverGetAwayWithThis!");
    
    /* Asking details */
    set_default_answer(VBFC_ME("default_answer"));
    
    /* No naked gnomes allowed */
    arm_me();
    
        
    /* Prop */
    add_prop(LIVE_M_NO_ACCEPT_GIVE, 0);
    
    
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
    clone_object(BANK_OBJ + "blast_goggles")->move(this_object());
    command("wear all");
    command("wield all");
    MONEY_MAKE_CC(15 + random(15))->move(this_object());
    MONEY_MAKE_SC(15 + random(10))->move(this_object());  
} /* Arm me */

/* 
 * Function name:        return_object
 * Description  :        have npcs give things they are given back
 *                       to players
 * Arguments    :        object obj - the object given
 *                       object to  - the player who gave it
 */
public void
return_object(object obj, object to)
{
    if (obj->id("hammer"))
    {
        if(!obj->id("_sparkle_bank_hammer"))
        {
            command("say Idiot!IWant*My*Hammer!ThisTrashWon'tDo.");
            return 0;
        }
        
        set_alarm(0.5, 0.0, &react_hammer(obj, to));
        return;
    }

    command("say UuhThanks?");
    command("give " + OB_NAME(obj) + " to " + OB_NAME(to));
    if (environment(obj) == this_object())
    {
       command("drop " + OB_NAME(obj));
    }
} /* return_object */


/*
 * Function name:        react_hammer
 * Description  :        have the npc respond to a specific object
 */
public void
react_hammer(object obj, object to)
{

    if (this_player()->test_bit("Sparkle", BANK_HAMMER_DELIVER_GROUP, 
                 BANK_HAMMER_DELIVER_BIT))
    {
        command("say Ah!Fantastic!ThankYou*Again*ForTheHelp!");
        obj->remove_object();
        return;
        
    }

    command("emote adjusts his blast goggles.");
    command("emote beams with pure joy!");
    command("say Ah!Fantastic!ThankYouForTheHelp!");
    command("say YouMightNotBeWorthlessAfterAll.");
    command("say NowGetOutOfMyWay.IHaveWork.");
    command("emote returns to work and ignores you.");

    this_player()->set_bit(BANK_HAMMER_DELIVER_GROUP, BANK_HAMMER_DELIVER_BIT);
    this_player()->add_exp_quest(BANK_HAMMER_DELIVER_EXP);
    this_player()->catch_tell("You feel a bit more experienced!\n");
    return;

} /* react_hammer */

