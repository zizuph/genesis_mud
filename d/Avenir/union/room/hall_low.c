/*
 * Hallway in the Union
 *  Cirion 032096
 */
#pragma strict_types
#include "../defs.h"

#include <filter_funs.h>
#include <composite.h>

inherit BASE;

public int
go_east(void)
{
    write("You follow the hallway to the east.\n");
    return 0;
}

public int
go_down(void)
{
    write("You descend the stairway into the mist.\n");
    return 0;
}

public void
union_room(void)
{
    set_short("limestone hallway");
    set_long("This is the western end of a pale white "
      +"hallway that stretches back to the east. Below you, "
      +"a beautifully carved stone circular stairway descends "
      +"into a thick white mist that seems to dance with "
      +"flickering shadows. A massive chamber opens up to the north, "
      +"from which can be heard the sound of water.\n");

    add_item(({"stair","stairs","staircase","stairwell","stairway"}),
	"The stair is carved from a white stone similiar to "+
	"the walls, but more sturdy. It descends into "+
	"a thick white mist.\n");
    add_item(({"mist","fog","tendrils","white"}),
	"White tendrils of fog reach up from below, swirling "+
	"around the edge of the stairwell.\n");
    add_item("down", "That way is obscured by the mist.\n");
    add_item(({"hall","hallway","wall","walls","limestone"}),
	"The walls of the hallways are made from a powdery "+
	"smooth limestone, flawless and white.\n");
    add_item(({"floor","ground"}),
	"The floor is solid white stone, the same material as "+
	"the staircase.\n");

    add_exit("landing", "east", "@@go_east@@");
    add_exit("guild", "down", "@@go_down@@");
    add_exit("astuary", "north");
}
