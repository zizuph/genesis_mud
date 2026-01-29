/* Hits have increased over the years, and the Knights fall off their horses left and right.
   To compensate a little bit, I have added a random(2) == 0 to the check for if they fall
   off their horse when hit.
   -- Navarre August 26th 2006
*/

inherit "/d/Genesis/steed/new/rider_shadow";
inherit "/cmd/std/command_driver";

#include "/d/Krynn/common/defs.h"
#include "../guild.h"
#include <macros.h>
#include <formulas.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include <files.h>

object
armour_check()
{
    object *armours = shadow_who->query_armour(-1);
    object arm;

    if (!armours || sizeof(armours) <= 0)
    return 0;

    return armours[random(sizeof(armours) - 1)];
}

// Might fall off the horse when being hit
public varargs mixed
hit_me(int wcpen, int dt, object attacker, int attack_id, int target_hitloc = -1)
{
    object armour;
    int i, phurt;
    mixed *hitres;

    hitres = shadow_who->hit_me(wcpen, dt, attacker, attack_id);
    phurt = hitres[0];

    if (phurt >= 5 && (random(shadow_who->query_skill(SS_MOUNTED_COMBAT) * 3) < phurt) && (random(2)==0))
    {
        if (!random(10) && armour_check())
        {
            armour = armour_check();

            if ((armour->query_prop(OBJ_I_IS_MAGIC_ARMOUR) && !random(3)) ||
               (!armour->query_prop(OBJ_I_IS_MAGIC_ARMOUR) && !random(2)) ||
                 armour->query_condition() != 0)
            {
                shadow_who->catch_tell("\nAs you are struck, you fall heavily to the "+
               "ground and your "+armour->short()+" breaks!\n\n");
               tell_room(E(shadow_who), "As "+PRONOUN(shadow_who)+" is struck, "+
               PRONOUN(shadow_who)+" falls heavily to the ground, breaking "+
               POSSESSIVE(shadow_who)+" "+armour->short()+"!\n", shadow_who);
               armour->remove_broken(1);
               query_steed()->do_dismount(shadow_who, 1);
            }
            else
            {
                i = random(2) + 1;
                shadow_who->catch_tell("\nAs you are struck, you fall heavily to the "+
                "ground, damaging your "+armour->short()+".\n\n");
                tell_room(E(shadow_who), "As "+QTNAME(shadow_who)+" is struck, "+
                PRONOUN(shadow_who)+" falls heavily to the ground, damaging "+
                POSSESSIVE(shadow_who)+" "+armour->short()+".\n", shadow_who);
                armour->set_condition(i);
                query_steed()->do_dismount(shadow_who, 1);
            }
        }
        else
        {
            shadow_who->catch_tell("\nAs you are struck, you lose your balance "+
            "and fall from your "+query_steed()->steed_short()+".\n\n");
            tell_room(E(shadow_who), "As "+PRONOUN(shadow_who)+" is struck, "+
            QTNAME(shadow_who)+" loses "+POSSESSIVE(shadow_who)+" balance "+
            "and tumbles from "+POSSESSIVE(shadow_who)+" "+
            query_steed()->steed_short()+".\n", shadow_who);
            query_steed()->do_dismount(shadow_who, 1);
        }
    }
    return hitres;
}

int query_stat(int i)
{

    return shadow_who->query_stat(i);
}


/*
 * Function name:   attacked_by
 * Description:     This routine is called when we are attacked.
 *
 *                  This has been masked to prevent additional riders from
 *                  staying on in combat.
 *
 * Arguments:       (object) attacker - The attacking object
 * Returns:         Nothing
 */
public void
attacked_by(object attacker)
{
    if (objectp(query_steed()) && query_steed()->query_driver() != shadow_who)
        query_steed()->do_dismount(shadow_who, 1);
    
    shadow_who->attacked_by(attacker);
} /* attacked_by */

/*
 * Function name:   attack_object
 * Description:     Start attacking, the actual attack is done in heart_beat
 *
 *                  This has been masked to prevent additional riders from
 *                  staying on in combat.
 *
 * Arguments:       (object) ob - The object to attack
 * Returns:         Nothing
 */
public void
attack_object(object ob)
{
    if (objectp(query_steed()) && query_steed()->query_driver() != shadow_who)
        query_steed()->do_dismount(shadow_who, 1);
    
    shadow_who->attack_object(ob);
} /* attack_object */