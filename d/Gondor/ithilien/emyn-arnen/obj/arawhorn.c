/*
 * /d/Gondor/ithilien/emyn-arnen/obj/arawhorn.c
 * Coded by Olorin
 *
 *  Modification history:
 * June 5th 1995, Elessar. - Changed the add_action("play_horn","play"); to
 *                           "blow_horn","play", as the new GD revealed the lack
 *                           of the function play_horn().
 */
#pragma strict_types

inherit "/std/object.c";
inherit "/lib/keep.c";
inherit "/d/Gondor/common/lib/tell_funcs.c";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_object()
{
    set_name("horn");
    set_adj("ivory");
    set_adj("silver-clad");
    set_short("silver-clad ivory horn");
    set_long(BSN("This ivory horn is from the great Kine of Araw. Silver is clad "
      + "around it in intricate patterns, and the horn has been hollowed out "
      + "to make it possible to blow in it, and produce a strong sound."));
    add_prop(OBJ_I_WEIGHT, 250);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE,  600);
    add_prop(OBJ_M_NO_BUY,1);
    FIX_EUID
}

public int
blow_horn(string str)
{
    string  his;

    if ((!str) || (str != "horn"))
    {
        NF(CAP(query_verb())+" what?\n");
        return 0;
    }

    his = TP->query_possessive();

    write("You breathe deeply, and blow the horn.\n"
        + "You produce a deep and mighty, bellowing sound!\n");
    say(QCTNAME(TP)+" blows into "+his+" horn, and produces a mighty sound!\n",TP);

    if (ENV(TP)->query_prop(ROOM_I_INSIDE))
        return 1;

    tell_players_in_same_subdir(TP,
        "The sound of a hunting horn echoes through the area.\n", 0);
    tell_next_room_with_dir(ENV(TP),
        "You hear the sound of a mighty horn from");
    return 1;
}

public string
query_recover()
{
    return MASTER + ":";
}

public void
init()
{
    ::init();
    add_action(blow_horn, "blow");
    add_action(blow_horn, "play");
}

