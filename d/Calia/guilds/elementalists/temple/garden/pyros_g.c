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
        + "of dry tinder and smoldering coals. Gusts of wind blow through "
        + "the area, occasionally carrying sparks to unburned areas of the "
        + "tinder. As the old burns away, new tinders appear from the ashes "
        + "of the old in a constant cycle of burning.\n\n"); 
        
    add_exit(ELEMENTALIST_GARDEN + "garden_11m", "northwest");
}
