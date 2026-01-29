inherit CELL_DOOR_BASE

#include "../defs.h"
#include <stdproperties.h>


void
create_door()
{
    set_door_id("cell_door");
    set_door_name(({"steel door", "cell door", "door"}));
    
    
    set_open(0);
    set_locked(1);    