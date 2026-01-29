/* Prototype arrow by Morrigan */
#include "/d/Krynn/common/defs.h"
#include <macros.h>

inherit "/std/object";

int gQuality;

void set_quality(int qual)
{
    gQuality = qual;
}

int query_quality()
{
    return gQuality;
}

int test_quality(int diff)
{
    if (diff > query_quality())
	return 0;

    return 1;
}

void create_object()
{
    set_name("arrow");
    set_short("wooden arrow");
    set_long("A wooden arrow.\n");

    if (!query_quality())
	set_quality(30);
}

