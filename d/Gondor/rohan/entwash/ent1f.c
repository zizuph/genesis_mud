#pragma strict_types

inherit "/d/Gondor/rohan/entwash/entwash.c";

#include <macros.h>
#include <ss_types.h>
#include "/d/Gondor/defs.h"

//  Prototypes
int     crossing();

void
create_swamp()
{
    add_exit(ENTWASH_DIR + "ent1e", "west");
    add_exit(ENTWASH_DIR + "a1", "northwest", crossing, 10);
}

int
crossing()
{
    int diff = 10 + random(10),
        swim = TP->query_skill(SS_SWIM);

    if (diff > swim)
    {
        write("You attempt to swim across the Entwash, but are confounded"
          + " by the current which flows through this narrow channel.\n");
        say(QCTNAME(TP) + " enters the river to swim across, but"
          + " soon returns to shore, wet and dripping.\n");

        return 1;
    }

    write("You enter the cold water, and swiftly swim across the river.\n");
    say(QCTNAME(TP) + " enters the cold water, and swims to the"
      + " northern shore.\n");

    return 0;
}

int
swim_crossing(string str)
{
    if (!strlen(str))
        NFN0("Swim where?");

    if (str != "river" && str != "across river" && str != "entwash"
     && str != "Entwash" && str != "water" && str != "stream"
     && str != "across stream" && str != "nw" && str != "northwest")
        NFN0("Where would you like to swim?");

    TP->command("nw");

    return 1;
}

void
init()
{
    ::init();

    add_action(swim_crossing, "swim");
}
