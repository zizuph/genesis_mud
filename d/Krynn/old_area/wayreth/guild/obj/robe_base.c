/*
 * The robe_base for the robe worn by the Wizards of High Sorcery
 *
 * by Rastlin 950525
 *
 * Todo:
 *   Better description when examine and wearing the hood.
 *      'He is wearing a black velvet robe, with a hood pulled low over
 *       his face.'
 *   Add magic protection.
 */
#pragma save_binary
#pragma strict_types

#include "/d/Krynn/common/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include "../local.h"
#include "../../local.h"
#include <macros.h>
#include <state_desc.h>
#include <formulas.h>

inherit "/std/armour";

int gInitiated = 0;
object gShadow = 0;

/* Prototypes */
static void initiate_robe(object who);
static void get_soul(object who);
static void get_spell_book(object who);

public void
create_robe()
{
}

public nomask void
create_armour()
{
    create_robe();

    add_name(GUILD_OBJECT);
    set_af(TO);
    seteuid(getuid());

    set_default_armour(12, A_ROBE, 0, 0);
    
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(OBJ_S_WIZINFO, "This robe is a guild item, worn by the members " +
	     "of the Wizards of High Sorcery. It is the only armour they " +
	     "are able to wear and are therefore better than most other " +
	     "robes found in the game. It provides small protection against " +
	     "most of the elements, also better protection against normal " +
	     "weapons than a normal robe should do. Recent changes in the "+
	     "subcontracting of tailors has resulted in a more heavily "+
	     "padded robe.\n");
    add_prop(MAGIC_AM_ID_INFO, ({ "This robe is protected by runes of " +
				  "magic.\n", 10, "The runes protects the " +
				  "wearer against most natural threats.\n",
				  50 }));
    add_prop(MAGIC_AM_MAGIC, ({ 50, "enchantment" }));

    add_prop(OBJ_I_VOLUME, 4250); /* The robe takes alot of place */
    add_prop(OBJ_I_WEIGHT, 2500);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(8) + 1000);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_M_NO_BUY, 1);
}

/*
 * Function name: query_auto_load
 * Returns:       The proper autoload string
 */
public string
query_auto_load()
{
    return MASTER + ":";
}

/*
 * Function name: init_arg
 * Description:   Called when the object is autoloaded
 * Arguments:     str - The string given when saved
 */
public void
init_arg(string str)
{
    if (calling_object() != TP)
        return;

    if (!gInitiated)
        set_alarm(0.1, 0.0, &initiate_robe(TP));
}

/*
 * Function name: force_init
 * Description:   Force an init. Should only be called by ADMIN
 * Arguments:     who - The player
 */
public void
force_init(object who)
{
    if (MASTER_OB(previous_object()) != ADMIN)
        return;

    initiate_robe(who);
}

/*
 * Function name: initiate_robe
 * Description:   Make a few guild checks so that everything is as
 *                it should.
 * Arguments:     who - The player carring the robe.
 */
static void
initiate_robe(object who)
{
    int result = ADMIN->restore_player(who);
    string color;
    
    gInitiated = 1;

    if (result == 1)
    {
        set_alarm(1.0, 0.0, &get_spell_book(who));
        set_alarm(2.0, 0.0, &get_soul(who));
	return;
    }    

    if (!result)
    {
        // LOG("violation", C(RNAME(who)) + " is not a member. [ROBE-SECURITY]");
	who->catch_msg("The " + short() + " disappears in a puff of smoke.\n");
        remove_object();
        return;
    }

    who->catch_msg("Arrghh... The Tower of Wayreth couldn't add the " +
		   "shadow to you. Try to visit the guild, if that " +
		   "doesn't help contact a Krynn-wizard or the " +
		   "'playerarch' team.\n");
}

/*
 * Function name: get_soul
 * Description:   Add the cmdsouls to the member
 */
static void
get_soul(object ob)
{
    int i;
    string *souls;
    string soul_name;

    soul_name = WGUILD + TO->query_robe_color() + "/mage_soul";

    souls = ob->query_cmdsoul_list();

    i = sizeof(souls);
    while (i--)
        ob->remove_cmdsoul(souls[i]);

    ob->add_cmdsoul(soul_name);
    ob->add_cmdsoul(WGUILD + "obj/wohs_cmd_normal");

    if (ADMIN->query_conclave_member(RNAME(ob)))
	ob->add_cmdsoul(WGUILD + "obj/wohs_cmd_conclave");

    i = sizeof(souls);
    while (i--)
        if (souls[i] != soul_name)
	     ob->add_cmdsoul(souls[i]);
    ob->update_hooks();
}

/*
 * Function name: get_spell_book
 * Description:   Give the spell-book to the player.
 * Arguments:     who - The player
 */
static void
get_spell_book(object who)
{
    object book;

    book = clone_object(WMAGIC + "spellbook");
    book->move(who);
    book->setup_spells(who->query_wohs_level());
}

/*
 * Function name: wear
 * Description:   Called from the armour when worn
 * Arguments:     what - The object worn.
 * Returns:       True if it went ok, a string or -1 otherwise
 */
public mixed
wear(object what)
{
    if (what != TO)
        return -1;

    if (THIS_GUILD(TP))
    {
        write("You wrap the " + short() + " around your body.\n");
	say(QCTNAME(TP) + " wears " + LANG_ADDART(short()) + ".\n");
	return 1;
    }

    TP->heal_hp(-random(TP->query_hp()));

    set_alarm(0.0, 0.0, remove_object);

    return "When you try as best to put the " + short() + " on, " +
           "it disappears in a bright light. Ouch, that hurt.\n";
}

/*
 * Function name: remove
 * Description:   Called when the robe is removed
 * Arguments:     what - The object being removed
 * Returns:       False or -1.
 */
public mixed
remove(object what)
{
    if (what != TO)
        return -1;

    if (gShadow)
        gShadow->remove_shadow();

    return 0;
}

/*
 * Function name: hood_player
 * Description:   This will put on the hood for the player.
 *                Make sure all the tests are done before
 *                calling this function.
 * Arguments:     player - The player object
 */
public void
hood_player(object player)
{
    string color = TO->query_robe_color();

    color = ((color == TYPE_RED ? "crimson" : (color == TYPE_BLACK ?
					       "dark" : color)));

    gShadow = clone_object(GOBJ + "hood_shadow");
    gShadow->set_color(color);
    gShadow->shadow_me(player);
}

/*
 * Function name: wear_hood
 * Description:   Wear the hood.
 * Arguments:     str - The proper string to wear the hood.
 * Returns:       True or false.
 */
public int
wear_hood(string str)
{
    if (!str || !strlen(str) || str != "hood")
        return 0;

    if ((query_worn() != TP) || gShadow)
        return 0;

    write("You pull the hood of your robe low down over your face.\n");
    say(QCTNAME(TP) + " pulls " + POSSESSIVE(TP) + " hood over " +
	POSSESSIVE(TP) + " head, hiding " + POSSESSIVE(TP) + " face.\n");

    hood_player(TP);

    return 1;
}

/*
 * Function name: remove_hood
 * Description:   Remove the worn hood.
 * Arguments:     str - The proper string to remove the hood.
 * Returns:       True or false.
 */
public int
remove_hood(string str)
{
    if (!str || !strlen(str) || str != "hood")
        return 0;

    if ((query_worn() != TP) || !gShadow)
        return 0;

    write("You remove the hood, and once again reveal your face.\n");
    say(QCTNAME(TP) + " removes " + POSSESSIVE(TP) + " hood from " +
	POSSESSIVE(TP) + " face.\n");

    gShadow->remove_shadow();

    return 1;
}

public void
init()
{
    ::init();

    if (TP != E(TO))
        return;

    add_action(wear_hood, "wear");
    add_action(remove_hood, "remove");
}

/*
 * Function name: query_recover
 * Description:   This armour shouldn't, recover it autoloads.
 */
public int
query_recover() { return 0; }

/*
 * Function name: leave_env
 * Description:   Called when the robe leaves its environment.
 */
public void
leave_env(object from, object to)
{
    if (gShadow)
        gShadow->remove_shadow();

    ::leave_env(from, to);     
}

/*
 * Function name:
 * Description:
 * Arguments:
 * Returns:
 */
