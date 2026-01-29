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
    set_short("Rocky area inside a walled garden");
    set_long("This is a part of the walled garden surrounding the crystalline "
        + "Elemental Temple of Calia. This particular area contains only "
        + "rocks of various kinds. The ground is covered in loose gravel. "
        + "In the middle of the area, a tray has been formed. Carved out "
        + "of the grey stone rock commonly found on the shores of the "
        + "Thalassian Sea, you can make out a tiny map of Calia.\n\n"); 
    
    add_exit(ELEMENTALIST_GARDEN + "garden_11a", "northeast");
}
