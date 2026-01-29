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
    set_short("Basin inside a walled garden");
    set_long("This is a part of the walled garden surrounding the crystalline "
        + "Elemental Temple of Calia. This particular area possesses a "
        + "basin. Inside the basin is a glittering sandstorm of swirling "
        + "and dancing lights, moving in beautiful and intricate patterns. "
        + "The sand catches the light and reflects the many shades of "
        + "the rainbow onto your face.\n\n"); 
    
    add_exit(ELEMENTALIST_GARDEN + "garden_01a", "southeast");
    
}
