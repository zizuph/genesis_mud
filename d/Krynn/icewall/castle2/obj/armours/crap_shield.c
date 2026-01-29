/* crap_shield.c is the poor reward item for slaying the Icewall yeti
   and laying the spirit of a dead Royal Guard of Sylvanos to rest.

   creator: Kessie
   final version: november 2001
*/

/*
 * Note by Navarre, November 22th 2005:
 *
 *
 * - This shield is not limited in numbers, it is cloned without clone_unique,
 *   since the unique shield is the silvanesti shield.
 *   For it always being here, the AC on it is a little high.
 *   I have changed the AC from 40 to 30, since it coveres the full body, 
 *   it is still a great armour.
 */

/* Navarre Feb 2007: Removed extra slots on shield.
                     It now only uses A_SHIELD + BODY
 */

/* Navarre June 2008: Reverting back changes to it uses A_SHIELD+Body+Legs (still no head).
 * and putting AC back to 40, since no one followed the shield changes we tried to do globally.
   The AC system was changed instead.
 */


#pragma strict_types

inherit "/std/armour";
inherit "/lib/keep";

#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <filter_funs.h>
#include <composite.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/castle2/local.h"
#include "/d/Krynn/icewall/local.h"

/*
    No idea why we have this function outside of create_armour.
    It causes bugs elsewhere in the game, so i've put it back.

    Arman 2017
*/ 


string
long_desc()
{
        return "A sturdy yet suprisingly light tower shield. Rectangular " +
           "in shape, with golden leaf designs running over its surface, " +
           "the shield must have been forged by elves and judging by the " +
           "smoothened edges, quite some time ago. Behind the leaves, " +
           "you can barely make out a faded symbol of a tall tower " +
           "standing in full sun.\n";
}


public void
create_armour()
{
    set_name("shield");
    set_pname("shields");
    set_adj("tower");
    add_adj("light");
    set_short("light tower shield");
    set_pshort("light tower shields");
    set_ac(40);
    set_at(A_SHIELD);
    set_am( ({0,0,0}) );
    set_long("A sturdy yet suprisingly light tower shield. Rectangular " +
           "in shape, with golden leaf designs running over its surface, " +
           "the shield must have been forged by elves and judging by the " +
           "smoothened edges, quite some time ago. Behind the leaves, " +
           "you can barely make out a faded symbol of a tall tower " +
           "standing in full sun.\n");
    add_prop(OBJ_I_VOLUME, 8500);
    add_prop(OBJ_I_WEIGHT, 8500);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(30));

    set_af(TO);
}

int*
query_shield_slots()
{
    return (::query_shield_slots() + ({ A_BODY, A_LEGS }) );
}