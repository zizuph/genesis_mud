/*
  /std/combat/chumanoid.c

  This is the externalized combat routines for humanoids. 

  This combat object predefines a set of attacks and hitlocations 
  for humanoid living objects. It also keeps track of the total percentage
  of attacks that can be made each turn and distributes those percentages
  over the attacks depending on effectiveness of weapon wielded.

  The distribution formula is:

          %use = %maxuse * (wchit*wcpen) / ( sum(wchit*wcpen) )

  This formula is used if the 'set_attuse()' function is called and the
  value set to something different than 0. Otherwise the %use is left
  unaffected.

  This object is cloned and linked to a specific individual when
  engaged in combat. The actual object resides in 'limbo'.
*/

#pragma save_binary
#pragma strict_types

inherit "/std/combat/chumanoid";

#include <options.h>
#include <macros.h>

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
 *			 If this is negative, it indicates fail
 *		  dam:   Damage we did in hit points
 */

/* MODIFED VERSION OF THIS ****************/
/* Sarr Nightshade */

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
 
        if(i_am_real && !me->query_option(OPT_GAG_MISSES))
        {
            me->catch_msg("You aim for the " + hdesc + " of " +
                enemy->query_the_name(me) + " with your " + with +
                " but miss.\n");
        }
        if(interactive(enemy) && !enemy->query_option(OPT_GAG_MISSES))
        {
            enemy->catch_msg(me->query_The_name(enemy) + " aims for your " +
                hdesc + " with " + me->query_possessive() + " " + with +
                ", but misses.\n");
        }
        tell_watcher(QCTNAME(me) + " aims for the " + hdesc + " of " +
            QTNAME(enemy) + " with " + me->query_possessive() + " " +
            with + ", but misses.\n", enemy);
        return;
    }
 
    cb_add_panic(-3 - (phurt / 5));
    where = " the " + hdesc + " of ";
 
    switch (phurt)
    {

    case 0..4:
        how = ".\n";
        what = "scratch";
        owhat = "scratches";
        break;
    case 5..9:
        how = ".\n";
        what = "slice";
        owhat = "slices";
        break;
    case 10..19:
        how = ".\n";
        what = "tear into";
        owhat = "tears into";
        break;
    case 20..29:
        how = ", rather bad.\n";
        what = "tear into";
        owhat = "tears into";
        break;
    case 30..49:
        how = ", very bad.\n";
        what = "tear into";
        owhat = "tears into";
        break;
    case 50..69:
        how = ", extremly bad.\n";
        what = "rip into";
        owhat = "rips into";
        break;
    case 70..89:
        how = ", shreding flesh and smashing bone.\n";
        what = "rip into";
        owhat = "rips into";
        where = " ";
        break;
    default:
        how = ", spraying blood everywhere.\n";
        what = "savage";
        owhat = "savages";
        where = " ";
    }
 
    if (i_am_real)
    {
        me->catch_msg("You " + what + where + enemy->query_the_name(me) +
            " with your " + with + how);
    }
    if (interactive(enemy))
    {
        enemy->catch_msg(QCTNAME(me) + " " + owhat + " your " + hdesc +
            " with " + me->query_possessive() + " " + with + how);
    }
    tell_watcher(QCTNAME(me) + " " + owhat + where + QTNAME(enemy) +
        " with " + me->query_possessive() + " " + with + how, enemy);
}


