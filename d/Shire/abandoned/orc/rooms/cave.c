/*
 * Orc Racial cave entrance
 * This room is lighted
 * By Finwe, October 2000
 */
 

#pragma strict_types

inherit "/d/Shire/std/room.c";
#include "local.h"
#include <stdproperties.h>
#include <macros.h>
#include <language.h>

inherit TUNNEL_BASE;

void
create_tunnel_room()
{
    set_long("A large cave in the mountains. It looks large " +
        "even though the back is shrouded in shadows. The walls " +
        "are irregular with deep gashes in them. Some light " +
        "filters in from the opening, barely penetrating into " +
        "the shadows. A dark passage is in the southeastern part " +
        "of the cave.\n");

//    add_exit(ORCR_ROOM + "psg02", "out");
    add_exit(ORCR_ROOM + "psg01",  "southeast");
}
