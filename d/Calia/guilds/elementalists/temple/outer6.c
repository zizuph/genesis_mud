/*
 * Outer Circle of the Elemental Temple of Calia
 * 
 * Created by Petros, April 2010
 */

#pragma strict_types

#include "defs.h"

inherit TEMPLE_ROOM_BASE;

// Defines

// Prototypes

public void
create_temple_room()
{
    add_exit(ELEMENTALIST_TEMPLE + "outer4", "northwest");
    add_exit(ELEMENTALIST_TEMPLE + "outer8", "south"); 
    add_exit(ELEMENTALIST_TEMPLE + "herbalist", "northeast", "@@cannot_enter_restrict_resource_banned",1, "@@cannot_see_restrict_resource_banned");     
}

/*
public int
herb_shop_closed()
{
    if (this_player()->query_wiz_level() > 0)
    {
        return 0;
    }
    
    write("The herb store is not yet open. Once the construction "
        + "of the temple is complete, you should be able to buy "
        + "and sell herbs here.\n");
    return 1;
}
*/
