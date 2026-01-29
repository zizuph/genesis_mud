/*
 *  NCAMP_ROOM + "hut10.c"
 *
 *  A hut. Only newbies and wizards should ever see this place.
 *
 *  Last modified by Alto, 16 November 2002
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include <math.h>
#include "/d/Gondor/defs.h"
#include "../ncamp_defs.h"

inherit NCAMP_LIB + "ncamp_funcs.c";

public void        create_gondor();
public string      long_desc();

static object *Woman = allocate(2);
static object *Orc = allocate(2);

object pot;

public void
create_gondor()
{
    set_short("a dilapidated hut in the southern parts of "
        + "the settlement");
    set_long(&long_desc());

    hut_add_items();

    add_item(({"room", "area", "surroundings", "place",
        "cottage", "house", "hut", "cabin", "building"}), long_desc);

    add_prop(ROOM_I_INSIDE, 1);

    defence_status = 1;

    add_exit(NCAMP_ROOM + "camp10.c", "out");

    setuid();
    seteuid(getuid());

    pot = clone_object(NCAMP_OBJ + "pot10.c");
    pot->move(TO);

    reset_room();
}

public void
reset_room()
{
    pot->remove_object();

    pot = clone_object(NCAMP_OBJ + "pot10.c");
    pot->move(TO);

    if(defence_status)
    {
    clone_npcs(Woman, NCAMP_NPC + "ncamp_human_female", -1.0);
    return;
    }

    clone_npcs(Orc, NCAMP_NPC + "ncamp_orc", -1.0);
}

string
long_desc()
{
    return "The residents of this hut have quite obviously fallen "
        + "upon hard times. In the middle of the room rests the hut's "
        + "sole "
        + "object of furniture. At least they could afford a pot to "
        + "piss in.\n";
}
