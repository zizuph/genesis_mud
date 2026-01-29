/*
 * Hallway in the Union guildhall
 *  Cirion 032096
 */
#pragma strict_types
#include "../defs.h"

#include <filter_funs.h>
#include <composite.h>

inherit BASE;

public void
union_room(void)
{
    set_short("lower landing");

    set_long("This is a wide stone landing made from "
      +"white marble streaked with veins of adamantine. "
      +"The wide stairs that descend from the north continue "
      +"down to the south. There is an opening to the east "
      +"into a pale blue room, and there is a short "
      +"hallway leading west.\n");

    add_item(({"hall","hallway","wall","walls","limestone"}),
      "The walls of the hallways are made from a powdery "+
      "smooth limestone, flawless and white.\n");
    add_item(({"floor","ground"}),"The floor is solid "+
	"marble, the same as the stairs.\n");
    add_item(({"stairs","stair","staircase"}),"The stairs "+
	"climb to the north where they seem to turn west, and "+
	"descend to the south into a thick gloom from which "+
	"hot air rises.\n");

    add_exit("hall_e","up");
    add_exit("f_landing","down","@@go_down@@");
    add_exit("blue", "east");
    add_exit("hall_low","west");
}
