/*
 *    Quest person. He will have two obvious quests to start with, both
 *    of which are mentioned in his chats. One is simple, go to the city hall
 *    and get a book from his office and return it. The second will involve 
 *    going to the Valhingen graveyard and slaying a vampire. This will have 
 *    several steps including going to the library for research, going to
 *    the confessional to be able to receive Tyr's blessing, then finding the
 *    crypt with the vampire's coffin, killing him, then dealing with the remains.
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

#define WEAPON WEP_DIR + "tyr_hammer"
#define BREASTPLATE ARM_DIR + "phlan_platemail"
#define SHIELD ARM_DIR + "phlan_heavy_steel_shield"
#define HELM ARM_DIR + "phlan_plate_helm"
#define BRACERS ARM_DIR + "phlan_bracers"
#define GREAVES ARM_DIR + "phlan_leggings"
#define BOOTS ARM_DIR + "phlan_light_boots"

void arm_me();

void create_monster()
{
    string type, phys;
    int i;

    seteuid(getuid());
    
    set_living_name("tulloch");
    set_name("tulloch"); 
    add_name("bishop");    
    set_title(" priest of Tyr");    
    set_race_name("human");
    set_adj( ({"active", "grey-haired"}) );         
    set_gender(G_MALE);    
    
    set_short("active grey-haired male human"); 
    set_long("An aging but active man, he seems to flow with the"
        +" strength that comes from holy service. His grey hair adds"
        +" a distinguished air to his friendly appearance. He is the"
        +" head of the temple of Tyr in Phlan.\n");       

/*
*   size and skills
*/

    set_stats(((150, 130, 150, 160, 200, 150)));

    set_alignment(500);

    set_skill(SS_WEP_CLUB,100);
    set_skill(SS_DEFENCE,80);
    set_skill(SS_PARRY,80);
    set_skill(SS_AWARENESS,100); 
    set_skill(SS_SPELLCRAFT,100);
    set_skill(SS_BLIND_COMBAT,100); 
    set_skill(SS_FORM_DIVINATION,100);
    set_skill(SS_ELEMENT_LIFE,100); 
    set_skill(SS_ACROBAT,50);    
    
    add_prop(CONT_I_WEIGHT, 81648);
    add_prop(CONT_I_HEIGHT, 180);      

/* 
*   Actions 
*/

    set_act_time(10);
    set_cact_time(5);
    add_chat("I must have left that book in my office.");
    add_chat("Something is afoot in the graveyard, I am sure of it.");
    add_act("emote looks concerned.");
    add_act("emote raises a prayer to Tyr.");

    add_ask( ({ "book" }),
    "say I was studying an ancient book of scriptures while in the city hall.", 1);
    add_ask( ({ "graveyard" }),
    "say Some of the residents in the area tell me they have seen things"
        +" moving about in the graveyard at night. He couldn't have come back.", 1);    

    

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
        BREASTPLATE,
        SHIELD,
        HELM,
        BRACERS,
        GREAVES,
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
