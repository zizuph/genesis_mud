/*
 * Quest person
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
#define BOD_ARM ({"dress"})
#define NECK_ARM ({"locket"})

void arm_me();

void create_monster()
{
    string type, phys;
    int i;

    seteuid(getuid());
    
    set_living_name("brandi");
    set_name("brandi");  
    set_title("the Bitter Blade waitress");    
    set_race_name("human");
    set_adj( ({"blue-eyed", "blonde-haired"}) );         
    set_gender(G_FEMALE);    
    
    set_short("blue-eyed blonde-haired female human"); 
    set_long("This young lady's eyes could steal a sailor from the"
        +" sea. She is usually working here behind the bar.\n");        

/*
*   size and skills
*/

    default_config_npc(35 + random(10));

    set_alignment(110 + random(50));

    set_skill(SS_WEP_KNIFE,30);
    set_skill(SS_DEFENCE,30);
    set_skill(SS_PARRY, 30);
    set_skill(SS_AWARENESS, 60); 
    
    add_prop(CONT_I_WEIGHT, 46000);
    add_prop(CONT_I_HEIGHT, 160);      

/* 
*   Actions 
*/

    set_act_time(10);
    set_cact_time(5);
    add_chat("He said I was a fine girl, but his love is the sea.");
    add_chat("I'm glad I don't have to work today.");
    add_act("emote sings a popular song loudly.");
    add_act("emote dances around the bar like no one is watching.");

    add_ask( ({ "bar", "pub" }),
    "say The Bitter Blade has been serving sailors for years.", 1);
    add_ask( ({ "him", "boyfriend" }),
    "say He came on a summer's day bearing gifts from far away.", 1);    

    

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
    arm = clone_object(ARM_DIR + "dress1");
    arm -> move(this_object());
    arm = clone_object(ARM_DIR + "locketandchain");
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
    command("curtsey gracefully " + OB_NAME(who));
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
