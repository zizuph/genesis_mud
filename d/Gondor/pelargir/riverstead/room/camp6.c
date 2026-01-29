/*
 *  NCAMP_ROOM + "camp6.c"
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
        
    add_item(({"tower", "large tower", "watchtower"}), "The tall "
        + "structure rising above the huts to the south appears "
        + "to be some kind of watchtower. You would need to move "
        + "south to see it more clearly.\n");
    add_item(({"building", "shop", "wooden building", "store"}), 
        "The large building seems different from the others in "
        + "the vicinity, suggesting that its owner makes a better "
        + "living than would be expected for a farmer. Through the "
        + "door you see various items on display. No doubt this "
        + "is the village store.\n");
        
    add_prop(ROOM_I_INSIDE, 0);
    
    defence_status = 1;

    add_exit(NCAMP_ROOM + "camp5.c", "north");
    add_exit(NCAMP_ROOM + "camp14.c", "east");
    add_exit(NCAMP_ROOM + "camp7.c", "south");
    add_exit(NCAMP_ROOM + "camp4.c", "west");
    add_exit(NCAMP_ROOM + "store.c", "enter", 0, 0, 1);

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
    return "Here in the northern part of the settlement, you find "
        + "yourself surrounded by numerous huts built closely "
        + "together. Just south of here you spy a large tower of "
        + "some sort."
        + sky_desc() 
        + " There is a rather large wooden building nearby that "
        + "looks like a shop, although you cannot tell what "
        + "mannner of goods are sold within. Perhaps you should "
        + "enter and ask the proprietor.\n";
}
