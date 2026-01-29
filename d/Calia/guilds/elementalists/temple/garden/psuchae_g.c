/*
 * Garden Room of the Elemental Garden of Calia
 * 
 * Created by Petros, April 2010
 */

#pragma strict_types

#include "../defs.h"

inherit GARDEN_ROOM_BASE;

// Defines

// Prototypes

public void
create_garden_room()
{
    set_short("Platform inside a walled garden");
    set_long("This is a part of the walled garden surrounding the crystalline "
        + "Elemental Temple of Calia. This particular area contains a platform "
        + "of dark purple marble and swirling purple mists. A gentle breeze "
        + "flows around the mists, keeping them in place above the marble.\n\n"); 
        
    add_exit(ELEMENTALIST_GARDEN + "garden_01g", "south");
}
