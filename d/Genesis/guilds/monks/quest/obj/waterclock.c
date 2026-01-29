#include "defs.h"
inherit "/std/object";

public void
create_object ()
{
    set_name ("waterclock");
    add_name ("hourglass");
    add_name (QUEST_WATERCLOCK);
    set_short ("small water-filled hourglass");
    set_long ("Perfectly clear glass on this oak-framed "
	+ "hourglass shows @@describe_water@@.\n");
}

public string
describe_water ()
{
    return "water";
}

