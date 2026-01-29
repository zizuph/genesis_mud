/*
 * /d/Gondor/anorien/osgiliath/osgiliath.c
 *
 * inherited by osgiliath rooms that are inaccessible when
 * the bridge is destroyed to prevent players from 
 * teleporting in
 */

#pragma strict_types

#include "/d/Gondor/defs.h"

#define	BRIDGE_ROOM	(OSG_DIR+"wbridge1")

public mixed	check_teleport();

public mixed
check_teleport()
{
    if ( !objectp(TP) )
	return 1;

    if ( ENV(TP) == TO )
	return 0;

    BRIDGE_ROOM->short();
    if ( !BRIDGE_ROOM->query_bridge_broken() )
	return 0;

    return "You don't seem to be able to focus on that location.\n";
}
