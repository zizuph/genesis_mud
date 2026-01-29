inherit "/std/board";

#include <std.h>

int
block_reader()
{
    if (SECURITY->query_wiz_rank(geteuid(this_interactive())) >= WIZ_STEWARD)
    {
	return 0;
    }

    return 1;
}

int
block_writer()
{
    if (SECURITY->query_wiz_rank(geteuid(this_interactive())) >= WIZ_LORD)
    {
	return 0;
    }

    return 1;
}
