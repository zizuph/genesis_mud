/*
 * jail_storage.c
 *
 * This is a store room for the equipment taken from
 * prisoners. 
 * 
 * Khail - June 20/97
 */
#pragma strict_types

#include "/d/Khalakhor/sys/defs.h"
#include <stdproperties.h>
#include "room.h"

inherit "/d/Khalakhor/std/room";

mapping equipment;

public int *
query_local_coords()
{
    return ({18,2});
}

public int *
query_global_coords()
{
    return VILLAGE_COORDS;
}

public void
create_khalakhor_room()
{
    set_short("storage room");
    set_long("   You are in a storage room of sorts, where " +
        "items confiscated by the guards of Port Macdunn " +
        "are stored until they are returned to their " +
        "owners. It's a rather plain room, nothing more " +
        "than four stone walls with a few shelves " +
        "attached to them.\n");

    add_item(({"shelves"}),
        "The shelves are probably intended to hold " +
        "items that have been confiscated, but they " +
        "don't appear to be used much.\n");
    add_item(({"floor", "ground"}),
        "The floor of the room is simply hard-packed " +
        "earth.\n");
    add_item(({"walls", "wall"}),
        "The walls of the room are made from various sized " +
        "pieces of hard grey stone, carefully placed together " +
        "and packed with clay.\n");
    add_item(({"roof", "ceiling"}),
        "The ceiling is constructed a bit more sturdily than " +
        "most buildings in the village, and seems to be " +
        "made from several layers of wooden planks atop " +
        "heavy rafters.\n");
    add_item(({"rafters"}),
        "The thatch of the roof is supported by a handful of " +
        "thick wooden rafters.\n");

    INSIDE;
    DARK;

    add_exit(ROOM + "jail_corridor_1", "south");
    equipment = ([]);
}

public int
add_equipment(object *obarr, object who)
{
    equipment[who->query_real_name()] = obarr;
    obarr->set_no_merge(1);
    obarr->move(TO);
}

public object *
get_equipment(object who)
{
    mixed *obarr;

    if (!equipment[who->query_real_name()])
        return ({});

    obarr = equipment[who->query_real_name()];
    obarr = filter(obarr, objectp);
    obarr = filter(obarr, &operator(==)(TO) @ environment);
    obarr->set_no_merge(0);
    return obarr;
}

public mapping
query_equipment()
{
    return equipment + ([]);
}
