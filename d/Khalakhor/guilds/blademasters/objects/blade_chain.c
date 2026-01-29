/*
 * blade_chain.c
 *
 * This object is the 'guild object' of the Blademasters of Khalakhor.
 * It's nothing special in itself, however. The type of metal in the
 * chain is either silver or gold. Gold chains are only worn by members
 * with sup. guru sword, representing the High Blademasters.
 * The number of links in the chain vary from 5 to 10, depending on
 * the guildstat (ranging from 0 to 161+).
 *
 * Khail - Feb 24/97
 * Teth  - Feb 25/99 - modified to use /lib/wearable_item.c
 * Zhar  - Nov 21/12 - moved leave_blademasters code to the shadow
 */
#pragma strict_types

#include "defs.h"
#include <macros.h>
#include <language.h>
#include <cmdparse.h>
#include <wa_types.h>

#define CHAIN_SUBLOC              "_khalakhor_blade_chain_subloc"

inherit "/std/object";
inherit "/lib/wearable_item.c";

string type;
int links,
    chain_worn;
object owner;

public string query_chain_type();
public string query_chain_links();

/*
 * Function name: is_blademaster_equipment
 * Description  : Is this item a blademaster item?
 * Arguments    : n/a
 * Returns      : 1 - it is.
 */
public int
is_blademaster_equipment()
{
    return 1;
}

/*
 * Function name: query_owner
 * Description  : Simply returns the current owner variable,
 *                if one is set, which is the Blademaster that
 *                first held this chain. Mainly for debugging.
 * Arguments    : n/a
 * Returns      : 'owner' global variable.
 */
public object
query_owner()
{
    return owner;
}

/*
 * Function nane: update_adjectives
 * Description  : Used to 'refresh' the adjectives based on the
 *                wearer's current status.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
update_adjectives()
{
    remove_adj(query_adjs());
    set_adj("small");
    add_adj(query_chain_type());
}

/*
 * Function name: query_chain_type
 * Description  : Queries the chain type. Automatically updates if
 *                the environment is a blademaster, else relies on
 *                current value.
 * Arguments    : n/a
 * Returns      : "silver" or "gold"
 */
public string
query_chain_type()
{
    remove_adj(type);
    if (IS_BLADEMASTER(environment()) &&
        environment()->query_skill(SS_WEP_SWORD) >= HIGH_SWORD_SKILL)
        type = "gold";
    add_adj(type);
    return type;
}

/*
 * Function name: query_chain_links
 * Description  : Queries the number of links in the chain.
 * Arguments    : n/a
 * Returns      : The number of links in the chain as a string. i.e. 'five'.
 */
public string
query_chain_links()
{
    int i;

  /* If the chain's environment is a blademaster, adjust link number. */
    if (IS_BLADEMASTER(environment()))
    {
      /* Get the lay stat / 40, limit to 5, and add 5 for */
      /* links number ranging from 5 to 10. */
        i = environment()->query_base_stat(SS_LAYMAN) / 40;
        i = (i > 5 ? 5 : i);
        links = 5 + i;
        return LANG_WNUM(links);
    }
  /* Environment isn't a blademaster, so use last set number of */
  /* links. */
    else
        return LANG_WNUM(links);
}

/*
 * Function name: value_by_links
 * Description  : Determines the value of the chain by the material
 *                it's made from, and the number of links. Value
 *                ranges from 100cc to 200cc for silver chains, and
 *                500cc to 1000cc for gold chains. For Blademasters,
 *                the chains are no_sell, however.
 * Arguments    : n/a
 * Returns      : A value in copper coins as described above.
 */
public int
value_by_links()
{
    return (20 * (query_chain_type() == "gold" ? 5 : 1)) * links;
}

/*
 * FUnction name: blademaster_info
 * Deescription : Returns a short string to remind blademasters what
 *                the syntax for blademaster help is.
 * Arguments    : n/a
 * Returns      : "" for non-blademasters, else reminds them that
 *                'help blademasters' provides info on them.
 */
public string
blademaster_info()
{
    if (TP->is_khalakhor_blademaster())
        return "You can do 'help blademaster' for information.";
    else
        return "";
}
 
/*
 * Function name: create_object
 * Description  : Turns this object into a blademaster chain.
 * Arguments    : n/a
 * Returns      : n/a
 */   
public void
create_object()
{
    set_name("chain");
    add_name(BLADEMASTER_CHAIN_NAME);
    set_short("small " + VBFC_ME("query_chain_type") + " chain");
    set_long("It is a simple, length of small " +
        VBFC_ME("query_chain_type") + " chain, with a total of " +
        VBFC_ME("query_chain_links") + " links in it. " +
        "This small collar-chain can be worn, and is a symbol of " +
        "the Blademasters. " + VBFC_ME("blademaster_info") + "\n");

    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_VALUE, VBFC_ME("value_by_links"));
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_I_BLADEMASTER_GOBJ, 1);

    type = "silver";
    links = 5;
    update_adjectives();

    config_wearable_item(A_NECK, 1, 5, this_object());
}

/*
 * Function name: remove_object (MASK)
 * Description  : What to do when the object is removed from the
 *                game.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
remove_object()
{
  /* If the chain is worn, remove it from the player, and clean */
  /* up the sublocs before final destruction. */
    if (chain_worn)
    {
        tell_object(environment(), "The " + short() + " suddenly " +
            "falls off your collar.\n");
        chain_worn = 0;
        TO->move(environment());
        environment()->remove_subloc(CHAIN_SUBLOC);
    }
    ::remove_object();
}

/*
 * Function name: wear
 * Description  : Wear the object.
 * Arguments    : what - the object
 * Returns      : 1 if we want our own messages.
 *
 */
public mixed
wear(object what)
{
    write("You wear the " + short() + " proudly on your collar.\n");
    say(QCTNAME(TP) + " clips a " + short() + " onto " +
        TP->query_possessive() + " collar.\n");
    TP->add_subloc(CHAIN_SUBLOC, TO);
    TO->move(TP, CHAIN_SUBLOC);
    chain_worn = 1;
    return 1;
}

/*
 * Function name: remove
 * Description  : Remove the chain.
 * Arguments    : what - The chain. 
 * Returns      : 1 - Stop threading.
 */
public mixed
remove(object what)
{
    if (TP->query_hp() <= 0)
    {
        TP->remove_subloc(CHAIN_SUBLOC);
        TO->move(TP);
        chain_worn = 0;
        return 1;
    }

    write("You remove the " + short() + " from your collar.\n");
    say(QCTNAME(TP) + " removes a " + short() + " from " +
        TP->query_possessive() + " collar.\n");
    TP->remove_subloc(CHAIN_SUBLOC);
    TO->move(TP);
    chain_worn = 0;
    return 1;
}

public void
leave_blademaster_guild()
{	
	TP->leave_guild_lay();
}

/*
 * Function name: show_subloc (MASK)
 * Description  : Generates a special description for a subloc.
 * Arguments    : subloc - String name of the subloc to describe.
 *                to_obj - Object pointer to the object the subloc
 *                         describes.
 *                for_obj - Object pointer to the object looking
 *                          at the subloc.
 * Returns      : A string description.
 */
public string
show_subloc(string subloc, object to_obj, object for_obj)
{
    string ret;

  /* Do nothing if 'subloc' isn't the chain subloc. */
    if (subloc != CHAIN_SUBLOC)
        return environment()->show_subloc(subloc, to_obj, for_obj);

  /* Nothing extra if the chain isn't worn. */
    if (!chain_worn)
        return "";

  /* Do nothing if the player is just checking their inventory. */
    if (to_obj->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    ret = "A small " + query_chain_type() + " chain of " + 
        query_chain_links() +
        " links is suspended from the left side of ";
    ret += (to_obj == for_obj ? "your" : to_obj->query_possessive());
    ret += " collar, down to the throat.\n";
    return ret;
}

/*
 * Function name: leave_env (MASK)
 * Description  : Makes sure that the chain is no longer worn if it
 *                leaves a player's inventory.
 * Arguments    : to - The destination environment.
 *                from - The old environment.
 * Returns      : n/a
 */
public void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    wearable_item_leave_env(from, to);

    if (!chain_worn)
        return;

    else
    {
        chain_worn = 0;
        from->remove_subloc(CHAIN_SUBLOC);
    }
}
 
/*
 * Function name: enter_env (MASK)
 * Description  : Called when this object enters a new environment.
 *                Here, we use it to set the owner of this chain
 *                to the first Blademaster who holds it.
 * Arguments    : new - Object pointer to the new environment.
 *                old - Object pointer to the last environment.
 * Returns      : n/a
 */
public void
enter_env(object new, object old)
{
    ::enter_env(new, old);

  /* If 'owner' is set, or 'new' doesn't point to an object, */
  /* or 'new' isn't a Blademaster, do nothing. */
    if (owner || !new || !IS_BLADEMASTER(new))
        return;

    else
        owner = new;
}


/* Function name: appraise_object (MASK)
 * Description  : Appraise the object.
 * Arguments    : int num - The appraise number, randomized.
 * Returns      : n/a
 */

public void
appraise_object(int num)
{
    ::appraise_object(num);

    appraise_wearable_item();
}