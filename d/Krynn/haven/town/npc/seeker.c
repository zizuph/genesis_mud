/*
 * seeker.c
 * A seeker, in the town of haven
 * Uses the SEEKERBASE file.
 * Created by Tibbit, 16 Feb 1998
 *
 *
 */

#include "../local.h"

inherit SEEKERBASE;

void
create_seeker()
{
    set_level((2 + random(2)));

    set_random_move(5,0);
    set_restrain_path(HDIR);
}

