/*
 * npc.c
 *
 * Standard library used in npc's of Erech.
 */
#pragma save_binary
#pragma strict_types

inherit "/std/monster";     /* for humanoid monsters */
inherit "/std/act/action";  /* make it do things */
inherit "/std/act/chat";    /* make it talk */

#include "../erech.h"     /* for Erech definitions */

#include <stdproperties.h>
#include <macros.h>

int
ghost_filter(object ghost)
{
  // test to se if it is any of the ghosts;

  return (ghost->id("_any_ghost_of_erech_"));
}

void
help_ghost(object enemy, object friend)
{
    if ((objectp(enemy) || objectp(query_attack())) &&
	present(enemy, ENV(this_object())) && CAN_SEE_IN_ROOM(this_object()) &&
	CAN_SEE(this_object(), enemy))
    {
        command("shout " + one_of_list(ANGRY_CRY));
	command("kill " + enemy->query_real_name());
    }
}

void
call_for_ghosts(object ob)
{
    int i;
    object room = ENV(this_object()),
           *arr = all_inventory(room);

    arr = filter(arr, "ghost_filter", this_object());
    for (i = 0; i < sizeof(arr); i++)
        arr[i]->notify_ob_attacked_me(this_object(), ob);
}



