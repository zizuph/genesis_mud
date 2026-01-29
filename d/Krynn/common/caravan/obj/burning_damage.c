/*
 *      /w/vencar/caravan/obj/burning_damage.c
 *
 *      The damage calculation of burning
 *      Created by Vencar 09/09/2003
 *
 *      Copyright by Peter Bech Lund (Vencar)
 *      09/2003
 *
 *  Based on Lightning.c (the lightning clouds
 *  found in Krynn.
 */

#pragma strict_types

inherit "/std/object";

#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

/*
 * Function name:  hurt_player
 * Description:    Does fire damage to a player where strength
 *                 is the hit points damage that are maximum,
 *
 *                 The higher maximum the less chance of getting
 *                 no damage. Damage of 20 or less will hardly ever
 *                 give any damage.
 *
 *                 Will reduce damage percentwise depending on the
 *                 fire resistance of the player, and also increase
 *                 the chance that there will be no fire damage at all
 *                 with ,9 % pr percent fire resistance.
 * Returns:        nothing
 */

#include "../wagon/wagon.h"

int
hurt_player(object player, int strength)
{
    int res, dam;
    object co;
    string str;

    dam = strength;

    /* Don't want the damage to be too 'even' so we make it
       slightly different from its original value
       +/- 30 percent */

    if (random(100) < 50)
        dam = dam * (100 - random(30)) / 100;
    else
        dam = dam * (100 + random(30)) / 100;;

    /* A chance that this time he wont take any damage */
    if (random(dam) < 20 )
        return 0;

    /* Fire resistance helps */
    res = player->query_magic_res(MAGIC_I_RES_FIRE);
    res = min(res, 100);
    if (res > random(110))
        return 0;

    dam -= dam * res / 100;

    /* Hurt it! */
    player->heal_hp(-dam);

    if (dam > 0)
    {
        switch (dam)
        {
        case 0..20:
            str = "a little ";
            break;
        case 21..50:
            str = "partly ";
            break;
        case 51..100:
            str = "badly ";
            break;
        default:
            str = "very badly ";
            break;
        }

        tell_object(player,"You are " + str + "burnt from the flames.\n");
    }

    tell_room(E(player), QCTNAME(player) + " is engulfed in " +
        "the flames.\n", player);

    if (!player->query_ghost() && player->query_hp() <= 0)
    {
        player->do_die(TO);
        return 0;
    }

    return dam;
}

