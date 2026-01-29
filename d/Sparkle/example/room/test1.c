/*
 * /d/Sparkle/example/room/test1.c
 *
 * Example Room - for the purpose of training new wizards
 * 
 * Varian 2016
 */
 
#pragma strict_types

inherit "/std/room.c";

#include "/d/Sparkle/common/defs.h"
#include <stdproperties.h>
#include <macros.h>

void
create_room()
{
    set_short("A small tree grove");
    set_long("You are in the middle of a small grove of trees, hidden " +
        "away from the rest of the world. The trees are so densely " +
        "packed here, that there appears to be no exit except to follow " +
        "the path north.\n");
    add_item("tree","These trees are very densely packed together, opening " +
        "only around the narrow path that winds its way north.\n");  
    add_item(({"path","narrow path"}),
        "This narrow path leads north, cutting through the densely " +
        "packed grove of trees.\n");    
    add_exit("/d/Sparkle/example/room/test2", "north");
}
