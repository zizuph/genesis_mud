/* Tough kroug.
   This particular one wields a gold broadsword and a main gauche..

   Coded by Maniac.

   History:
          20/2/96        Mofified          Maniac
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

    weapon = clone_object(MOUNTAIN_WEAPONS + "gold_broadsword");
    weapon->move(this_object()); 
    command("wield broadsword");

    weapon = clone_object(MOUNTAIN_WEAPONS + "main_gauche");
    weapon->move(this_object()); 
    command("wield gauche");
}


/* Short and sweet :) */
void
create_kroug()
{
    set_kroug_type(KROUG_TOUGH);
}
