/*
 * /d/Gondor/common/dwarf_guild/virtual.c
 *
 * This room is a non-existant room. Some NPC's might seek refuge here if
 * they are attacked and cannot manage to kill the attacker(s).
 *
 * /Mercade, 9 January 1994
 *
 * Revision history:
 */

#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("some floating essence in the fabric of space");
    set_long("You are floating in the fabric of space.");

    add_prop(OBJ_S_WIZINFO, BSN("This room is used by some dwarves that " +
        "seek refuge here if they are attacked by hordes of evil players " +
        "and they fear they cannot manage to stand against them. No mortal " +
        "should even be in this room. The exit \"start\" will take you to " +
        "your starting location. (Just in case a mortal would get here.)"));

    add_exit("@@get_start", "start");
}

string
get_start()
{
    return (TP->query_default_start_location());
}