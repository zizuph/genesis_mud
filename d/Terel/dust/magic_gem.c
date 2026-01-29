/*
 * This is the alternate object, as suggested by me.
 *
 * Mrpr, Okt 1993
 *
 * Recoded by Sorgum on the suggestion of Olorin, May 1994
 */
inherit "/std/object";

#include <stdproperties.h>
#include <ss_types.h>
#include <tasks.h>
#include <macros.h>

#define CHARGE_TIME 2000
#define TELE_DELAY  10
#define CHARGE_MANA 50
#define LOST_GEM_LOG "/d/Terel/open/lost_gem_log"

#define TO      this_object()
#define TP      this_player()
#define BSN(xx) break_string(xx + "\n", 70)

/*
 * Prototypes
 */

static int decrease_charges(int ch);
static void fix_long(int ch);

/*
 * Global variables
 */

object to_summon;   /* The player who will be teleported */
int charges = 100;  /* How many charges left in the gem */
int swallow = 0;    /* Is the gem swallowed (1/0) */

/*
 * Function name: query_auto_load
 * Description:   Make this object auto loading
 * Returns:       A string that is the filename of this object and
 *                charges and swallow variables.
 */
string
query_auto_load()
{
    return (MASTER_OB(TO) + ":#c#" + charges + "#s#" + swallow + "#");
}

/*
 * Function name: init_arg
 * Description:   This function is called when this object is autoloaded.
 *                It will cause the charges and swallow variables to be
 *                resotred.
 */
void
init_arg(string arg)
{
    string foobar;

    if (!strlen(arg))
	return;
    
    sscanf(arg, "%sc#%d#%s", foobar, charges, foobar);
    sscanf(arg, "%ss#%d#%s", foobar, swallow, foobar);

    if (swallow)
    {
	call_out("recharge", CHARGE_TIME);
	set_no_show();
    }

    fix_long(charges);
}

/*
 * Function name: query_charges
 * Description:   How many charges remain in this gem
 * Returns:       The value of the global variable charges, which holds the
 *                number of charges left in this gem.
 */
int
query_charges()
{
    return charges;
}

int set_charges(int ch) { charges = ch; return ch;} /* for debugging */

/*
 * Function name: create_object
 * Description:   Create the gem.
 */
void
create_object()
{
    set_name("gem");
    add_name("Terel_ZODIAC_gem");
    set_adj("glowing");
    set_long("This is a strange gem glowing in all rainbow colours.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_LIGHT, 0);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_I_NO_STEAL, 1);

    add_prop(MAGIC_AM_MAGIC, ({ 30, "enchanted" }));
    add_prop(MAGIC_AM_ID_INFO,
	     ({"The gem is enchanted so that it can light up the room you " +
		   "are standing in.", 1,
		   "The gem will light up if you rub it, it gets brighter " +
		   "the more you rub it.", 10,
		   "The gem will teleport you home if you kiss it.", 20,
                   "The gem will wear out after a certain amount of " +
		   "use. To teleport wears harder on it than to light it up.",
		    30, "You can recharge the gem by swallowing it and " +
			"then regurgitating it after a (long) while.", 40 }));

    to_summon = 0;
}

/*
 * Function name: init
 * Description:   Initialize some gem related actions.
 */
init()
{
    ::init();
    add_action("do_rub", "rub");
    add_action("do_kiss", "kiss");
    add_action("do_swallow", "swallow");
    add_action("do_vomit", "regurgitate");
}

/*
 * Function name: do_rub
 * Description:   rub the gem.  Will increase the light value to a maximum
 *                of 20.
 * Arguments:     str: what to rub.
 */
int
do_rub(string str)
{
    notify_fail("Rub what?\n");
    if (str != "gem" || swallow)
	return(0);

    if (!present(TO, TP))
	return(0);

    if (!decrease_charges(1))
	return 1;

    if (query_prop(OBJ_I_LIGHT) > 20)
    {
	write("The gem doesn't look any brighter...\n");
	return 1;
    }
    
    if (query_prop(OBJ_I_LIGHT) > 0)
    {
	write("The gem looks a little brighter now!\n");
	say(QCTNAME(TP) + " does something, and the gem " +
	    TP->query_pronoun() + " is holding suddenly turns brighter!\n");
    }
    else
    {
	write("The gems suddenly is filled with a luminous glow!\n");
	say(QCTNAME(TP) + " does something, and suddenly a luminous light " +
	    "shines from a gem in " + TP->query_possessive() + " hands!\n");
    }
    add_prop(OBJ_I_LIGHT, query_prop(OBJ_I_LIGHT) + 1);
    call_out("decrease_light", 100);
    return 1;
}

/*
 * Function name: do_kiss
 * Description:   kiss the gem.  If the action is successful, the player will
 *                be teleported to their starting location.
 * Arguments:     str: what to kiss.
 */
int
do_kiss(string str)
{
    int manas, mana_cost, success;

    notify_fail("Kiss what?\n");
    if (str != "gem" || swallow)
	return(0);
    
    if (!present(TO, TP))
	return(0);

    if (to_summon)
    {
	write("But you're already kissing your lips off....\n");
	return 1;
    }

/*
    mana_cost = CHARGE_MANA + TP->query_max_mana() / 4;
*/
    mana_cost = CHARGE_MANA + 200;
    manas = TP->query_mana();
    if (manas < mana_cost)
    {
	write("A shiver goes thru your body - but it seems you're too weak.\n");
	return 1;
    }

    TP->add_mana(-mana_cost);
    success = TP->resolve_task(TASK_ROUTINE,
			       ({ SKILL_WEIGHT, 80, SS_SPELLCRAFT,
				  SKILL_WEIGHT, 20, SS_FORM_CONJURATION }));

    if (!decrease_charges(8))
	return 1;
    
    if (TP->query_attack())
    {
	write("You can't concentrate with all this action going on! " +
	      "Nothing happens.\n");
	return 1;
    }
    
    if (success > 0)
    {
	if (!decrease_charges(12))
	    return 1;
	write(BSN("You concentrate yourself and get together " +
		"all your power... You can feel something is going " +
		"on..."));
	to_summon = TP;
	call_out("do_summon", TELE_DELAY);
    }
    else
	write(BSN("You concentrate yourself and get together " +
		  "all your power... But nothing seems to happen."));
    return 1;
}

/*
 * Function name: do_swallow
 * Description:   swallow the gem.  The gem recharges while swallowed
 *                (and the player has mana).  The gem can not be used while
 *                it is in a swallowed state.
 * Arguments:     str: what to swallow.
 */
int
do_swallow(string arg)
{
    notify_fail("Swallow what?\n");
    if (arg != "gem" || swallow)
	return 0;

    write("You're having a hard time getting it down. It's large " +
	  "and unexpectadly coarse, but it's going doooooooooooooown...\n");
    set_no_show();
    if (query_prop(OBJ_I_LIGHT))
	say(QCTNAME(TP) + " swallows a bright gem.\n");
    add_prop(OBJ_I_LIGHT, 0);
    call_out("recharge", CHARGE_TIME);
    swallow = 1;
    return 1;
}

/*
 * Function name: do_regurgitate
 * Description:   regurgitate the gem.  Make the gem visible in the inventory
 *                of the player an available for use.
 * Arguments:     str: what to regurgitate
 */
int
do_vomit(string arg)
{
    notify_fail("Regurgitate what?\n");
    if (arg != "gem" || swallow == 0)
	return 0;

    write("Yuck! Bleurk! Yech!!! That's gross!\n");

    unset_no_show();
    set_no_show_composite(0);
    swallow = 0;
    while(remove_call_out("recharge") >= 0);
    return 1;
}
/*
 * Function name: do_summon
 * Description:   If the props of the player and room permit it, teleport
 *                the player to theior starting location.
 */
void
do_summon()
{
    mixed msg;

    /* Is the player still in the game? */
    if (!to_summon)
	return;

    /* Can the player be moved? */
    msg = to_summon->query_prop(OBJ_M_NO_TELEPORT);

    if (msg)
    {
	if (stringp(msg))
	    tell_object(to_summon, msg);
	else
	    tell_object(to_summon, "Somehow you cannot be summoned.\n");
	to_summon = 0;
	return;
    }

    /* Does the room object? */
    msg = environment(to_summon)->query_prop(ROOM_M_NO_TELEPORT);

    if (msg)
    {
	if (stringp(msg))
	    tell_object(to_summon, msg);
	else
	    tell_object(to_summon,
			"Somehow you cannot be summoned from this place.\n");
	to_summon = 0;
	return;
    }
	
    tell_object(to_summon, "Suddenly, you feel magically summoned...\n");
    to_summon->move_living("X",
			   to_summon->query_default_start_location());
    to_summon = 0;

}

/*
 * Function name: decrease_charges
 * Description:   Remove some charges from the gem.
 * Arguments:     ch: how many charges to remove
 */
int
decrease_charges(int ch)
{
    int oldch;

    oldch = charges;
    charges -= ch;

    if (charges < 0)
    {
	write("The gem crumbles to dust in your hand!\n");
	call_out("remove_object", 1);
	write_file(LOST_GEM_LOG, capitalize(TP->query_name()) +
		   " lost " + TP->query_possessive() + " gem (" +
		   ctime(time()) + ")\n");
	return 0;
    }

    fix_long(charges);
    return 1;
}

/*
 * Function name: dispel_magic
 * Description:   Function called by a dispel spell
 * Argument:      strength - How strong the dispel is
 * Returns:       0 - No dispelling, 1 - Object dispelled
 */
dispel_magic(int strength)
{
    object pl;

    if (strength < 30)
	return 0;

    if (query_prop(OBJ_I_LIGHT) > 0)
    {
	pl = environment(TO);
	write("The light in the gem fails!\n");
	if (living(pl))
	    say("The light in the gem held by " + QCTNAME(pl) +
		" suddenly goes out!\n");
	else
	    say("The light in the gem suddenly goes out!\n");
	add_prop(OBJ_I_LIGHT, 0);
    }

    if (strength > 40 && to_summon)
    {
	write("The gem twitches in your hands. Something is amiss!\n");
	to_summon = 0;
    }

    if (strength > 50)
    {
	write("You hear a faint crunching sound from the gem!\n");
	decrease_charges(charges - 1);
    }

    if (strength > 60)
	decrease_charges(charges);
    
    return 1;
}

/*
 * Function name: decrease_light
 * Description:   Adjust the light property and print messages
 */
void
decrease_light()
{
    object pl;
	
    if (query_prop(OBJ_I_LIGHT) <= 0)
	return;

    pl = environment(TO);

    if (pl && !living(pl))
	pl = 0;
    
    add_prop(OBJ_I_LIGHT, query_prop(OBJ_I_LIGHT) - 1);

    if (pl)
    {
	if (query_prop(OBJ_I_LIGHT) > 0)
	{
	    tell_object(pl, "The gem suddenly turns a bit duller!\n");
	    say("The bright gem held by " + QCTNAME(pl) +
		" suddenly turns a bit duller!\n", pl);
	}
	else
	{
	    tell_object(pl, "The luminous glow from the gem suddenly " +
			"winks out!\n");
	    say("The light emanating from the gem held by " + QCTNAME(pl) +
		" suddenly winks out!\n", pl);
	}
    }
    else
    {
	if (query_prop(OBJ_I_LIGHT) > 0)
	    say("The bright gem suddenly turns a bit duller!\n");
	else
	    say("The light emanating from the gem suddenly winks out!\n", pl);
    }
}

/*
 * Function name: recharge
 * Description:   Add charges to the gem and take mana
 */
void
recharge()
{
    int mana, i;
    
    call_out("recharge", CHARGE_TIME);

    mana = environment(TO)->query_mana();
    
    if (mana <= CHARGE_MANA)
	return;

    if (charges <= 95)
    {
	write("You feel a funny twitch in your stomache!\n");

	charges += 5;
	environment(TO)->add_mana(-CHARGE_MANA);

	fix_long(charges);
    }
    else
    {
	write("Your tummy is a bit upset!\n");
	for (i = 0 ; i < 5 + random(10) ; i++)
	    TP->command("burp");
    }
}

/*
 * Function name: enter_env
 * Description:   The container enters a new environment
 * Arguments:     dest - The destination
 *                old  - From what object
 */
void
enter_env(object dest, object old)
{
    object *obs;
    int i, change;
    string player_name;
    string *losers;
    string who;

    obs = all_inventory(dest);

    change = 0;
    for (i = 0; i < sizeof(obs); i++)
    {
	if (obs[i]->id("Terel_ZODIAC_gem") && obs[i] != this_object())
	{
	    obs[i]->remove_object();
	    change++;
	}
    }

    if (change)
	write("The gems disintegrate into fine dust! However... the cloud " +
	      "of incandescent particles immediately condences into a " +
	      "single gem again!\n");


    /*
     * Make sure players didn't cheat or exploit a bug to get another gem!
     */
    
    if (file_size(LOST_GEM_LOG) <= 0)
	return;

    player_name = TP->query_name();
    
    seteuid(getuid());
    losers = explode(read_file(LOST_GEM_LOG), "\n");
    for (i = 0; i < sizeof(losers); i++) {
	who = explode(losers[i], " ")[0];
	if (who == player_name) {
	    TP->catch_msg("Your glowing gem disintigrates into fine dust!\n");
	    TO->remove_object();
	}
    }
}

/*
 * Function name: fix_long
 * Description:   Change the long description of the object to reflect the
 *                number of chargers remianing.
 * Arguments:    ch - the number of charges left in the gem.
 */
void
fix_long(int ch)
{
    string desc = "This is a strange gem glowing in all rainbow colours. ";
    string aux_desc;

    switch (ch) {
    case 50..100:
	aux_desc = "\n";
	break;
    case 25..49:
	aux_desc = "The colours look a bit faded though.\n";
	break;
    case 11..24:
	aux_desc = "The colours look very faded though, and you can see " +
	    "fine cracks all over the surface.\n";
	break;
    case 0..10:
	aux_desc = "The colours look very faded though, and the surface is " +
	    "so riddled with flaws and cracks it almost looks opaque.\n";
	break;
    }

    set_long(desc + aux_desc);
}
	
