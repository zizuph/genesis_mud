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

static object *Citizens = allocate(2 + random(3));

public void    reset_room();

public void
create_street()
{
    set_circle("Third");
    set_streetname("Arnor Street");
    set_areaname("northern");
    set_streettype("street");
    set_activity(1);
    set_wealth(1);

    add_exit(MINAS_DIR + "n1crc3","east",0);
    add_exit(MINAS_DIR + "rooms/mtoffice","north",0);

    set_extraline("Arnor Street ends here, as the steep slopes of Mount "+
        "Mindolluin form a wall to the west. East the street continues. To the north "+
        "is the Minas Tirith Administration Office.");

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
    set_alarm(15.0 + rnd() * 30.0, 0.0, 
        &clone_npcs(Citizens, MINAS_DIR + "npc/citizen", 60.0 + rnd() * 60.0));
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

