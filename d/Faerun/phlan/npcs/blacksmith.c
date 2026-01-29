/*
* Blacksmith. He can repair armour and weapons.
* Based on Bubba in Gelan.
*
* Nerull
*
*   Edited for use in Phlan by Tharizdun, 2021
*
*/

//#pragma save_binary

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <formulas.h>
#include <wa_types.h>
#include <const.h>
#include <money.h>
#include <cmdparse.h>
#include <language.h>
#include <options.h>

inherit FAERUN_NPC_BASE;
inherit "/lib/trade";

#define WEAPON ({"smith_hammer"})

void arm_me();

int price; /* price on copper of the thing currently being worked on */

object finished_item;

#include "repairs_new.c"



mixed *fixing;
int testing;

 string
 sign()
{
	return
		" ______________________________________ \n" +
		"| Fixing weapons and armours for coin  |\n" +
		"|  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  |\n" +
		"|                                      |\n" +
		"| you may:                             |\n" +
		"| --------                             |\n" +
		"| Sharpen weapons                      |\n" +
		"| Wax weapons                          |\n" +
		"| Fix armours                          |\n" +
		"|                                      |\n" +
		"| All prices for weapons depends on    |\n" +
		"| their value. Do: cost <weapon>       |\n" +
		"|______________________________________|\n";
}


void
create_monster()
{	
	set_name("Oleson");
	add_name("blacksmith");
	add_name("smith");
	set_race_name("human");
	set_adj(({ "broad-chested","bald" }));

	set_short("broad-chested bald male human");
	set_long("The town blacksmith has thickly corded muscles bulging"
        +" from his arms and seems like he could work at his forge"
        +" tirelessly for hours. Scars cover his rough calloused hands"
        +" from working with hot and sharp tools.\n");

	set_gender(G_MALE);
	set_alignment(100);
	add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(OBJ_I_NO_ATTACK, 1);
    add_prop(OBJ_I_NO_MAGIC_ATTACK, 1);
	add_prop(NPC_M_NO_ACCEPT_GIVE, 0);

	default_config_npc(150);
	set_base_stat(SS_CON, 200);
	set_base_stat(SS_STR, 200);

	set_skill(SS_WEP_CLUB, 70);
	set_skill(SS_DEFENCE, 100);
	set_skill(SS_AWARENESS, 60);
    
    add_prop(CONT_I_WEIGHT, 99792);
    add_prop(CONT_I_HEIGHT, 185);    
    
    add_item( ({"sign"}), sign);

	set_chat_time(5);
	add_chat("Do your armours need repairs?");
    add_chat("Never leave town with a dull sword.");
    
    set_act_time(10);    
	add_act("emote arches his back and stretches out his muscular arms.");
	add_act("emote wipes sweat from his brow.");
	add_act("emote cleans and oils his tools.");

    set_cact_time(10); 
	add_cact("curse violently");
	add_cact("tackle");
	
	config_default_trade();
    
    arm_me();
}


void
arm_me()
{
    object arm, wep;

    wep = clone_object(WEP_DIR + "smith_hammer");
    wep -> move(this_object());

    command("wield weapon");

}


mixed
query_option(int opt)
{
	return (opt == OPT_UNARMED_OFF);
}


void
init_living()
{
	::init_living();
	
	/* weapon repair */
	add_action(do_w_fix, "sharpen");
	add_action(do_w_fix, "wax");
	add_action(do_w_cost, "wcost");

	/* armour repair */
	add_action(do_a_fix, "fix");
	add_action(do_a_cost, "acost");
}

/*
*   This is called if the person has already been introduced before.
*/

void
greet(object who)
{
    command("bow respectfully " + OB_NAME(who));
}

/*
*   This is called if the person has not been introduced before.
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
    {
        react_to_introduction(name);
    }
}
