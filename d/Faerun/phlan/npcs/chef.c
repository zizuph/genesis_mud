/* /d/Faerun/guilds/fire_knives/npc/chef/
 * 
 * Nerull 2019
 *
 *updated as Phlan innkeeper
 *
 *Tharizdun 2021
 *
 */
 
inherit "std/monster.c";
inherit "/std/combat/unarmed";   /* Get standard unarmed routines */
inherit "/d/Genesis/lib/intro";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h> 
#include <wa_types.h>
#include <filter_funs.h>
#include <defs.h>


/*
* Function name: create_monster()
* Description  : Constructor. Edit this to change monster.
*/
nomask void create_monster()
{
    seteuid(getuid());

    set_race_name("human");
    add_name("daniel");

    set_adj("short");
    add_adj("stocky");

    set_gender(G_MALE);
    
    add_prop(LIVE_I_SEE_DARK, 100);
    add_prop(LIVE_I_SEE_INVIS, 99);
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_NO_STUN, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);
    add_prop(OBJ_I_RES_MAGIC, 100);
    add_prop(OBJ_I_NO_ATTACK, 1);
    add_prop(OBJ_I_NO_MAGIC_ATTACK, 1);
    
    set_short("short stocky male human");
    
    set_long("This is Daniel, a classically trained chef who has come "
    +" to the Moonsea to bring his culinary style to a new audience."
    +" His calloused hands indicate years of physical labor.\n");

    set_stats(({ 310, 310, 320,
                 243, 320, 280 }));

    set_hitloc_unarmed(A_HEAD, 25, 15, "head");
    set_hitloc_unarmed(A_R_ARM, 25, 10, "right arm");
    set_hitloc_unarmed(A_L_ARM, 25, 10, "left arm");
    set_hitloc_unarmed(A_BODY, 25, 45, "body");
    set_hitloc_unarmed(A_LEGS, 25, 20, "legs");

    set_attack_unarmed(W_LEFT,  55, 55, W_BLUDGEON,
    80, "left fist");

    set_attack_unarmed(W_RIGHT,  55, 55, W_BLUDGEON,
    80, "right fist");
    
    set_attack_unarmed(W_FOOTR, 40, 40, W_BLUDGEON,
    0, "left foot");

    set_attack_unarmed(W_FOOTL, 40, 40, W_BLUDGEON,
    0, "right foot");

    set_skill(SS_UNARM_COMBAT,100);
    set_skill(SS_DEFENCE,100);
    set_skill(SS_AWARENESS,100);
    set_skill(SS_ACROBAT,100);
    
    add_prop(CONT_I_WEIGHT, 68040);
    add_prop(CONT_I_HEIGHT, 165);    
	
	set_act_time(5);
    set_cact_time(5);
    add_act("smile proudly");
    add_act("emote peers into the kitchen to check on his staff.");
	add_act("emote inpects an empty table to ensure it is ready for the next customer.");
	add_act("emote whispers something to a server.");
	add_act("emote leaves briefly to the kitchen to check on a"
        +" customer's order.");
	add_act("emote comments on the superior quality of food coming"
        +" out of the kitchen.");
	add_act("emote praises the local fishermen for their bountiful catch.");
	
	set_default_answer("The short stocky male human "
	    +"says: I have never prepared that dish before. Do you have"
	    +" the recipe?\n");
	
	add_ask( ({ "special" }),
    "say Read the menu to find out more about the special!", 1); 

    add_ask( ({ "recipe", "recipes" }),
    "say My recipes change from time to time. Make sure to check back"
	    +" whenever you are in the area.", 1);

    add_ask( ({ "menu" }),
    "say It is mounted on the wall. Feel free to read it.", 1);

    add_ask( ({ "cook" }),
    "say I specialize in seafood. Check the menu for"
	    +" today's specials.", 1);

    add_ask( ({ "table", "tables" }),
    "say There are open tables if you would like to have"
	    +" a seat.", 1);
 
	add_ask( ({ "quest", "task", "help" }),
    "say I am not looking for any help at this time. Thank you"
        +" for asking", 1);   
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