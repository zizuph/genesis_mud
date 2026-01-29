/* Elite kroug, not too many of these around.

   Coded by Maniac.

   History:
          11/8/95        Created           Maniac
*/

#pragma save_binary

inherit "/d/Calia/std/kroug";

#include "/d/Calia/sys/kroug.h"
#include <money.h>
#include "/d/Calia/mountain/monsters/monster.h"
#undef TP
#undef TO
#undef NF
#include "defs.h"

void
arm_me()
{
   object heap;
   object weapon;
   object armour;

    heap = MONEY_MAKE_GC(8);
    heap->move(this_object());

    armour = clone_object(MOUNTAIN_ARMOURS + "steel_chainmail");
    armour->move(this_object());

    armour = clone_object(MOUNTAIN_ARMOURS + "long_curve_helm");
    armour->move(this_object());

    command("wear all");

    weapon = clone_object(MOUNTAIN_WEAPONS + "two_handed_sword");
    weapon->move(this_object()); 
    command("wield sword");
}


/* Short and sweet :) */
void
create_kroug()
{
    set_kroug_type(KROUG_REGULAR);
    set_adj(({"massive","deranged"}));
    set_long("This massive, deranged kroug appears to have at one time " +
        "to have been a commander in Kroug's army, but someone or " +
        "something changed all that. While outwardly looking like any " +
        "kroug, including equipment, there's something insane in " +
        "the eyes, something that says kill or be killed.\n");
}

public int
second_life(object killer)
{
    environment(TO)->kroug_killed();
    killer->add_prop(LIVE_I_HORN_QUEST,
        killer->query_prop(LIVE_I_HORN_QUEST) | HQ_KILLED_KROUG);    
}
