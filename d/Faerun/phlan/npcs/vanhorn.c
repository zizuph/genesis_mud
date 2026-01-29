/*
 *    Quest person. She will have the basic tour quests. She will
 *    send players to the bank, adventurers guild, post, inn and
 *    then refer them to the bishop. Non-assigned quest, when the players
 *    find the stolen goods in the well at Kuto's Well, she will be 
 *    the one they report it to.
 *    Tharizdun, 2021
 */

#pragma strict_types

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h> 
#include <wa_types.h>
#include <filter_funs.h>
#include <defs.h>

inherit "std/monster.c";
inherit "/d/Genesis/lib/intro";

/*
*   Global variables
*/

#define WEAPON WEP_DIR + "ringed_scimitar"
#define HAUBERK ARM_DIR + "owlbear_hauberk"
#define BRACERS ARM_DIR + "chainmail_gloves"
#define BOOTS ARM_DIR + "phlan_lizardhide_boots"

void arm_me();

void create_monster()
{
    string type, phys;
    int i;

    seteuid(getuid());
    
    set_living_name("daari");
    set_name("daari"); 
    add_name("van Horn");    
    set_title("commander of the city guard");    
    set_race_name("human");
    set_adj( ({"fierce", "raven-haired"}) );         
    set_gender(G_FEMALE);    
    
    set_short("fierce raven-haired female human"); 
    set_long("Dark tanned with almond-shaped eyes, it is obvious that Daari"
        +" Van Horn is not native to the Moonsea area. Her lithe movement"
        +" and fierce demeanor leave no doubt that she is an enemy to be"
        +" respected. Her calm, measured and reassuring voice also leave"
        +" no doubt she is a staunch ally. She is the commander of the city"
        +" guard and makes a point of helping those new to her city.\n");    

/*
*   size and skills
*/

    set_stats(((150, 180, 130, 130, 200, 150)));

    set_alignment(500);

    set_skill(SS_WEP_SWORD,100);
    set_skill(SS_DEFENCE,80);
    set_skill(SS_PARRY,80);
    set_skill(SS_AWARENESS,100); 
    set_skill(SS_BLIND_COMBAT,100);  
    set_skill(SS_ACROBAT,80);    
    
    add_prop(CONT_I_WEIGHT, 68040);
    add_prop(CONT_I_HEIGHT, 175);      

/* 
*   Actions 
*/

    set_act_time(10);
    set_cact_time(5);
    add_chat("Have you taken the opportunity to tour Phlan?");
    add_chat("We offer every service a young adventurer should need.");
    add_act("emote inspects her sword.");
    add_act("emote gets a far away look in her eyes for just a moment"
        +" and then her focus quickly returns.");

    add_ask( ({ "service", "services" }),
    "say Phlan has all the basic services of a much larger town. Taking a"
        +" tour should give you a better idea of where to find the help"
        +" you need.", 1);
        
/*
*   setting up quests
*/
        
    add_ask( ({ "tour", "tours", "help", "task", "quest", "job" }),
    
/*
*   Checking to see if they are currently working on a quest.
*/

    if(this_player()->query_prop("_phlan_tour1_start"))
    {
        "say You still have not found the bank.", 1;
    }
    if(this_player()->query_prop("_phlan_tour2_start"))
    {
        "say You still need to find the post office.", 1;
    }
    if(this_player()->query_prop("_phlan_tour3_start"))
    {
        "say First you must find the adventurer's guild.", 1;
    } 
    if(this_player()->query_prop("_phlan_tour4_start"))
    {
        "say You have not yet found the Cracked Crown Inn?", 1;
    } 

/*
*   Checking to see if they have completed a tour but not claimed 
*   their reward.
*/
 
    if(this_player()->query_prop("_phlan_tour*_prop"))
    {
        "say It looks like you have completed your tour. You are ready"
        +" to ask me for your reward.", 1;
    }  
    
/*
*   Checking to see which tour they will be assigned.
*/

    if(this_player()->query_prop("_phlan_tour4_complete"))
    {
        "say You seem to have all the basics down. Perhaps you could"
        +" speak with Bishop Tulloch in the Temple of Tyr if you"
        +" are looking for more work.", 1;
    }   
    if(this_player()->query_prop("_phlan_tour3_complete"))
    {
        "say The after a hard day's adventuring a good meal and place to sleep"
        +" can be a lifesaver. We offer both of those at the Cracked"
        +" Crown Inn. Visit the inn and then come back here and ask"
        +" for your reward."
        this_player()->add_prop("_phlan_tour4_start", 1);         
    }     
    if(this_player()->query_prop("_phlan_tour2_complete"))
    {
        "say The key to success for an adventurer is gaining and increasing"
        +" one's skills. The Phlan adventurer's guild provides a solid"
        +" base for you to build from. Visit the adventurer's guild"
        +" and then come back here and ask for your reward."
        this_player()->add_prop("_phlan_tour3_start", 1);         
    }
    if(this_player()->query_prop("_phlan_tour1_complete"))
    {
        "say Many times an adventurer will need to contact their peers or"
        +" respond to missives from other lands. To facilitate that"
        +" need, go no farther than the Phlan post office. Visit the"
        +" post office and then come back here and ask for your reward."
        this_player()->add_prop("_phlan_tour2_start", 1);         
    }
    {
        "say Phlan is a safe town. We have almost no crime and a big part of"
        +" that is citizens being careful. We have an excllent bank"
        +" to store your extra money or gems to avoid looking like"
        +" a target for pickpockets. Visit the bank and then come"
        +" back here and ask for your reward."
        this_player()->add_prop("_phlan_tour1_start", 1);  
    }   
1);

/*
*   Setting up rewards
*/
        
    add_ask( ({ "reward" }),

/*
*   Checking which reward is due
*/

{
    if(this_player()->query_prop("_phlan_tour1_prop"))    
    {
        this_player()->remove_prop("_phlan_tour1_prop");
        this_player()->catch_msg("Excellent, you have found the bank.\n"); 
        // add experience to be determined
        this_player()->add_prop("_phlan_tour1_complete", 1);        
        return 0;
    }
    if(this_player()->query_prop("_phlan_tour2_prop"))    
    {
        this_player()->remove_prop("_phlan_tour2_prop");
        this_player()->catch_msg("Wonderful, you have found the post office.\n"); 
        // add experience to be determined
        this_player()->add_prop("_phlan_tour2_complete", 1);        
        return 0;
    }
    if(this_player()->query_prop("_phlan_tour3_prop"))    
    {
        this_player()->remove_prop("_phlan_tour3_prop");
        this_player()->catch_msg("The adventurer's guild is quite popular.\n"); 
        // add experience to be determined
        this_player()->add_prop("_phlan_tour3_complete", 1);        
        return 0;
    }
    if(this_player()->query_prop("_phlan_tour4_prop"))    
    {
        this_player()->remove_prop("_phlan_tour4_prop");
        this_player()->catch_msg("I hope the inn met your needs.\n"); 
        // add experience to be determined
        this_player()->add_prop("_phlan_tour4_complete", 1);        
        return 0;
    }
), 1);    

    arm_me();
}


void

/*
*   adding gear
*/

arm_me()
{
    seteuid(getuid(this_object()));
    equip(({
        WEAPON,
        HAUBERK,
        BRACERS,
        BOOTS,
    }));
}

/*
 * This is called if the person has already been introduced before.
 */

void
greet(object who)
{
    command("bow respectfully " + OB_NAME(who));
}

/*
 * This is called if the person has not been introduced before.
 */

void
introduce(object who)
{
    command("introduce me to " + this_player()->query_real_name() + "");
}

/*
*   React to introduction. String name is person being introduced.
*/

void
react_to_introduction(string name)
{
    object who = find_player(name);
    if (!who || !present(who, environment(this_object())))
    {
        return;
    }
    if (this_object()->query_prop(LIVE_I_NEVERKNOWN) ||
        who->query_met(this_object()))
        {
            greet(who);
        }
        else
        {
            introduce(who);
        }
}

/*
*   react_intro 
*   Function name: add_introduced
*   Description  : Called automatically from the mudlib whenever a person
*                introduces himself to this NPC.
*   Arguments    : string name - the name of the person being introduced.
*
*/

public void
add_introduced(string name)
{
    if (intro_delay)
    {
        set_alarm(itof(intro_delay), 0.0, &react_to_introduction(name));
    }
    else
    {
        react_to_introduction(name);
    }
}
