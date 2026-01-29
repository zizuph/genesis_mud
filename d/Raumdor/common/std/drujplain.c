/*
  /std/combat/cplain.c

  This is the externalized combat routines for simple creatures that
  can not use tools for aid in combat.

  This object is cloned and linked to a specific individual when
  engaged in combat. The actual object resides in 'limbo'.

  This simplistic creature combat object does not handle objects used
  as weapons or armours, only intrinsic combat capabilities.

*/
#pragma save_binary

inherit "/std/combat/cbase";
#include "/d/Raumdor/defs.h"
/*
* Function name: create_cbase
* Description:   Reset the combat functions
*/
public nomask void
create_cbase()
{
    if (qme())
	return;
    this_object()->create_cplain();

}

/*
 * Function name: cb_configure
 * Description:   Configure nonhumanoid attacks and hitlocations.
 */
public void
cb_configure() { qme()->cr_configure(); }

/******************************************************************
 *
 * These functions should be accessible from 'me'
 * 
 */

/*
 * Function name: cb_add_attack
 * Description:   Add an attack to the attack array.
 * Arguments:	  
 *             wchit: Weapon class to hit
 *             wcpen: Weapon class penetration
 *	       dt:    Damage type
 *             %use:  Chance of use each turn
 *	       id:    Specific id, for humanoids W_NONE, W_RIGHT etc
 *	       skill: Skill to use
 *
 * Returns:       True if added.
 */
public int
cb_add_attack(int wchit, mixed wcpen, int damtype, int prcuse,
    int id, int skill)
{
    return ::add_attack(wchit, wcpen, damtype, prcuse, id, skill);
}

/*
 * Function name: cb_remove_attack
 * Description:   Removes a specific attack
 * Arguments:     id: The attack id
 * Returns:       True if removed
 */
public int
cb_remove_attack(int id) { return ::remove_attack(id); }

/*
 * Function name: cb_add_hitloc
 * Description:   Add a hitlocation to the hitloc array
 * Arguments:	  
 *	      ac:    The ac's for a given hitlocation
 *	      %hit:  The chance that a hit will hit this location
 *	      desc:  String describing this hitlocation, ie "head", "tail"
 *	      id:    Specific id, for humanoids A_TORSO, A_HEAD etc
 *
 * Returns:       True if added.
 */
public int
cb_add_hitloc(int *ac, int prchit, string desc, int id)
{
    return ::add_hitloc(ac, prchit, desc, id);
}

/*
 * Function name: cb_remove_hitloc
 * Description:   Removes a specific hit location
 * Arguments:     id: The hitloc id
 * Returns:       True if removed
 */
public int
cb_remove_hitloc(int id) { return ::remove_hitloc(id); }


/******************************************************************
 *
 * These functions are called from the central combat routines in
 * xcombat. Here they are linked to corresponding cr_ routines in the
 * mobile object.
 */

/*
 * Function name: cb_try_hit
 * Description:   Decide if a certain attack fails because of something
 *                related to the attack itself, ie specific weapon that only
 *		  works some of the time. 
 * Arguments:     aid:   The attack id
 * Returns:       True if hit, otherwise 0.
 */
public int
cb_try_hit(int aid)
{
    return (int)qme()->cr_try_hit(aid);
}

/*
 * Function name: cb_got_hit
 * Description:   Tells us that we got hit. It can be used to reduce the ac
 *                for a given hitlocation for each hit. This is supposed to be
 *                replaced by a more intelligent routine in creature and
 *                humanoid combat. (called from cb_hit_me)
 * Arguments:     hid:   The hitloc id
 *                ph:    The %hurt
 *                att:   Attacker
 *		  aid:   The attack id
 *                dt:    The damagetype
 *	 	  dam:	 The damage in hit points
 */
public varargs void
cb_got_hit(int hid, int ph, object att, int aid, int dt, int dam) 
{
    qme()->cr_got_hit(hid, ph, att, aid, dt, dam);
}

/*
 * Function name: cb_attack_desc
 * Description:   Gives the description of a certain attack slot.
 * Arguments:     aid:   The attack id
 * Returns:       string holding description
 */
public string
cb_attack_desc(int aid)
{
    string desc;

    if (desc = qme()->cr_attack_desc(aid))
	return desc;
    else
	return "body";
}

/*
 * Function name: cb_did_hit
 * Description:   Tells us that we hit something. Should produce combat
 *                messages to all relevant parties. This is supposed to be
 *                replaced by a more intelligent routine in creature and
 *                humanoid combat. (called from heart_beat)
 * Arguments:     aid:   The attack id
 *                hdesc: The hitlocation description.
 *                phurt: The %hurt made on the enemy
 *                enemy: The enemy who got hit
 *		  dt:	 The current damagetype
 *		  phit:  The %success that we made with our weapon
 *		  dam:	 The damamge made in hitpoints
 */
public varargs void
cb_did_hit(int aid, string hdesc, int hid, int phurt, object enemy, int dt,
           int phit, int dam)
{
    string how;
    string what;
    string owhat;
    string with;
    string where;
 
    if ((!objectp(enemy)) || (!objectp(me)))
    {
        return;
    }
 
    with = cb_attack_desc(aid);
 
    if (phurt == -1 || phurt == -2)
    {
        cb_add_panic(1);
 
        if (i_am_real)
        {
            me->catch_msg("You aim for the " + hdesc + " of " +
                enemy->query_the_name(me) + " with your " + with +
                " but miss.\n");
        }
        if (interactive(enemy))
        {
            enemy->catch_msg(me->query_The_name(enemy) + " flies at you "+
            "with its claws extended, but you dodge in time, and it "+
            "barely misses your "+hdesc+".\n");
        }
        tell_watcher(QCTNAME(me) + " flies at "+QTNAME(enemy)+" with its "+
        "claws extended, but "+enemy->query_pronoun()+" dodges in time, "+
        "and it barely misses "+enemy->query_possessive()+" "+
        hdesc+".\n",enemy);
        return;
    }
 
    cb_add_panic(-3 - (phurt / 5));
    where = " the " + hdesc + " of ";
 
    switch (phurt)
    {

    case 0..4:
    if (i_am_real)
    {
        me->catch_msg("You " + what + where + enemy->query_the_name(me) +
            " with your " + with + how);
    }
    if (interactive(enemy))
    {
        enemy->catch_msg(QCTNAME(me)+" flies at you and lightly scratches "+
        "your "+hdesc+" with its sharp claws.\n");
    }
    tell_watcher(QCTNAME(me) + " flies at "+QCTNAME(enemy)+" and lightly "+
        "scratches "+enemy->query_possessive()+" "+hdesc+" with its sharp "+
        "claws.\n",enemy);
        break;
    case 5..9:
    if (i_am_real)
    {
        me->catch_msg("You " + what + where + enemy->query_the_name(me) +
            " with your " + with + how);
    }
    if (interactive(enemy))
    {
        enemy->catch_msg(QCTNAME(me)+" flies at you and stings "+
        "your "+hdesc+" with its sharp claws.\n");
    }
    tell_watcher(QCTNAME(me) + " flies at "+QCTNAME(enemy)+" and stings "+
       enemy->query_possessive()+" "+hdesc+" with its sharp claws.\n",enemy);
        break;
    case 10..19:
    if (i_am_real)
    {
        me->catch_msg("You " + what + where + enemy->query_the_name(me) +
            " with your " + with + how);
    }
    if (interactive(enemy))
    {
        enemy->catch_msg(QCTNAME(me)+" hooks underneath you and tears "+
        "into your "+hdesc+" with its deadly claws.\n");
    }
    tell_watcher(QCTNAME(me) + " hooks underneath "+QCTNAME(enemy)+" and "+
        "tears into "+enemy->query_possessive()+" "+hdesc+" with its deadly "+
        "claws.\n",enemy);
        break;
    case 20..29:
    if (i_am_real)
    {
        me->catch_msg("You " + what + where + enemy->query_the_name(me) +
            " with your " + with + how);
    }
    if (interactive(enemy))
    {
        enemy->catch_msg(QCTNAME(me)+" flies over your head, then dives "+
        "down onto your "+hdesc+", tearing into your flesh.\n");
    }
    tell_watcher(QCTNAME(me) + " flies over "+QCTNAME(enemy)+"'s head, then "+
        "dives down onto "+enemy->query_possessive()+" "+hdesc+", tearing "+
        enemy->query_possessive()+" flesh.\n",enemy);
        break;
    case 30..49:
    if (i_am_real)
    {
        me->catch_msg("You " + what + where + enemy->query_the_name(me) +
            " with your " + with + how);
    }
    if (interactive(enemy))
    {
        enemy->catch_msg(QCTNAME(me)+" flies over your head, then dives "+
        "down onto your "+hdesc+", ripping hard into your flesh.\n");
    }
    tell_watcher(QCTNAME(me) + " flies over "+QCTNAME(enemy)+"'s head, then "+
        "dives down onto "+enemy->query_possessive()+" "+hdesc+", ripping "+
        "hard into "+enemy->query_possessive()+" flesh.\n",enemy);
        break;
    case 50..69:
    if (i_am_real)
    {
        me->catch_msg("You " + what + where + enemy->query_the_name(me) +
            " with your " + with + how);
    }
    if (interactive(enemy))
    {
        enemy->catch_msg(QCTNAME(me)+" arches around your side, then drills "+
        "HARD into your "+hdesc+", shredding flesh with its sharp claws.\n");
    }
    tell_watcher(QCTNAME(me) + " arches around "+QCTNAME(enemy)+"'s side, "+ 
    "then drills HARD into "+enemy->query_possessive()+" "+hdesc+", shredding "+
    "flesh with its sharp claws.\n",enemy);
        break;
    case 70..89:
    if (i_am_real)
    {
        me->catch_msg("You " + what + where + enemy->query_the_name(me) +
            " with your " + with + how);
    }
    if (interactive(enemy))
    {
        enemy->catch_msg(QCTNAME(me)+" swoops down and drills dead center "+
        "into your "+hdesc+", splattering your blood around and making you " +
        "feel the true meaning of agony!\n");
    }
    tell_watcher(QCTNAME(me) + " swoops down and drills dead center into "+ 
    QCTNAME(enemy)+"'s "+hdesc+", and "+enemy->query_pronoun()+" now looks "+
    "like "+enemy->query_pronoun()+" knows the true meaning of agony!\n",
    enemy);
    enemy->command("scream");    
        break;
    default:
    if (i_am_real)
    {
        me->catch_msg("You " + what + where + enemy->query_the_name(me) +
            " with your " + with + how);
    }
    if (interactive(enemy))
    {
        enemy->catch_msg(QCTNAME(me)+" swoops down and totally devastates "+
        "your "+hdesc+", nearly cutting it off. If your not dead now, you "+
        "will be soon.\n");
    }
    tell_watcher(QCTNAME(me) + " swoops down and totally devastates "+ 
    QCTNAME(enemy)+"'s "+hdesc+", nearly cutting it off. If "+
    enemy->query_pronoun()+" is not dead now, "+enemy->query_pronoun()+
    " will be soon.\n",enemy);
    }
}

