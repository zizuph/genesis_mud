/*
 * chain.c
 *
 * This chain is used the imprison Firestorm, the dragon that must
 * be freed for the Calian Sup. Guru Quest. To do so requires breaking
 * this chain, which is accomplished by crushing it with the King's
 * Hand. The hand is a gauntlet players must find and have charged,
 * the bring ehre to break the chain. This required multiple players,
 * as the gauntlet can only be used once per player, and it can never
 * be broken in one attempt.
 *
 * In order to encourage calians to do this with just calians, they
 * do more 'damage' to the chain than non-calians will.
 *
 * Khail, Feb 8/96
 */
#pragma strict_types

#include "defs.h"
#include "../guru_quest.h"

inherit "/std/object";

int damage;
object dragon;
object *damagers;

/*
 * Function name: check_broken
 * Description  : Delivers an extra vbfc string for the long desc
 *                based on damage sustained.
 * Arguments    : n/a
 * Returns      : A string with the appropriate damage desc.
 */
public string
check_broken()
{
    switch(damage)
    {
        case 0:
            return "";
            break;
        case 1..25:
            return "The chain looks to have suffered a little " +
                "damage.";
            break;
        case 26..50:
            return "The chain has suffered some minor damage.";
            break;
        case 51..75:
            return "The chain has taken a considerable amount of " +
                "abuse.";
            break;
        case 76..100:
            return "The chain looks like it's about to shatter " +
                "completely.";
            break;
        default:
            return "The chain has amazingly enough been shattered!";
    }
}

/*
 * Function name: create_object
 * Description  : Turns this object into a chain. Also makes it
 *                set_no_show_composite, so while it can be
 *                examined, etc. it does not appear in the room's
 *                long description.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_object()
{
    set_name("chain");
    add_name(C_GURU_CHAIN_NAME);
    add_name("chains");
    set_adj("massive");
    add_adj("iron");
    set_long("The chain is massive, each link about as thick " +
        "as your arm. Whoever designed it intended that whatever " +
        "it was attached to stayed in place. @@check_broken@@\n");

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 2000000);
    add_prop(OBJ_I_VOLUME, 200000);
    add_prop(OBJ_M_NO_GET, "That's completely impossible, it's " +
        "too heavy, not to mention anchored to the floor.\n");

    set_no_show_composite(1);

    damagers = ({});
}

/*
 * Function mame: set_damage
 * Description  : Sets the damage variable.
 * Arguments    : i - The new damage level. 0 - fine, 101+ - Broken.
 * Returns      : n/a
 */
public void
set_damage(int i)
{
    damage = i;
}

/*
 * Function name: query_damage
 * Description  : Queries the current damage.
 * Arguments    : n/a
 * Returns      : A integer indicating current damage.
 */
public int
query_damage()
{
    return damage;
}

/*
 * Function name: set_dragon
 * Description  : Tells the chain what dragon it's holding.
 * Arguments    : ob - Object pointer to the dragon.
 * Returns      : n/a
 */ 
public void
set_dragon(object ob)
{
    dragon = ob;
}

/*
 * Function name: query_dragon
 * Description  : Queries the current dragon.
 * Arguments    : n/a
 * Returns      : Object pointer to the dragon linked to this chain.
 */
public object
query_dragon()
{
    return dragon;
}

/*
 * Function name: try_break
 * Description  : Lets players try to break the chain. Damage range
 *                per attempt is 50 + random(10) for a calian,
 *                35 + random(10) for a non-calian. Also breaks
 *                the chain and ends the quest if the damage done
 *                exceeds 100.
 * Arguments    : who - Object pointer to the player trying to 
 *                      break the chain.
 * Returns      : n/a
 */
public void
try_break(object who)
{
    int dam;

  /* Do nothing if the chain is already broken. */
    if (damage > 100 ||
        (dragon && dragon->query_prop(DRAGON_S_WAS_RELEASED)))
    {
        tell_object(who, "The chain is already broken!\n");
        return;
    }

 /* Calculate damage. Add 15 damage points if this is a calian. */
 /* The point here is to make it easier for calians to help */
 /* than for non-calians to help. */ 
    dam = 35 + random(10);
    if (TP->query_guild_name_occ() == C_GURU_GUILD_NAME)
        dam += 15;

  /* Generate a damage message. */
    switch(dam)
    {
        case 35..45:
            tell_object(who, "The chain suffered only a little " +
                "damage.\n");
            break;
        case 46..55:
            tell_object(who, "The chain suffered some notable " +
                "damage.\n");
            break;
        default:
            tell_object(who, "The chain suffered a lot of damage.\n");
    }

    damagers += ({who});

  /* Add the new damage to the old, if it's more than 100, break */
  /* the chain and reward the players. */
    damage += dam;
    if (damage > 100)
    {
        tell_room(environment(who), "The chain has broken! " +
            "Firestorm is Free!\n");            
        dragon->react_freedom(who, TO);
    }
}

public object *
query_damagers()
{
    return damagers + ({});
}
