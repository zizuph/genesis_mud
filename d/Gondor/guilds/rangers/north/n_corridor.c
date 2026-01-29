/*
 *  /d/Gondor/guilds/rangers/north/n_corridor.c
 *
 *  A hallway in the North Hideout.
 *
 *  Coded by Elessar
 *    Modified by Alto, 14 July 2001, changed to fit revised themes
 *
 */
inherit "/d/Gondor/std/room.c";

#include "../rangers.h"

inherit RANGERS_NOR_DIR + "north_funcs.c";

#include <macros.h>
#include <stdproperties.h>

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
    return "You are standing in the northern corridor of the underground "
        + "hideout. A large tapestry hangs on the south wall. Set into the "
        + "north wall is an iron torch stand" + txt + "The corridor leads "
        + "further to the west and opens onto a brightly lit room to the "
        + "east while a narrow arch opens up into an alcove to the north.\n";
}

public void
create_gondor()
{
    set_short("a northern corridor");
    set_long(&long_desc());

    north_add_items();

    add_item(({"room", "corridor", "northern corridor"}), &long_desc());
    add_item(({"tapestry", "south wall", "southern wall"}), 
        "The tapestry shows one of the "
        + "most beautiful locations of the Second Age. You see a high and "
        + "steep mountain, Meneltarma, on the island of Numenor, the "
        + "ancestral home of the Dunedain. Numenor sank below the waves when "
        + "the last king, Ar-Pharazon, became too arrogant and challenged "
        + "the Valar.\n");
    add_item(({"walls"}), "There are two primary walls in the room, the north "
        + "wall and the south wall.\n");
    add_item(({"north wall", "northern wall"}), "Like much of the underground hideout, the "
        + "walls are made of stone. An iron torch stand hangs beside " +
        "a narrow arch which opens up into an alcove to the north.\n");
    add_item(({"alcove", "small alcove"}), 
        "This alcove is rather small and cramped, apparentl holding " +
        "nothing more than a long wooden table and the strong scent " +
        "of herbs.\n");
    add_item(({"arch", "narrow arch"}), 
        "This narrow arch cuts through the stone of the northern wall and " +
        "opens up into a small alcove.\n");
    add_item(({"hatch", "small hatch", "small wooden hatch"}), "Cleverly "
        + "hidden among the arches of the ceiling is a small wooden hatch.\n");

    add_item(({"sentinel", "grey-cloaked sentinel"}), "You are too late! "
        + "Ranger sentinels are usually too busy with their duties to "
        + "stand around long enough to be looked at.\n");

    add_exit(RANGERS_NOR_DIR + "song_room", "east");
    add_exit(RANGERS_NOR_DIR + "north_train", "west");
    add_exit(RANGERS_NOR_DIR + "herbalist", "north");

    add_prop(ROOM_I_INSIDE, 1);
    set_alarm(1.1, 0.0, &add_prop(ROOM_I_LIGHT, 0));
    reset_room();
}

void
reset_room()
{
    set_alarm(1.0, 0.0, &north_add_torch());
}

