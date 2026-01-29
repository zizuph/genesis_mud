/*
 *  Last modified by Alto, 09 June 2001
 *      Added room tells and revised descriptions
 */
#pragma strict_types

inherit "/d/Gondor/minas/lib/street.c";
inherit "/d/Gondor/minas/lib/street_funcs.c";

#include <macros.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"

public void    reset_room();
static object *kids = allocate(2 + random(3));

public void
create_street()
{
    set_circle("Second");
    set_streetname("Main Street");
    set_areaname("northern");
    set_streettype("broad street");
    set_activity(2);
    set_wealth(1);

    add_exit(MINAS_DIR + "e3crc2","southeast",0);
    add_exit(MINAS_DIR + "n2crc2","northwest",0);
    add_exit(MINAS_DIR + "gate3","southwest","@@gate_closed");

    set_extraline("Before you to the southwest lies the Third Gate, "
      + "which leads through to the Third Circle beyond the wall. "
      + "The Main Street continues southeast, and a narrower road to "
      + "the northwest.");
    add_item(({"gates","third gate","gate"}), BSN(
        "This is the Third Gate that guards the City. The gates are open at "
      + "present, but the guards might ask for a password before they allow "
      + "anyone to pass."));
    add_item(({ "third wall", "wall", }), BSN("The Third Wall surrounds "
      + "the inner parts of Minas Tirith to the southwest, and the Third "
      + "Gate leads through it."));
    /* These items are similar in all streets on all levels */

    add_street_items();

    set_tell_time(150);

    /* These tells are common to all streets */

    add_street_tells();

    /* These tells are unique to this circle */

    reset_room();
}

public int
gate_closed()
{
    if (IS_DUNADAN(TP))
        write("A guard looks closely at you, and says: You may pass, dunadan.\n");
    else if (IS_RANGER(TP))
        write("A guard looks closely at you, and says: You may pass, ranger.\n");
    else
        write("A guard looks closely at you, and says: All right, you may pass "
          + "for now, but maybe I won't be so kind the next time.\n");
    return 0;
}

static void
clone_kid()
{
    int     i, s;

    for (i = 0, s = sizeof(kids); i < s; i++)
        if (!objectp(kids[i]))
        {
            kids[i] = clone_object(MINAS_DIR + "npc/child");
            kids[i]->set_random_move(10);
            kids[i]->set_restrain_path(MINAS_DIR);
            kids[i]->move_living("down", TO);
            set_alarm(60.0 + rnd() * 120.0, 0.0, clone_kid);
            return;
        }
}

public void
reset_room()
{
    set_alarm(15.0 + rnd() * 30.0, 0.0, clone_kid);
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

