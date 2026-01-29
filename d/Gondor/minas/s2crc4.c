/*
 *	/d/Gondor/minas/s2crc4.c
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

#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"

private string
read_sign()
{
    return BSN(
        "Which sign to you want to read, the metal plaque to the "
      + "south or the wooden board to the north?");
}

private string
read_board()
{
    return 
        "On the board is painted in large red letters:\n"
      + "\t'Throman the Stone-mason'\n";
}

private string
read_plaque()
{
    return BSN(
        "Looking closer you notice that the plaque is made from "
      + "massive gold. Onto it these words have been etched:")
      + "\t*                                         *\n"
      + "\t                  Sarndil                  \n"
      + "\t                                           \n"
      + "\t            maltaglos ar mirdan            \n"
      + "\t         - Goldsmith and Jeweller -        \n"
      + "\t                                           \n"
      + "\t*                                         *\n";
}

public void
create_street()
{
    set_circle("Fourth");
    set_streetname("Pelargir Street");
    set_areaname("southern");
    set_streettype("alley");
    set_activity(2);
    set_wealth(1);
    add_exit(MINAS_DIR + "rooms/stonemason", "north", 0, 0);
    add_exit(MINAS_DIR + "s1crc4",           "east",  0, 1);
    add_exit(MINAS_DIR + "rooms/jewel_shop", "south", 0, 0);
    add_exit(MINAS_DIR + "alleycrc4",        "west",  0, 1);
    set_extraline("To both sides of the alley are shops. The shop to "
      + "south has a small metal plaque next to the entrance and a "
      + "large wooden board is hanging over the door leading north "
      + "into the other establishment.");

    add_item(({"sign", "signs"}), read_sign());
    add_cmd_item(({"sign", "signs"}), "read", read_sign());

    add_item(({"board", "wooden board", "north sign", "wooden sign"}),
        read_board());
    add_cmd_item(({"board", "wooden board", "north sign", "wooden sign"}),
        "read", read_board());

    add_item(({"plaque", "metal plaque", "gold plaque",
        "golden plaque", "metal sign", "south sign", }),
        read_plaque());
    add_cmd_item(({"plaque", "metal plaque", "gold plaque",
        "golden plaque", "metal sign", "south sign", }),
        "read", read_plaque());

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
