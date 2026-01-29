#pragma strict_types

#include "defs.h"
inherit TBASE;


public void
tunnel_room(void)
{
    set_short("stairwell");
    set_long("A low whistling emanates from the stairwell "+
	"as hot, dry winds flow up from the center of "+
	"this open stairwell. Open to the darkness "+
	"below, the circular stairs descend around the "+
	"inner wall of this great hole.\n");

    add_item(({"stair","stairs","step","steps","stairwell"}),
	"The circular stairs run along the interior of the "+
	"gaping opening, fixed against the inner wall of "+
	"the abyss. The center of the stairwell is open, "+
	"with no bannister at the inner edge.\n");

    ANTIMAGIC;
}

public varargs object
link_room(string lfile, mixed dest, int pos)
{
    return clone_object(STAIR_MASTER);
}
