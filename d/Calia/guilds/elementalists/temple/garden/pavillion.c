/*
 * Garden Room of the Elemental Garden of Calia
 * 
 * Created by Petros, April 2010
 */

#pragma strict_types

#include <stdproperties.h>
#include "../defs.h"

inherit GARDEN_ROOM_BASE;

// Defines

// Prototypes

public void
create_garden_room()
{
    set_short("A pavillion inside a walled garden");
    set_long("This is a part of the walled garden surrounding the crystalline "
        + "Elemental Temple of Calia. This particular area is a bit raised "
        + "compared to the rest of the garden and has been formed into "
        + "a pavillion marked with five wide strips of white cloth attached "
        + "at the center to a circle. The cloth sways gently in the wind. At "
        + "the north end of the pavillion is a reflecting pond.\n\n"); 
    
    try_item( ({ "pond", "reflecting pond" }),
        "The reflecting pond contains the clearest of waters, but you "
      + "are unable to perceive the depth of the waters. As you gaze "
      + "upon it, it shows you multiple reflections of yourself that "
      + "seem to shift in and out.\n");
       
    add_prop(OBJ_I_CONTAIN_WATER, 1);
    
    add_exit(ELEMENTALIST_GARDEN + "garden_06m", "west");
}
