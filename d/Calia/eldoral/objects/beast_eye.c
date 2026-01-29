/*
 * beast_eye
 * 
 * This item is the 'eye of the beast', a monster in the north ravine
 * of the island, and is the 'evidence' for completion of the fourth
 * quest in Eldoral.
 *
 * Khail, Jan 27/96
 */
#pragma strict_types

#include "defs.h"

inherit "/std/object";

string killer;

public void
create_object()
{
    set_name("eye");
    add_name(ELDORAL_BEAST_EYE_NAME);
    set_adj("brilliant");
    add_adj("green");
    set_short("brilliant green eye");
    set_long("This object looks at first glance to be an emerald " +
        "or some other green gem, but the brilliant green glare " +
        "it gives off seems all the stranger when you look " +
        "closer and realize it to be an eye.\n");

    add_prop(OBJ_I_VALUE, 10);
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_S_WIZINFO, "This item is a quest-marker for " +
        "the Eye of the Beast quest in Eldoral. Once obtained " +
        "by killing the beast, /d/Calia/eldoral/npc/ravine_beast, " +
        "it should be returned to Firestorm for the final rewar, " +
        "/d/Calia/eldoral/npc/firestorm.\n");
    add_prop(OBJ_M_NO_BUY, 1);
}

public void
set_killer(string who)
{
    killer = who;
}

public string
query_killer()
{
    return killer;
}

