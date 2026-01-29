/*
 *  Last modified by Alto, 09 June 2001
 *      Added room tells and revised descriptions
 */

#pragma strict_types

inherit "/d/Gondor/minas/lib/street.c";
inherit "/d/Gondor/minas/lib/street_funcs.c";

#include <language.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"

static object *Kids = allocate(2 + random(4));

public void reset_room();

public void
create_street()
{
    set_circle("First");
    set_streettype("street");
    set_areaname("southeastern");
    set_streetname("Ithilien Street");
    set_streetlight(2);
    set_wealth(2);
    set_activity(2);
    add_exit(MINAS_DIR + "e1crc1", "northeast");
    add_exit(MINAS_DIR + "s2crc1", "southwest");
    add_exit(MINAS_DIR + "gate2",  "northwest");

    set_extraline("Just before you to the northwest is the Second Gate of "+
        "Minas Tirith, and going through will bring you further into "+
        "the city, to the Second Circle. Northeast, the street continues "+
        "towards the main gate. ");
    add_item("gate", BSN("The Second Gate is quite impressively "
        + "large, but not as large as the First Gate. The great doors "
        + "of the Gate are opened, letting people pass through it."));
    /* These items are similar in all streets on all levels */

    add_street_items();

    set_tell_time(150);

    /* These tells are common to all streets */

    add_street_tells();

    /* These tells are unique to this circle */

    reset_room();
}

public object
clone_npc(object npc, string file)
{
    if (objectp(npc))
        return npc;

    npc = ::clone_npc(npc, file);
    npc->set_random_move(30);
    npc->set_restrain_path(MINAS_DIR);

    return npc;
}

public void
reset_room()
{
    set_alarm(30.0, 0.0, &clone_npcs(Kids, MINAS_DIR + "npc/child", 60.0 + rnd() * 60.0));
}

/*
 * This function enables the random room tells.
 */

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}



