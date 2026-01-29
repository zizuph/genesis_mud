#include "defs.h"
#include <wa_types.h>
#include "/d/Immortal/rogon/open/parse.h"

inherit "/std/weapon";
// inherit IM_MESSAGE_FILE;

/*
 * Function name:    get_hitloc_id
 * Arguments:        string hdesc   hitlocation description.
 *                   object who     who's description.
 * Returns:          The probable id of the hitloc id.
 */
int
get_hitloc_id(string hdesc, object who)
{
    int i, found, *hitloc_id;
    object co;
    mixed hitloc;

    co = who->query_combat_object();
  
    hitloc_id = co->query_hitloc_id();
    for (i=0; i<sizeof(hitloc_id); i++)
    {
        hitloc = co->query_hitloc(hitloc_id[i]);
        if (hitloc[2] == hdesc)
            return hitloc_id[i];
    }
    return -1;
}

/*
 * Function name:    get_hitloc_data
 * Arguments:        string hdesc   hitlocation description.
 *                   object who     who's description.
 * Returns:          An array of the form:
 *                   ({ ac[3]    [total armour class here
 *                                (impale/slash/bludgeon)],
 *                      %hit     [chance of hit here],
 *                      desc     [hitloc desc],
 *                      m_ac[3]  [modified armour class]
 *                      hid      [hitloc id] })
 */
mixed
get_hitloc_data(string hdesc, object who)
{
    int id = get_hitloc_id(hdesc, who);        
    return who->query_combat_object()->query_hitloc(id)+({ id });
}

/*
 * Function name:    get_armours_protecting
 * Arguments:        string hdesc   hitlocation description.
 *                   object who     who's description.
 * Returns:          An array which contains possible armours
 *                   (and weapons?) protecting the area.
 */
object *
get_armours_protecting(string hdesc, object who)
{
    int id = get_hitloc_id(hdesc, who);
    return who->query_combat_object()->query_armour(id);
}

int
query_extra_dam(int aid, string hdesc, int phurt, object enemy, int dt)
{
    return 0;
}

/*
public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    int extra_dam;
    int told;

    if (phurt > 0)
    {
        extra_dam = query_extra_dam(aid, hdesc, phurt, enemy, dt);
    }
    else
    {
        extra_dam = 0;
    }

    LIMIT(extra_dam, 0, 100);

    if (extra_dam > 0)
    {    
        phit += extra_dam / MAX_HP(enemy);    
        phurt += extra_dam * 100 / MAX_HP(enemy);
        dam += extra_dam;
        enemy->heal_hp(-extra_dam);
    }
 
    told = message(ENV(TO), enemy, dt, hdesc, phurt, TO);

    if (HP(enemy) <= 0)
    {
        enemy->do_die(wielder);
	return told;
    }

    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);      

    return told;
}
*/
    

#if 0
/** -------------------------------------------- **
 **         Part for a better "wielding"         **
 ** -------------------------------------------- **/

init()
{
    ::init();
    add_action("do_wield", "wield");
    // add_action("do_unwield", "unwield");
}

public int
do_wield(string arg)
{
    object *a, *normal, *mine;
    mixed env;
    string hand;

    notify_fail(CAP(query_verb()) + " what?\n");

    gFail = "";

    env = objectp(ETP) ? ETP : TP;
	
    if (!parse_command(arg, env, "%i 'in' [my] [the] %w 'hand' / 'hands'", a, hand) &&
	!parse_command(arg, env, "%i %w", a, hand) &&
	!parse_command(arg, env, "%i", a)) 
    {
	return 0;
    }
    else {
	write("hand = " + hand + "\n");
	a = VIS_ACCESS(a, "wield_access", 1, 0);
	mine = filter(a, "wield_one_weapon", TO, hand);
	a -= mine;
	normal = filter(a, "wield_me", TO);

	if (sizeof(mine) + sizeof(normal) == 0) {
	    if (!strlen(gFail))
		return 0;
	    else
		write(gFail);
	}
	gFail = 0;
	
	return 1;
    }
}

int
wield_one_weapon(object what, string hand)
{
    string fail;

    write("In wield_one_weapon.\n");
    if (what != TO) {
	if (function_exists("wield_this_weapon", what))
	    fail = what->wield_this_weapon();
	else
	    fail = what->wield_me();
    }
    else 
	fail = TO->wield_this_weapon(hand);

    if (stringp(fail)) {
	gFail += fail;
	return 0;
    } else
	return 1;
}

mixed
wield_this_weapon(string what)
{
    string hand;

    if (stringp(what)) {
	if (sscanf(what, "%shanded", hand) != 1)
	    hand = what;

	if (hand=="two-" || hand=="two " || hand=="2-" || 
	    hand=="both" || hand=="two")
	    wep_hands = W_BOTH;
	else if (hand=="left" || hand=="left-")
	    wep_hands = W_LEFT;
	else if (hand=="right" || hand=="right-")
	    wep_hands = W_RIGHT;
	else
	    wep_hands = W_ANYH;
    } 
    return wield_me();
}

#endif
