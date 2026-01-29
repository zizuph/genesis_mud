/*
 * /d/Sparkle/area/jade/obj/jade_pear.c
 *
 * Sparkle herbs (Jade Forest) - inedible, throwable_item
 * On impact, does damage and releases fumes; basically an alcohol grenade.
 *
 * Created 2017-02-03 by Martin Berka (Mar) for Genesis MUD
 */

#pragma strict_types
inherit "/std/herb";
inherit "/d/Sparkle/area/jade/obj/throwable_item";

#include <herb.h>
#include <macros.h>
#include <math.h>
#include <ss_types.h> //Skills
#include <tasks.h>


/* Global variables */
int stored_align,
    time_created;

//public void        create_herb();

/*
 * Function name:        create_herb
 * Description  :        the constructor for the herb object
 */
public void
create_herb()
{
    set_name("fruit");
    add_name( ({ "fruit", "pear", "jade pear" }) );
    add_pname("pears");
    set_adj( ({"hard", "green"}) );
    set_herb_name("jade pear");
    set_short("hard green fruit");
    set_ingest_verb("eat");
    set_effect(HERB_SPECIAL, "", 50);
    set_unid_long("The smooth, rock-hard surface of this oblong fruit is a "
        + "deep, rich green.\n");
    set_id_long("The jade pear is named for the rock that it resembles in both "
        + "colour and texture. It owes both to the rocky, metallic soil "
        + "preferred by the jade peartree: abnormally high amounts of minerals "
        + "accumulate in the pear's skin. The delicate seeds are thus well "
        + "protected from animals and may wait decades for an impact to "
        + "release them (presumably onto rocky terrain). The pear's high metal "
        + "content makes it toxic to any who can even bite into it. "
        + "Some use it as a decoration or missile, at their own risk: the "
        + "seeds are preserved by the pear's long-fermented flesh, which "
        + "escapes as mind-numbing fumes when the pear breaks.\n");

    set_amount(1); // Stone shell surrounding alcohol - just the seeds
    set_id_diff(25); // Obvious appearance, but the facts require knowledge.
    set_find_diff(4);
    set_herb_value(400);
    add_prop(OBJ_I_VOLUME, 180);
    //Normal pear would float (V>W), but this one is 80% alcohol and 20% jade.
    add_prop(OBJ_I_WEIGHT, 260); //Usual pear is 150-180

    time_created = time();
} /* create_herb */


/*
 * Function     : aim_at_living
 * Description  : Overriding the throwable-item aim procedure to make it
 *      easy to pear Family NPC's in the Runaway quest.
 * Arguments    : (object) Pear thrower - must be player for special effect
 *                (object) Pear target - must be Family NPC ' '
 * Returns      : (int) 0 if kidnap procedure is launched, otherwise the
 *          1/0 result of the regular throw procedure
 */
int
aim_at_living(object thrower, object target)
{
    if (!thrower->query_npc() && function_exists("kidnap_pear", target))
    {
        if (target->kidnap_pear( this_object() ))
        {
            //Diverts to family.c NPC functions
            return 0;
        }
    }

    return ::aim_at_living(thrower, target);
}


/*
 * Function:    query_recover
 * Description: You recover (this herb)
 * Returns:     The recovery string
 */
string
query_recover()
{
    return MASTER + ":" ;//+ query_herb_recover();
} /* query_recover */

/*
 * Function:    init_recover
 * Description: Launch herb-recovery function
 */
void
init_recover(string arg)
{
   // init_herb_recover(arg);
} /* init_recover */

/*Smash/smack/hit/bash/break/whack/kick:
    breaker gets main dose, everyone else gets half as much

Smash/smack/hit/bash/whack __ with pear:
    receiver takes damage (strength-based) and gets full dose, holder gets 3/4,
    others get half.

Throw/fling at - receiver takes damage and full dose, others get half

Full dose comes with triple the mental awareness penalty for all others. Good
against mages?
Double dose if indoors.

*/


/*
 * Function name: ingest_access
 * Description  : Determine whether we can ingest this herb. Redefine this if
 *                you only want it to trigger on the special ingest verb.
 * Returns      : see command_eat()
 */
public mixed
ingest_access()
{
    if (this_player()->resolve_task(TASK_ROUTINE, SS_STR))
    {
        this_player()->add_fatigue(-5);
        return 1;
    }
    return 0;
}


/*
 * Function name: impact_effect
 * Description  : Override throwable_item: intoxicate all objects in the room,
 *          the nearest twice as much and with light damage.
 * Arguments    : (object) nearest object to the place where Missile stops.
 * Returns      : (int) 1 if effect occurred, 0 if blocked by some condition
 */
varargs int
impact_effect(object nearest)
{
    //Set potency based on age:
    int time_factor = ftoi(log( itof(time() - time_created + 100) ));

    tell_room(environment(this_player()), "The hard green fruit shatters, "
        + "releasing an intoxicating cloud.\n");

    //Nearest somehow missing? Player is next in line.
    if (!environment(nearest))
    {
        nearest = Thrower;
    }

    foreach(object liv : filter(all_inventory( environment(nearest) ), living))
    {
        liv->set_intoxicated(liv->query_intoxicated() + time_factor);
    }

    if (living(nearest))
    {
        int new_hp = nearest->query_hp() - 50;
        if (new_hp < 1)
        {
            new_hp = 1;
        }
        nearest->set_hp(new_hp);
        nearest->catch_msg("You are hurt by rock-hard shards!");
        nearest->set_intoxicated(nearest->query_intoxicated() + time_factor);
        //Nearest gets double the effect
    }
    else if (file_name(nearest) == file_name( this_object() )) //Hitting another pear
    {
        //Cause targeted pear to explode near Thrower
        nearest->impact_effect(Thrower);
    }

    if (calling_function() != "special_effect") //(then herb.c handles removal).
    {
        query_missile()->remove_object();
    }
    return 1;
}

/*
 * Function     : special_effect
 * Description  : Effect of eating the pear - shatter if strong enough to
 *      break through.
 */
public void
special_effect()
{
    impact_effect(this_player());
}


/*The following initialization, leave_env, and appraise functions are only here
to ensure that that throwable_item's versions are called. Headers are there.*/
void init()
{
    ::init();
    init_throwable();
}

void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    leave_env_throwable(from, to);
}

void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_throwable(num);
}
