/*
 *	/d/Gondor/minas/n2crc5.c
 *
 *	Coded by Elessar.
 *
 *	Modification log:
 *	29-Jan-1997, Olorin:	Changed inheritance,
 *				general revision.
 *  Last modified by Alto, 09 June 2001
 *      Added room tells and revised descriptions
 */
#pragma strict_types

inherit "/d/Gondor/minas/lib/street.c";
inherit "/d/Gondor/minas/lib/street_funcs.c";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"

string
read_letters()
{
    return BSN("Into the outer wall of the balcony are hewn letters almost "
         + "three feet high. You can read:")
         + "\tLibrary of the City of Minas Tirith\n";
}

public void
create_street()
{
    set_circle("Fifth");
    set_streetname("Elendil's Street");
    set_areaname("northern");
    set_streettype("street");
    set_activity(1);
    set_wealth(2);

    add_exit(MINAS_DIR + "rooms/mtclibrary", "north" ,0, 0);
    add_exit(MINAS_DIR + "n1crc5",           "east"  ,0, 1);

    set_extraline("The street ends here, as the steep slopes of Mount "
      + "Mindolluin form a wall to the west. East the street continues. "
      + "To the north stands an ancient impressive stone building. A "
      + "short flight of stairs is leading up to the entrance.");

    add_item(({"building", "stone building", "ancient building", }), BSN(
        "The ancient building is built with the back to the outer wall of "
      + "the Fifth Circle. The entrance in the center of the front side "
      + "of the building is the only opening into the building on this side."));

    add_item(({"entrance", "door", }), BSN(
        "The entrance lies seven steps above the street level. A pair of "
      + "two mighty stone columns is standing on both sides of the entrance. "
      + "Resting on the two columns is a balcony on which large letters were "
      + "hewn into the stone."));
    add_item(({"stairs", "flight", "steps", }), BSN(
        "A short flight of seven steps made from massive black stone slabs "
      + "is leading up to the entrance."));
    add_item(({"column", "columns", "pair of columns", "stone columns"}), BSN(
        "On each side of the entrance is standing a mighty stone column. "
      + "Resting on the columns and roofing the entrance is a balcony on "
      + "which large letters were hewn into the stone."));
    add_item(({"balcony", "letter", "letters"}), read_letters());
    add_cmd_item(({"balcony", "letter", "letters"}), "read", read_letters());

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

