/*
 * Vault of the Elemental Temple of Calia
 * 
 * Created by Jaacar, July 2016
 */

#pragma strict_types

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

inherit TEMPLE_ROOM_BASE;

// Defines

// Prototypes

// Global Variables

public void
create_temple_room()
{
    set_short("Elemental Vault");
    set_long("This chamber is quite large and holds many "+
        "shelves of items from throughout the realms. All four walls "+
        "are polished wood, the ceiling and floor both a smoothly "+
        "polished grey stone. The main hallway lies back out to the "+
        "south.\n\n");   
                   
    add_exit(ELEMENTALIST_TEMPLE + "stairwell4", "south");     
    
    try_item(({"shelf","shelves","many shelves"}),"The shelves hold "+
        "many items from throughout the realms.\n");
    try_item(({"items","item"}),"The items are held on the shelves.\n");
    try_item(({"floor","roof","ceiling"}),"The floor and ceiling are "+
        "both constructed with a grey stone and then smoothed and "+
        "polished afterwards. The floor is quite comfortable to "+
        "walk on.\n");
    try_item(({"wall","walls"}),"The walls here are covered in a "+
        "polished wood, light brown, almost red, in colour. They are "+
        "extremely smooth to the touch.\n");
    try_item("ceiling", "The floor and ceiling are both constructed with a "+
      "grey stone and then smoothed and polished afterwards.\n");
}

void
init()
{
    ::init();
}