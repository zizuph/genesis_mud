/*
 * Spider web in which players can be trapped.  They will have to cut their
 * way out with something sharp (wielded!)
 */

inherit "/std/room";

#include <macros.h>
#include <language.h>
#include <formulas.h>
#include <stdproperties.h>

int hit_points;

/*
 * Function name: query_max_hp
 * Description:   Get the initial number of "hit points" the web has
 * Returns:       Max. hp
 */
int
query_max_hp()
{
    return 250;
}

/*
 * Function name: create_room
 * Description:   Initialize the spider web
 */
void
create_room()
{
    set_name("web");
    set_adj("sticky");
    set_short("@@short_desc@@");
    set_long("@@web_desc@@");

    add_prop(OBJ_M_NO_GET, 1);

    hit_points = query_max_hp();

    clone_object("/d/Rhovanion/hazelnut/webob")->move(this_object());
}

/*
 * Function name: short_desc
 * Description:   Give a short desc depending on wether we are inside
 *                or outside the web
 * Return:        The short desc as a string
 */
string
short_desc()
{
    if (environment(this_player()) == this_object())
	return "Inside sticky web";
    return "sticky web";
}

/*
 * Function name: web_desc
 * Desctription:  Give the long desc depending on wether we are inside
 *                or outside the web.  Perhaps it should include some-
 *                thing about monsters/players inside/outside the web?
 * Returns:       The long desc as a string
 */
string
web_desc()
{
    if (environment(this_player()) == this_object())
	return "Long desc of the web innards.\n";
    return "Long desc of the outside of the web.\n";
}

/*
 * Function name: init
 * Description:   Add commands specific to the web
 */
void
init()
{
    ::init();
    if (environment(this_player()) != this_object())
	add_action("do_cut", "cut");
}

/*
 * Function name: query_weapon
 * Description:   Return the weapon held in a specified location
 * Arguments:     which - the toolslot we want to know about
 * Returns:       The correcsponding weapon
 */
mixed
query_weapon(int which)
{
    return ({});
}

/*
 * Function name: query_the_name
 * Description:   Return the name of the web prefixed with 'the', used
 *                in combat routines.
 * Returns:       The name of the web prefixed with the word 'the'
 */
string
query_the_name()
{
    return "the sticky web";
}

string
query_pronoun()
{
    return "it";
}

string
query_objective()
{
    return "it";
}

string
query_possessive()
{
    return "its";
}

/*
 * Function name: hit_me
 * Description:   Called to make damage on this object. The actually made
 *                damage is returned and will be used to change the score
 *                of the aggressor.
 * Arguments:     wcpen     - The wc penetration
 *                dt        - The damage type
 *                attacker  - The object hurting us
 *                attack_id - Special id saying what hit us
 * Returns:       The hitresult as an array with the following elements:
 *                ({ percent damage, "hitloc name", hp damage, penetration })
 */
mixed *
hit_me(int wcpen, int dt, object attacker, int aid)
{
    int phit, phurt, dam;
    object ob;

    if (hit_points < 1 || (dt & W_SLASH) == 0)
	return ({ -1, "strand", -1, 0 });

    if (wcpen > 0) {
	phit = random(wcpen);

	/*
	 * Arguments to F_DAMAGE is the penetration of the attack
	 * and the AC of the hitloc being hit
	 */
	dam = F_DAMAGE(phit, 0) + 5;
	if (dam < 1)
	    dam = 0;
    }
    else {
	dam = 0;
	phit = (wcpen < 0 ? wcpen : -1);
    }
    if (dam > 0 && hit_points) {
	phurt = 100 * dam / hit_points;
	if (dam && !phurt)
	    phurt = 1;
    }
    else if (wcpen >= 0)
	phurt = 0;
    else
	phurt = -1;
    hit_points -= dam;
    return ({ phurt, "strand", phit, wcpen });
}

/*
 * Function name: query_hp
 * Description:   Return the current number of hit points of the object
 * Returns:       The current number of hit points
 */
int
query_hp()
{
    return hit_points;
}

/*
 * Function name: do_die
 * Description:   "Kill" the object when number of hit points are <0.
 *                Move all items contained in the object to the
 *                environment, then self-destruct
 * Arguments:     killer - The object that killed us
 */
void
do_die(object killer)
{
    object *obs;
    int i;

    if (hit_points > 0)
	return;
    tell_room(environment(), "The web starts to disintegrate.\n");
    tell_room(this_object(), "The web starts to disintegrate.\n");
    obs = all_inventory();
    for (i=0 ; i<sizeof(obs) ; i++) {
	if (!obs[i] || obs[i]->id("_inside_web_"))
	    continue;
	if (living(obs[i])) {
	    tell_room(environment(), QCTNAME(obs[i]) + " falls out of "+
		      "the web.\n");
	    obs[i]->catch_msg("You fall out of the web.\n");
	    catch(obs[i]->move_living("M", environment()));
	}
	else {
	    catch(obs[i]->move(environment()));
	    tell_room(environment(), capitalize(LANG_THESHORT(obs[i])) +
		      " falls out of the web.\n");
	}
    }
    remove_object();
}

/*
 * Function name: query_ghost
 * Description:   Called by the combat routines to see if the object has
 *                been "killed"
 * Returns:       1 - the object has been killed
 *                0 - the object is still "alive"
 */
int
query_ghost()
{
    if (hit_points <= 0)
	return 1;
    return 0;
}

/*
 * Function name: do_cut
 * Description:   Start cutting up the web.  Called when the player says
 *                'cut'.
 * Arguments:     arg - the rest of the command given
 * Returns:       0 - the command was not executed
 *                1 - the command was executed
 */
int
do_cut(string arg)
{
    notify_fail("Cut what?\n");
    if (!id(arg))
	return 0;
    if (environment(this_player()) != environment())
	return 0;
    write("You attack the web.\n");
    say(QCTNAME(this_player()) + " attacks the web.\n");
    this_player()->attack_object(this_object());
    return 1;
}
