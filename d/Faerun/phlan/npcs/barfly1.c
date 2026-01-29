/*
 * Bar patron
 * Tharizdun, 2021
 */

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h> 
#include <wa_types.h>
#include <filter_funs.h>
#include <defs.h>

inherit "std/monster.c";
inherit "/d/Genesis/lib/intro";

#define WEAPON ({"dagger"})
#define BOD_ARM ({"shirt")}
#define GREAVES ({"pants"})

void arm_me(); 

void create_monster()

{
    string type, phys;
    int i;

    seteuid(getuid());
    
    set_living_name("aldo");
    set_name("aldo");  
    set_title("bar patron");    
    set_race_name("human");
    set_adj( ({"tipsy", "happy-go-lucky"}) );         
    set_gender(G_MALE);   
     
    set_short("tipsy happy-go-lucky male human"); 
    set_long("This inebriated man looks like he spends a lot of time" +
        " in the bar. His cheeks are a bit flushed and his speech is slurred.\n");         

/*
*   size and skills
*/

    default_config_npc(40 + random(10));

    set_alignment(110 + random(50));

    set_skill(SS_WEP_KNIFE,20);
    set_skill(SS_DEFENCE,30);
    set_skill(SS_PARRY, 30);
    set_skill(SS_AWARENESS, 60); 

    add_prop(CONT_I_WEIGHT, 68040);
    add_prop(CONT_I_HEIGHT, 175);    
 
/* 
*   Actions 
*/

    set_act_time(10);
    add_chat("Try the whishkey. It'sh great!");
    add_chat("I love thish bar!");
    add_act("emote signals a server for another drink.");
    add_act("emote stumbles as he tries to stand up.");
    
    set_cchat_time(10);
    add_cchat("Not in the face!"); 

    add_ask( ({ "bar", "pub" }),
    "say Thish ish the Bitter Blade."
    +" He points at the mural shakily.", 1);
    
    arm_me();
}

void

/*
*   adding gear
*/

arm_me()
{
    object arm, wep;

    wep = clone_object(WEP_DIR + "dagger");
    wep -> move(this_object());
    arm = clone_object(ARM_DIR + "shirt1");
    arm -> move(this_object());
    arm = clone_object(ARM_DIR + "pants1");
    arm -> move(this_object());

    command("wield weapon");
    command("wear all");

}


/*
 * This is called if the person has already been introduced before.
 */

void
greet(object who)
{
    command("nod drunkenly " + OB_NAME(who));
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

