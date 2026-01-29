/*
* Blacksmith. He can repair armour and weapons, and coat 
* weapons with silver vs lycanthropes.
*
* Based on Bubba in Gelan.
*
* Nerull
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

int price; /* price on copper of the thing currently being worked on */

object finished_item;

#include "repairs_new.c"



mixed *fixing;
int testing;

string
sign()
{
	return
		" ______________________________________n\n" +
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
	
	set_name("putin");
	add_name("blacksmith");
	add_name("smith");
	set_race_name("human");
	set_adj(({ "travelling","muscular" }));

	set_short("travelling muscular blacksmith");
	set_long("The travelling blacksmith is a tall muscular human. It seems "
        +"he has temporary set up a small travelling forge, complete with "
        +"tools "
        +"for all sorts of repairs. You see "
		+"many scars on his hands from cuts and molten metal, probably "
		+"due to his many experiences in fixing weapons and "
        +"armours for coin. You notice he is wearing a sign that "
        +"is probably worth examining.\n");

	set_gender(G_MALE);
	set_alignment(100);
	add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(OBJ_I_NO_ATTACK, 1);
    add_prop(OBJ_I_NO_MAGIC_ATTACK, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
	

	add_prop(NPC_M_NO_ACCEPT_GIVE, 0);

	default_config_npc(150);
	set_base_stat(SS_CON, 200);
	set_base_stat(SS_STR, 200);

	set_skill(SS_WEP_CLUB, 70);
	set_skill(SS_DEFENCE, 100);
	set_skill(SS_AWARENESS, 60);
    
    add_item( ({"sign"}), sign);

	set_act_time(3);

	add_act("What can repair for you, traveler?");
	add_act("emote is looking for customers that need repairs.");
	add_act("emote contemplates about the weather.");
	add_act("emote eats some salted jerky.");
	add_act("emote contemplates about something else.");
	add_act("yawn");
	add_act("sweat");
	add_act("swear");

	add_cact("curse violently");
	add_cact("tackle");
	

	config_default_trade();
}


mixed
query_option(int opt)
{
	return (opt == OPT_UNARMED_OFF);
}


int
do_treat(string str)
{
	object *oblist, tp, shadow;

	int int_str, value, *money_arr, s;
    
	string item_name, pay_type, get_type, coin_pay_text, coin_get_text,
		verb, material;
        
	verb = query_verb();
    
	tp = this_player();
    
	value = 500;
    
	notify_fail(capitalize(verb) + " what?\n");
    
	if (!str)
    {
        return 0;
    }
		
	mixed  *adjs;
    
	if (!strlen(str))
	{ 
		notify_fail("Treat which weapon?\n");
		return 0;
	}
    
	str = lower_case(str);
    
	if (!parse_command(str, tp, "[the] %i",
		oblist))
	{
		notify_fail(capitalize(query_verb()) + " which blade?\n");
		return 0;
	}
    
	oblist = NORMAL_ACCESS(oblist, 0, 0);
    
	if (!(s = sizeof(oblist)))
	{
		notify_fail(capitalize(query_verb()) + " which blade?\n");
		return 0;
	}

	if (s > 1)
	{
		notify_fail("Be more specific. Which one?\n");
		return 0;
	}
    
	if ((function_exists("create_object", oblist[0]) != "/std/weapon"))
	{
		notify_fail("That is not really a weapon!\n");
		return 0;
	}
    
    if (oblist[0]->query_wt() != W_KNIFE)
    {
        notify_fail("Your weapon must be a knife or a dagger for this treatment "
        +"to work!\n");
        
        return 0;
    }
       
	if (oblist[0]->query_nondull_shadow() == 1)
	{
        notify_fail("The " + oblist[0]->short() + " is already treated.");
        
		/*tell_room(this_object(), break_string(
			"The travelling muscular blacksmith says: The " + oblist[0]->short() + " is already treated, "
			+ tp->query_nonmet_name() + ".\n", 70));*/
		return 0;
	}
    
	write("You give the " + oblist[0]->short() + " to the travelling muscular blacksmith.\n");
    
	say(QCTNAME(tp) + " gives the travelling muscular blacksmith " + tp->query_possessive() +
		" " + oblist[0]->short() + ".\n");
        
        
    shadow = clone_object("/d/Faerun/highroad/npcs/nondull_shadow");
        
	shadow->shadow_me(oblist[0]);
        
	set_alarm(2.0, 0.0, &shadow->init_nondull_shadow());
    
    command("travelling muscular blacksmith "
            +"applies some clear mystical liquid on the "
			+ oblist[0]->short() + " and puts it in the heat of the forge "
            +"for a minute. The "+oblist[0]->short()+" starts to radiate "
            +"a dim, nearly invisible purple glow.\n"
			+ "The travelling muscular blacksmith returns the blade.\n");
    
    tell_room(environment(this_object()),
			"The travelling muscular blacksmith "
            +"applies some clear mystical liquid on the "
			+ oblist[0]->short() + " and puts it in the heat of the forge "
            +"for a minute. The "+oblist[0]->short()+" starts to radiate "
            +"a dim, nearly invisible purple glow.\n"
			+ "The travelling muscular blacksmith returns the blade.\n");
            
	
	return 1;
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
    
    /* Special services */
    //add_action(do_treat, "treat");
}


