/*
 * f7.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit CARISCADIR + "earthroom";

void
create_earthroom()
{
    set_short("just inside a warm and damp forest");
    set_long("You are at the edge of a warm and damp forest. Around you, " +
             "you hear noises from different animals, but you can't see " +
             "much, because the thick vegetation blocks most of your view. " +
             "The ground is rather soft here, making your feet sink slightly.\n");

    add_item("ground", "The ground consists of a thick layer of leaves. " +
             "It also looks soft enough to dig in.\n");

    add_item("animals", "You can't see them, just hear them.\n");
    add_item("vegetation", "The vegetation is rather thick here.\n");

    set_noshow_obvious(0);

    add_exit("f5", "north");
    add_exit("f10", "south");
    add_wall("x6", "down");
}

int
do_dig(string direct, int how, int i)
{
    if (direct == "here" || direct == "ground" || !direct)
        direct = "down";

    return ::do_dig(direct, how, i);
}
