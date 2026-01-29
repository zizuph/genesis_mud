/*
 *    Quest person. He will send players to the textile mill to
 *    find a hidden ledger showing how much financial damage his
 *    ancestor caused so he can make amends with the town.
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

#define WEAPON WEP_DIR + "cadorna_dagger"
#define ROBE ARM_DIR + "cadorna_robe"
#define BOOTS ARM_DIR + "phlan_light_boots"

void arm_me();

void create_monster()
{
    string type, phys;
    int i;

    seteuid(getuid());
    
    set_living_name("ennio");
    set_name("ennio"); 
    add_name("cadorna");    
    set_title("councilman of Phlan");    
    set_race_name("human");
    set_adj( ({"youthful", "charismatic"}) );         
    set_gender(G_MALE);    
    
    set_short("youthful charismatic male human"); 
    set_long("Heir to the Cadorna textile wealth, Ennio Cadorna is"
        +" the kind of man you want running a business. He has an air"
        +" of both intelligence and capability along with the exuberance"
        +" of youth. He is the junior member of the council.\n");      

/*
*   size and skills
*/

    set_stats(((100, 110, 90, 100, 90, 80)));

    set_alignment(400);

    set_skill(SS_WEP_KNIFE,50);
    set_skill(SS_DEFENCE,50);
    set_skill(SS_PARRY,50);
    set_skill(SS_AWARENESS,75); 
    set_skill(SS_SPELLCRAFT,100);
    set_skill(SS_TRADING,100); 
    set_skill(SS_APPR_OBJ,100); 
    set_skill(SS_APPR_VAL,100); 
    set_skill(SS_ACROBAT,50);    
    
    add_prop(CONT_I_WEIGHT, 77192);
    add_prop(CONT_I_HEIGHT, 182);      

/* 
*   Actions 
*/

    set_chat_time(30);
    add_chat("The employees are doing excellent work.");
    add_chat("Phlan is continuing to grow.");

    set_act_time(25);
    add_act("emote adjusts the fit of his robe.");
    
    set_cchat_time(10);
    add_cchat("Guards! Guards! I am being attacked!");   

    set_cact_time(10);
    add_cact("emote gets a frightened look in his eyes.");
    
    add_ask( ({ "mill", "textile mill" }),
    "say My family has owned the Cadorna Textile Mill for generations.", 1);    

    
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
        ROBE,
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
