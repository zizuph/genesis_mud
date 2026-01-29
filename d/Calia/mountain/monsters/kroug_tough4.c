
/* Tough kroug.
   This particular one wields a massive mace.

   Coded by Maniac.

   History:

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

    heap = MONEY_MAKE_GC(4);
    heap->move(this_object());

    armour = clone_object(MOUNTAIN_ARMOURS + "gold_scalemail");
    armour->move(this_object());

    armour = clone_object(MOUNTAIN_ARMOURS + "long_straight_helm");
    armour->move(this_object());
    command("wear all");

    weapon = clone_object(MOUNTAIN_WEAPONS + "massive_mace");
    weapon->move(this_object()); 
    command("wield mace");
}


/* Short and sweet :) */
void
create_kroug()
{
    set_kroug_type(KROUG_TOUGH);
}
