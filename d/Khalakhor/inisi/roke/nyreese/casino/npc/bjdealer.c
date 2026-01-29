/*
 * bjdealer.c
 *
 * Used in obj/bjtable.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 *
 * Moved to new casino and updated, Treacher Oct 2021
 */

#pragma save_binary
#pragma strict_types

#include "../defs.h"

inherit ROKEDIR + "lib/monster";

#include <stdproperties.h>

void
create_monster()
{
    default_config_npc(100);
  
    set_name("dealer");
    set_short("dealer");
    set_race_name("dealer");

    set_long("He is pleasant looking and stands patiently behind the " +
             "black jack table.\n");
    
    add_prop(OBJ_M_NO_ATTACK, "No violence in here please.\n");

    NEVERKNOWN;
}
