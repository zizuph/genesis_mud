/*
 *  NCAMP_ROOM + "camp15.c"
 *
 *  A dirt path. Only newbies and wizards should ever see this place.
 *
 *  Last modified by Alto, 17 November 2002
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

static object *Man = allocate(2);
static object *Orc = allocate(2);

public void
create_gondor()
{
    set_short("in the northern part of a settlement");
    set_long(&long_desc());

    sky_add_items();
    camp_add_items();
    add_camp_tells();

    add_item(({"room", "area", "surroundings", "place",
        "landscape", "settlement", "village", "camp"}), long_desc);
        
    add_item(({"tree", "trees"}), "The trees of the woodland "
        + "to the north grow very close together. It is unlikely "
        + "you could enter them here.\n");
    add_item(({"woods", "woodland", "stand"}), "A dense stand "
        + "of trees grows to the north of the settlement.\n");
    add_item(({"huts", "cabins"}), "Most of the huts to the "
        + "southwest look intact, but those to the southeast "
        + "are mostly either on fire or burned to the ground.\n");
    add_item(({"hut"}), "There is a hut here that still looks "
        + "secure enough to enter, although the smoke rolling "
        + "from the windows suggests it may not remain that "
        + "way for long.\n");
        
    add_prop(ROOM_I_INSIDE, 0);
    
    defence_status = 1;

    add_exit(NCAMP_ROOM + "camp16.c", "northeast");
    add_exit(NCAMP_ROOM + "camp17.c", "east");
    add_exit(NCAMP_ROOM + "camp14.c", "south");
    add_exit(NCAMP_ROOM + "camp5.c", "west");
    add_exit(NCAMP_ROOM + "hut15.c", "enter", 0, 0, 1);

    reset_room();
}

public void
reset_room()
{
    if(defence_status)
    {
    clone_npcs(Man, NCAMP_NPC + "ncamp_human_male", -1.0);
    return;
    }

    clone_npcs(Orc, NCAMP_NPC + "ncamp_orc", -1.0);
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
    {
        sky_add_items();
        start_room_tells();
    }
}

string
long_desc()
{
    return "You are standing in the northern parts of the "
        + "settlement. Huts are built to the south of here, "
        + "whereas a dense stand of trees can be seen "
        + "to the north."
        + sky_desc() 
        + " Most of the huts to the southwest are still "
        + "standing, but to the southeast many of the cabins "
        + "have burned to the ground. There is one hut nearby "
        + "that looks safe enough to enter, although you see "
        + "smoke rolling from the windows.\n";
}
