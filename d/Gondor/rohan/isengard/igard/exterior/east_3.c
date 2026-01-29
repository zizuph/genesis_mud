/*
 *  IGARD_EXTERIOR + "east_3.c"
 *
 *  Eastern path around the outside of Isengard.
 *
 *  Last modified by Alto, 02 January 2002
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../igard_defs.h"

inherit IGARD_LIB + "igard_funcs.c";
inherit IGARD_LIB + "outside_funcs.c";

public void        create_gondor();
public string      long_desc();

static object *Orc   = allocate(2);

public void
create_gondor()
{
    set_short("A pathway beneath the ring wall of Isengard");
    set_long(&long_desc());

    sky_add_items();
    outside_add_items();
    exterior_add_items();
    add_exterior_tells();

    add_item(({"room", "area", "surroundings", "area", "place",
        "landscape"}), long_desc);

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(IGARD_EXTERIOR + "east_2.c",      "west");
    add_exit(IGARD_EXTERIOR + "east_4.c",      "east");

    reset_room();
}


string
long_desc()
{
    return "You are walking along a small gravel path directly beneath "
      + "the mighty Ring Wall of Isengard." + sky_desc() 
      + " This place stinks of orc, and every now and then you detect "
      + "a stench that resembles orc, but is unique in a disturbing way.\n";
}


public void
reset_room()
{
    clone_npcs(Orc,  IGARD_NPC + "outside_orc",  -1.0);
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
     sky_add_items();
     start_room_tells();

}

