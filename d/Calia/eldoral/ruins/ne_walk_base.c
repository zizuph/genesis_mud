#pragma strict_types

#include "defs.h"

inherit STDROOM;

string extra;

public void
create_walk(string str)
{
    int index = wildmatch("*west", str);

    if (!extra)
        extra = "";

    set_short("atop a walkway above the " + str + " edge of " +
        "a courtyard");
    set_long("You are on the " + str + " portion of a " +
        "walkway that overlooks the northeast " +
        "courtyard of the ruins of Castle Chimera on " +
        "the south and west edges, high atop the " +
        "walls on those sides. Below, " +
        "the courtyard covers a wide region " +
        "approximately square in shape, bound on all " +
        "sides by high walls. In the center of " +
        "the courtyard, a dozen black stone pillars " +
        "stand in a circular formation on the ground. " +
        extra + "\n\n");

    add_item(({"courtyard"}),
        "The courtyard spreads out below you, extending " +
        "from the foot of the wall out to the northeast-" +
        "most corner of the ruins. In the center of the " +
        "courtyard, a dozen black stone pillars stand " +
        "around a strange pattern on the courtyard floor.\n");
    add_item(({"pillars"}),
        "They don't seem to depict anything, just simple " +
        "stone columns carved from black stone.\n");
    add_item(({"pattern"}),
        "In the heart of the courtyard, a strange pattern " +
        "that doesn't seem to have any obvious meaning " +
        "rests on the ground. You think you can almost " +
        "make sense of it, but you're not quite at the " +
        "right angle.\n");
    add_item(({"walls", "courtyard walls"}),
        "The square courtyard is bounded by tall walls " +
        "on the north, east, south and west sides. Of " +
        "those, the north and east appear to be outer " +
        "walls, judging from the mist-enshrouded trees " +
        "on the other side. The other walls serve to " +
        "separate the courtyard from the rest of the " +
        "ruins.\n");
    add_item(({"forest", "trees", "mist-enshrouded trees"}),
        "Beyond the outer walls to the north and east of " +
        "the courtyard, and ancient forest rises into " +
        "the sky. The uppermost branches are concealed " +
        "in thick mist, as is the extent of the forest, " +
        "you can't see more than a dozen or so trees " +
        "back from the forest edge.\n");
    add_item(({"walkway"}),
        "You're on it, dummy!\n");

}
