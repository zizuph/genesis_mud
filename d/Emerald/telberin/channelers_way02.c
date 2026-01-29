#include "defs.h"

inherit TELBERIN_CHANNELERS_WAY;

public void
create_channelers_way()
{
    set_em_long("Channelers Way swings outward ever so slightly from"
      + " its north and south march between the Royal Circle and the"
      + " Magic Quarter as it forms the edge of a narrow ellipse which"
      + " rounds a beautiful reflecting pool to the east. A green"
      + " swath of lawn runs as a border between street and water"
      + " the entire length of the road. To the west, various"
      + " buildings border the lane, their purposes difficult to"
      + " guess, though most of the people here have the look of"
      + " magic about their interests.\n");
    add_exit("channelers_way03", "south");
    add_exit("channelers_way01", "north");
}
