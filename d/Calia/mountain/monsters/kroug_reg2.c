/* Regular kroug.
   This particular one wields two red gladiuses.

   Coded by Maniac.

   History:
          20/2/95        modified          Maniac
          11/8/95        Created           Maniac
*/

#pragma save_binary

inherit "/d/Calia/std/kroug";

#include "/d/Calia/sys/kroug.h"
#include <money.h>
#include "monster.h"

void
arm_me()
{
   object heap;
   object weapon;
   object armour;

    heap = MONEY_MAKE_GC(2);
    heap->move(this_object());

    armour = clone_object(MOUNTAIN_ARMOURS + "copper_ringmail");
    armour->move(this_object());

    armour = clone_object(MOUNTAIN_ARMOURS + "short_curve_helm");
    armour->move(this_object());
    command("wear all");

    weapon = clone_object(MOUNTAIN_WEAPONS + "red_gladius");
    weapon->move(this_object()); 
    command("wield gladius");

    weapon = clone_object(MOUNTAIN_WEAPONS + "red_gladius");
    weapon->move(this_object()); 
    command("wield gladius");
}


/* Short and sweet :) */
void
create_kroug()
{
    set_kroug_type(KROUG_REGULAR);
}
