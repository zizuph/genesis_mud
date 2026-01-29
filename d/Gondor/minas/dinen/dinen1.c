/*
 *  /d/Gondor/minas/houses/dinen1.c
 *
 *  The Rath Dinen - First part of path.
 *
 *  Alto, 12 April 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define INNER_MINAS "/d/Gondor/minas"


public void
create_gondor()
{
    set_short("The Rath Dinen, near the Fen Hollen");
    set_long("This small path leads down into the Hallows "
        + "of Minas Tirith, where stand the House of Stewards "
        + "and the House of Kings. The Men of Gondor call this "
        + "path the Rath Dinen, or Silent Street. Except in "
        + "times of funeral, only the Lord of the city or those "
        + "bearing the token of the tombs are permitted to walk "
        + "this path. The Rath Dinen leads downhill to the west "
        + "and passes back into the city through the Fen Hollen "
        + "to the east.\n");

    add_exit(INNER_MINAS + "/dinen/dinen2", "west", 0, 0);

    clone_object(INNER_MINAS + "/obj/fenhollenin")->move(TO);

    add_item(({"path", "street", "rath dinen", "silent street"}),
        "Here the path of the Rath Dinen is very narrow and leads "
        + "west in almost a straight line. It is comprised of small "
        + "white pebbles that appear to have come from near the Sea. "
        + "Its surface has been raked smooth, and it looks as though "
        + "no feet have passed this way for some time. The path is "
        + "lined on both sides by a tall hedge.\n");
    add_item(({"pebbles", "white pebbles"}), "You suspect they were "
        + "transported here "
        + "from the Sea, where long years of tossing in the currents "
        + "made them smooth, rounded and white.\n");
    add_item(({"surface"}), "Because there are no footprints in the "
        + "pebbles, you surmise that nobody has walked here for a long "
        + "time. The prospect of violating this sacred place makes "
        + "you feel a little nervous.\n");
    add_item(({"hedge", "tall hedge"}), "It is impossible to tell what "
        + "lies beyond the path because the tall hedge blocks your "
        + "view. It is mildly disconcerting that no birds or other "
        + "creatures can be seen or heard within them.\n");
    add_item(({"hallows", "house of stewards", "house of kings"}),
        "Because of the twisting of the Rath Dinen to the west, in "
        + "concert with the tall hedge blocking your view, you cannot "
        + "see the Hallows from this place. If you are brave enough, "
        + "perhaps you should venture west and have a look.\n");

    reset_room();

}

    




