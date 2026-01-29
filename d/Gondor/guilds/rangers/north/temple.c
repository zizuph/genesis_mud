/*
 *  /d/Gondor/guilds/rangers/north/temple.c
 *
 *  The temple of Tulkas.
 *
 *  Coded by Elessar
 *    Modified by Alto, 17 July 2001, changed to fit revised themes
 *
 */
inherit "/d/Gondor/std/room.c";

#include "../rangers.h"
inherit RANGERS_NOR_DIR + "north_funcs.c";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"
#include "check_exit.c"

public string      long_desc();

string
long_desc()
{
    string txt;

    if (gTstand->query_torch_is_lit())
        txt = " from which a warm flickering light plays off the walls, "
            + "floor and ceiling. ";
    else
        txt = ". ";

    return "This large hall is the temple of Tulkas, also called Astaldo. "
        + "Set into the north wall is an iron torch stand" + txt + "The "
        + "temple is spartanly furnished, with a simple but beautiful altar "
        + "built into the east wall.\n";
}

void
create_gondor()
{
    set_short("the temple of Tulkas");
    set_long(&long_desc());

    north_add_items();

    add_item(({"room", "hall", "temple"}), &long_desc());
    add_item(({"walls"}), "There are three primary walls in the room, the "
        + "north wall, the east wall and the south wall.\n");
    add_item(({"north wall"}), "Like much of the underground hideout, the "
        + "walls are made of stone. The north wall is unadorned save the "
        + "iron torch stand mounted upon it.\n");
    add_item(({"east wall"}), "The east wall is unadorned, and the bare "
        + "stone provides a stark backdrop to the large altar placed before "
        + "it.\n");
    add_item(({"south wall"}), "The south wall is unadorned and composed "
        + "entirely of stone.\n");
    add_item(({"altar", "simple altar", "beautiful altar"}), "The altar "
        + "is dedicated to the worship of Tulkas, or as he is often called, "
        + "Astaldo. Although the altar is fairly simple in construction, "
        + "there is something beautiful and elegant about its smooth facade. "
        + "From somewhere deep inside, you feel strength and courage welling "
        + "up within you, and a compelling urge to worship and pray here.\n");

    add_item(({"sentinel", "grey-cloaked sentinel"}), "You are too late! "
        + "Ranger sentinels are usually too busy with their duties to "
        + "stand around long enough to be looked at.\n");

    add_exit(RANGERS_NOR_DIR + "t_corridor", "west");

    add_prop(ROOM_I_INSIDE, 1);
    set_alarm(1.1, 0.0, &add_prop(ROOM_I_LIGHT, 0));

    reset_room();
}

void
reset_room()
{
    set_alarm(1.0, 0.0, &north_add_torch());
}


public void
init()
{
    ::init();
    add_action("pray","pray");
    add_action("pray","worship");
}

int
pray()
{
    write("You kneel and start to pray to Tulkas. A sudden warmth "
        + "surrounds you and there is fresh hope and strength coursing "
        + "in your veins. As you open your eyes, a bright light fades and "
        + "you are once again looking upon the simple altar.\n"); 
    say(QCTNAME(TP) + " closes " + POSSESSIVE(TP) + " eyes and kneels "
        + "briefly. The room is filled with a sudden bright light. As the "
        + "light fades, you see fresh hope in " + QTPNAME(TP) + " eyes.\n");
    return 1;
}
