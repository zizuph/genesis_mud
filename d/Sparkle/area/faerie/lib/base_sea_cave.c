/*
 * Base file for sea cave rooms in Faerie
 * By Finwe, April 2005
 */

#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit "/std/room";
inherit COMMON_BASE;

void create_sea_cave_room() {}

   
public void
create_room()
{
    set_short("Inside a rock cave");
    set_long(short() + " It is large with a sloping, irregular ceiling. " +
        "The walls are rough, having been carved by the sea many years " +
        "ago. The ground is dirty and littered with rocks and pebbles.\n");
        

    create_sea_cave_room();
    reset_room();
 
    add_prop(ROOM_I_INSIDE, 1); // This is an indoor room
    add_prop(ROOM_I_NO_ALLOW_STEED, 1); // sorry, no horses in here.
}

/*
 * Function name : set_cave_room
 * Description   : adds descr of dry cave room
 */
void set_cave_room()
{
    add_item(({"pebbles", "rocks"}),
        "They are small stones that have been dislodged from the walls " +
        "and ceiling. They are smooth and various sizes.\n");
    add_item(({"ceiling"}),
        "It is jagged and irregular shaped. The ceiling is low and " +
        "was carved by the sea many years aqo.\n");
    add_item(({"walls"}),
        "The walls are rough and irregular from having been carved by " +
        "rushing sea waters.\n");
    add_item(({"ground"}),
        "The ground is uneven and dirty, and littered with rocks and " +
        "pebbles.\n");
}

/*
 * Function name : 
 * Description   : adds descr of 
 */
void set_add_stream()
{
    add_item(({"water", "stream", "cool water", "cool clear water", 
            "clear water"}),
        "It bubbles up from the earth somewhere nearby and flows through " +
        "the cave. The water is cool and clear, and looks refreshing.\n");
    add_item(({"walls"}),
        "The walls are irregular shaped. They look smooth and clammy " +
        "from water that seems to constantly run down them.\n");
    add_item(({"ceiling"}),
        "It is jagged and irregular shaped. The ceiling is low and " +
        "was carved by the sea many years aqo. Water drips from the " +
        "ceiling, splashing into the stream.\n");
    add_item(({"pebbles", "rocks"}),
        "They are small stones, smoothed by the flowing water. They lay " +
        "scattered around in the water.\n");
    add_item(({"ground"}),
        "The ground is uneven and and sprinkled with pebbles and rocks. " +
        "Cool, clear water flows acrossed it from somewhere in the caves.\n");
}
