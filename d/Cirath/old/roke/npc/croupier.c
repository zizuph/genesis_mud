/*
 * croupier.c
 *
 * Used in nyreese/cadu_casino2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/monster.c";

#include "defs.h"
#include <stdproperties.h>

object table;

void
create_monster()
{
    default_config_npc(70);
    
    set_name("croupier");
    set_short("croupier");
    set_race_name("croupier");

    add_notify_meet_interactive("meet");
    set_long("This is the croupier who handles the roulette table.\n");

    add_prop(OBJ_M_NO_ATTACK, "No violence in here please.\n");
}

void
set_table(object tab)
{
    table = tab;
}

void
meet()
{
    if (table) table->notify_enter();
}
