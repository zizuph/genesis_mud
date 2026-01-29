/*
 * /d/Gondor/morgul/cellar/dung_1ws.c
 * A dungeon on the first floor of dungeons below the Morgul Tower
 *
 * Olorin,  5-nov-1995
 */
#pragma strict_types

inherit "/d/Gondor/morgul/cellar/cellar.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/cellar/cellar_defs.h"

public void    reset_room();

static object  Olog;

public void
create_morgul_cellar_room()
{
    set_level(1);
    set_room_type("gloomy dungeon");
    set_extra_long("There is only one exit, an archway to the north "
      + "beyond which a dark tunnel is visible.");

    add_walls();
    add_floor();
    add_archway("north");
    add_ceiling();

    add_exit(CELLAR_DIR + "cellar_1c", "north", "@@check_exit@@", 1);

    clone_object(CELLAR_DIR + "doors/prison_up")->move(TO);

    reset_room();
}

public void
reset_room()
{
    if (objectp(Olog))
        return;

    Olog = clone_object(MORGUL_DIR + "npc/ithil_olog");
    Olog->add_name("guard");
    Olog->set_long(Olog->query_long() + "This one seems to have the "
      + "duty to guard the trap door in this room.\n");
    Olog->arm_me();
    Olog->move_living("down", TO);
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (!objectp(ob) || !living(ob) || !objectp(to))
        return;

    if (file_name(to) != (CELLAR_DIR + "pris_2w1"))
        return;

    if (objectp(Olog) && present(Olog) && (Olog->query_feeling(ob) > -1))
    {
        Olog->command("cackle terr");
        set_alarm(2.0, 0.0, &Olog->command("close door"));
    }
}

