/*
 *
 * /std/magic.shadow.c
 * 
 * This object is intended to shadow magical spell effects which have
 * a duration which is not instant. It is in charge of handling the movement
 * of the effect from room to room, and the ensuing conflict between the spells.
 * Plus of course whatever actual effects are being caused.  
 *
 * spell_effect should be set to shadow the highest level container object(s)
 * defining the spells area of effect.  The shadow will then ensure that any
 * objects which enter the inventory are checked to make sure there are no 
 * magical objects in their deep_inventory.  If there are, the dispell 
 * routines are called.

Example:

Commentary: 
TRANSMUTATION spells need never use this if the effect is permanent.
    Permanent transmutations are in all ways the same as ordinary objects.
    Temporary transmutations (polymorph, eg) are treated as conjurations are.

CONJURATION spells are always magical in nature.  Even permanently conjured
    objects can be dispelled, in which case the conjured object disappears (is
    destructed)	To do a conjuration effect, simply clone the conjured object
    and the clone this shadow and shadow the newly cloned object.

ILLUSIONS can be written in many ways, but always use this shadow.
    An illusion can be written using another object (in which case the
    conjuration rules apply) or can be just modification of existing
    objects (often the room the player is in, but could be anything.)  For
    this, the shadow can be used to rewrite the appropriate functions.

ABJURATION spells can be either dispelling or protective.  Only the
    latter have durations and use this shadow.

DIVINATION spells will usually be instant, but some will be centered
    on a living creature (usu. the caster) and have a duration.

ENCHANTMENT spells will ordinarily affect an existing object.	This
    object will be the shadowed object.	The shadow will usually be able to
    provide all the functionality needed. If dispelled, the original object
    remains, but the spell is gone.  (The shadow is removed)


*/

inherit "/std/shadow";

#include <ss_types.h>

object shadow_who;
object spell;

static int magic_alarm_id;

int query_magic_alarm() { return magic_alarm_id; }

/*
 * Function:	qme
 * Description: Returns the shadowed object.
 */
object
qme()
{
    return shadow_who;
}

/*
 * For now, we will redefine all the public functions in /std/shadow
 */

/*
 * Function name: autoload_shadow
 * Description:   Called by the autoloading routine in /std/player_sec
 *                to ensure autoloading of the shadow
 */
public void
autoload_shadow(mixed arg)
{
    write("Shadow\n");
    ::autoload_shadow(arg);
}

/*
 * Function:	dispel_effect
 * Arguments:	attacker - (object) : Which object caused the dispell.
 *				      Default previous object.
 *
 * Description: What to do when the spell effect is dispelled.
 */
nomask varargs void
dispel_magic_effect(object attacker = previous_object())
{
    this_object()->notify_dispel(attacker);

    qme()->remove_magic_effect(this_object());

    if (this_object()->query_remove_on_dispel())
        remove_object();
    else
        remove_shadow();
}

#include "/d/Krynn/rastlin/open/spells/lib.effect.c"

/*
 * Function name: shadow_me
 * Description:   Called from object to make us shadow it.
 * Returns:       True if shadowed
 */
public varargs int
shadow_me(mixed to_shadow)
{
    if(!::shadow_me(to_shadow))
        return 0;
    return 1;
}

/*
 * Function: init_shadow
 * Description:
 *	Should be used to initialize the shadow effect.
 */
varargs nomask public mixed
move_spell(object target, int power)
{
    object caster;
    string err_msg;
    mixed *vars;

    spell = previous_object();
    shadow_who = target;

    vars = spell->query_all_variables();

    caster = vars[0];

    if(!shadow_me(target))
	return "Could not shadow target.\n";

    set_power(power);

    set_element(vars[1]);
    set_duration(vars[2]);
    set_protect(vars[3]);
    set_remove_on_dispel(vars[4]);
    set_reducible(vars[5]);

    magic_alarm_id = set_alarm(itof(query_duration()), 0.0, 
                     "dispel_magic_effect");

    target->add_magic_effect(this_object());

    return 0;
}

string
stat_object()
{
    string str, rest;

    str = "\nMagical effect : " + file_name(this_object()) + "\n"
	+ "Shadowing      : " + file_name(qme()) + "\n"
	+ "-----------------------------------------------------\n"
	+ "Power          : " + query_power() + "\n"
	+ "Element        : " + query_element() + "\n"
	+ "Secondary elem : " + query_secondary_element() + "\n"
	+ "Previous spell : " + sprintf("%O\n", spell)
	+ "\n"
	+ "Reducible      : " + query_reducible() + "\n"
	+ "Duration       : " + query_duration() + "\n"
	+ "Time left      : " + query_time_left() + "\n"
	+ "Remove on disp : " + query_remove_on_dispel() + "\n"
	+ "\n";

    rest = qme()->stat_object();
    if (strlen(rest))
	return str + rest;
    else
	return str;
}
