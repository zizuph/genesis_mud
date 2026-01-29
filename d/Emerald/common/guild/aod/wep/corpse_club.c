/*
 * corpse_club.c
 *
 * If you have a hammer, the world looks like a nail. If you are an ogre
 * everything looks like a club.
 */

#pragma strict_types

inherit "/std/weapon";

#include "../defs.h"
#include <stdproperties.h>
#include <wa_types.h>

/* Global variables. */
int    Gdecay_left;
object Gcorpse;

/*
 * Function name: create_weapon
 * Description  : Constructor. Called to create this weapon. Note that we need
 *                a corpse to become fully operational.
 */
void
create_weapon()
{
    set_name("club");
    add_name(AOD_CORPSE_WEAPON_ID);
    set_pname("clubs");
    set_adj("corpse");
    add_adj("remains");
    add_adj("of");
    set_short("nondescript club");
    set_pshort("nondescript clubs");
    set_long("Ce n'est pas un club.\nIt will be once a corpse has been weaponised.\n");

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_SELL, "A proper burial might be in order instead.\n");

    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_BOTH);
    set_may_not_recover();

    /* These are necessary to make us look like a container. */
    add_prop(CONT_I_REDUCE_WEIGHT, 100);
    add_prop(CONT_I_REDUCE_VOLUME, 100);
}

/*
 * Function name: weaponise_corpse
 * Description  : This routine will take a corpse and turn this weapon into a
 *                club that matches the descriptions of the corpse.
 * Arguments    : object corpse - the corpse to model this weapon after.
 */
void
weaponise_corpse(object corpse)
{
    int volume, weight;

    Gcorpse = corpse;
    /* We hide the corpse inside this object. */
    Gcorpse->move(this_object(), 1);

    /* Stop the decay of the corpse for the duration of hostilities. We round
     * it to whole minutes for the purpose of restarting it later. */
    Gdecay_left = ((Gcorpse->query_decay_left() + 30) / 60);
    Gcorpse->set_decay(0);

    /* Link various properties of the weapon to the corpse. */
    set_short(&Gcorpse->short());
    set_pshort(&Gcorpse->plural_short());
    set_long(&Gcorpse->long());
    set_name(Gcorpse->query_name());
    add_name(Gcorpse->query_prop(CORPSE_S_RACE));
    
    add_prop(OBJ_I_VOLUME, Gcorpse->query_prop_setting(OBJ_I_VOLUME));
    add_prop(OBJ_I_WEIGHT, Gcorpse->query_prop_setting(OBJ_I_WEIGHT));

    /* Weapon class is loosely dependent on the corpse properties. A small
     * corpse is easier to hit with, but a heavy corpse does more damage. */
    volume = min(200, (query_prop(OBJ_I_VOLUME) / 1000));
    weight = min(200, (query_prop(OBJ_I_WEIGHT) / 1000));
    set_hit(15 + random(10) - (volume / 20));
    set_pen(10 + random(10) + (weight / 10));
}

/*
 * Function name: long
 * Description  : Masking the long() isn't totally necessary, but it helps
 *                to prevent the "condition" messages associated with weapons.
 * Arguments    : see long in /std/object.c
 * Returns      : string - the long description.
 */
string
long(string item, object for_obj)
{
    if (Gcorpse)
    {
        return Gcorpse->long(item, for_obj);
    }
    else
    {
        ::long(item, for_obj);
    }
}

/*
 * Function name: enter_env
 * Descriptioon : After the fun it is time to let the corpse go and continue
 *                to decay.
 * Arguments    : object to - where we go to.
 *                object from - where we come from.
 */
void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    
//  if (!IS_OGRE(to))
    if (to->query_prop(ROOM_I_IS))
    {
        Gcorpse->move(to, 1);
        /* Restart the decay. */
        Gcorpse->set_decay(Gdecay_left);
        /* The alarm is needed in case of dropping the corpse. */
        set_alarm(0.0, 0.0, remove_object);
    }
}
