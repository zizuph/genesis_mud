/*
 * XXX DEBUGGING VERSION 
 */

#pragma strict_types

inherit "/d/Gondor/common/lib/town";

#include "/d/Gondor/defs.h"

public int     testopen();

/*
 *      Global variables:
 */
static int     Flag;
static string  Desc;

static string
read_sign()
{
    if (Flag)
        return "The sign reads:\n" + 
            break_string("The Sleeping Stallion is temporarily " +
                "closed due to an attack" +
                (strlen(Desc) ? " by " + Desc : "") +
                ".\n",50,"\t") + "\tFastred, Innkeeper\n";
    else
        return "The sign reads: \n\n"
            + "\tWelcome to the Sleeping Stallion!\n"
            + "\t      Open day and night!\n"
            + "\t      Fastred, Innkeeper\n";
}

public void
change_sign(int flag, string desc = 0)
{
    Flag = flag;

    if (Flag && strlen(desc))
        Desc = desc;
    else
        Desc = 0;
}

public void
create_room() 
{
    set_hillside("north");
    set_height(3);
    set_road(2);
    set_density(3);
    set_extraline("On the west side of the staircase, a little "
        + "stream is rushing downhill in a nice little canal made of "
        + "stone. To your east there is a big wooden house. That is "
        + "'The Sleeping Stallion', the local inn, and to the west "
        + "lies the Bank of Edoras. The stairs lead up to a square to "
        + "the south and downwards towards another square to the north.");
    add_exit(EDORAS_DIR + "square2", "south", 0);
    add_exit(EDORAS_DIR + "square1", "north", 0);
    add_exit(EDORAS_DIR + "edbank",  "west",  testopen);

    make_the_room();

    add_item(({"canal","little canal","stream","little stream","river"}),
        BSN("The little stream splashes and bubbles on its way to the "
            + "Snowbourne, which runs along just outside town. The "
            + "water is cold and clear."));

    add_item("sign", read_sign);
    add_cmd_item("sign", "read", read_sign);

    clone_object(EDORAS_DIR + "rooms/DBGinndoorout")->move(TO);
}

public int
testopen() 
{
    object  clock = find_object(CLOCK);
    string  time = clock->query_time_of_day();

    switch (time)
    {
    case "evening":
    case "night":
    case "early morning":
        write("The bank is closed in the "+time+", come back in the daytime.\n");
        return 1; 
    default:
        return 0;
    }
}
