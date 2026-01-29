/*
 *	/d/Gondor/minas/gate5.c
 *
 *	Coded by Elessar.
 *
 *	Modification log:
 *	28-Jan-1997, Olorin:	Changed inheritance.
 *  Last modified by Alto, 09 June 2001
 *      Added room tells and revised descriptions
 */
#pragma strict_types

inherit "/d/Gondor/minas/lib/street.c";
inherit "/d/Gondor/minas/lib/street_funcs.c";
inherit "/d/Gondor/minas/lib/std_gate.c";

#include <macros.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"

public void
create_street()
{
    set_circle("Fifth");
    set_streetname("Main Street");
    set_areaname("north-eastern");
    set_streettype("broad street");
    set_activity(2);
    set_wealth(2);
    add_exit(MINAS_DIR + "n1crc4", "northeast", "@@pass_gate@@");
    add_exit(MINAS_DIR + "n1crc5", "northwest", 0, 1);
    add_exit(MINAS_DIR + "e3crc5", "southeast", 0, 1);
    set_extraline("You are standing just inside the doors of the Fifth Gate, "
      + "which leads out to the Fourth Circle beyond the wall. The Main "
      + "Street continues southeast, and a narrower street goes off to the "
      + "northwest.");
    add_item(({"gates","fifth gate","gate"}), exa_gate);
    add_item(({"sixth wall", "inner wall", }), 
        "The Sixth Wall surrounds the inner parts of Minas Tirith to the southwest.\n");
    add_item(({"fifth wall", "outer wall", }), BSN(
        "The Fifth Wall surrounds the Fifth Circle, in which you are standing "
      + "right now. The Fifth Gate leads through it to the northeast."));
    add_item(({"wall", "walls", }), BSN(
        "The Fifth Wall is to the east and northeast of you, surrounding the "
      + "circle you are in, while on your other side is the Sixth Wall, "
      + "guarding the inner parts of the City.")); 

    /* These items are similar in all streets on all levels */

    add_street_items();

    set_tell_time(150);

    /* These tells are common to all streets */

    add_street_tells();

    /* These tells are unique to this circle */

    reset_room();
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

