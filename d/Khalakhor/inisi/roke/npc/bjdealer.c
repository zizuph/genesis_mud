/*
 * bjdealer.c
 *
 * Used in obj/bjtable.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/monster";

#include <stdproperties.h>

void
create_monster()
{
    default_config_npc(100);
  
    set_name("dealer");
    set_short("dealer");
    set_race_name("dealer");

    set_long("This is the guy who plays Black Jack like a god.\n");
    
    add_prop(OBJ_M_NO_ATTACK, "No violence in here please.\n");

    NEVERKNOWN;
}
