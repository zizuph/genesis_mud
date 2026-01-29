/*
 * Stairwell leading down to the elite training room
 *  Cirion 032096
 */
#pragma strict_types
#include "../defs.h"

inherit BASE;

#include <ss_types.h>


public void
union_room(void)
{
    set_short("darkened stairwell");
    set_long("Smooth cylindrical walls rise up above you, "+
	"as if you were down some massive well. The stairs "+
	"beneath your feet are made from multi coloured stone, "+
	"once a mosaic, and lead down into a stygian "+
	"shadow, terrifyingly dark.\n");

    add_item(({"stair","ground","floor","mosaic","stairwell",
	    "stairway"}), "The stair was once a mosaic, and now "+
	"has fallen into perfect order, lowering into a darkness "+
	"ages old.\n");
    add_item(({"dark","blackness","gloom","shadow"}),
	"It threatens to consume you.\n");

    add_exit("elite", "down", "@@go_down@@");
    add_exit("crossing", "up", "@@go_up@@");
}

public int
go_down(void)
{
    if (TP->query_stat(SS_DIS) < 85)
    {
	write("You are too terrified to continue down.\n");
	TP->add_panic(100000);
	return 1;
    }

    write("You descend into the dark shadows, and are immediately "+
	"engulfed within the gloom.\n");
    return 0;
}

private void
rem_stair(void)
{
    (ROOM + "crossing")->remove_stair();
}

public int
go_up(void)
{
    set_alarm(1.0, 0.0, rem_stair);
    (ROOM + "crossing")->make_stair();
    write("You ascend into the light.\n");
    return 0;
}
