/*   barrel.c
 *
 * A barrel in the upper levels of the Shipwreck.
 *
 * Baldacin@Genesis, July 2003
 */

#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"
inherit "/d/Calia/std/water_room";

void
create_water_room()
{
    set_short("In a dark barrel");
    set_long("It is pitch-black in here, it feels as if something "+
        "is crawling around your legs though.\n");
    add_prop(ROOM_S_DARK_LONG, "It is pitch-black in here, it feels "+
        "as if something is crawling around your legs though. you "+
        "can leave <out>.\n");
    add_prop(ROOM_I_LIGHT, -1);

    add_swim_exit(WRECKU + "upper2","out");    
}

int
is_occupied()
{
    object *livs = FILTER_LIVE(all_inventory());
    
    if (!sizeof(livs))
       return 0;
    
    return 1;
}
