#pragma strict_types

#include "defs.h"

inherit NTOWERBASE;

public string
exa_timber()
{
    string str;

    str = "A long timber juts out into the air beyond " +
        "edge of the tower. It looks fairly sturdy, " +
        "but at the same time it's very old. You think " +
        "you might be able to crawl along it, but if " +
        "it breaks under your weight, you're in for a " +
        "long, painful drop. " +
        ((RUIN + "timber")->query_broken() ? "Fortunately, " +
        "the decision's been made for you, the timber " +
        "has broken off and isn't long enough to be " +
        "of any use." : "Interestingly enough, it comes " +
        "quite close to the top of a nearby tree. ") +
        (stringp((RUIN + "timber")->check_break(TP)) ?
        (string)(RUIN + "timber")->check_break(TP) : "") +
        "\n";
    return str;
}
    
public void
create_room()
{
    extra = "The tower ruins come to an abrupt halt " +
        "here, opening into thin air. It appears " +
        "that the tower reached a cliff edge here, " +
        "and the rest of it descended down the face " +
        "of the cliff, leaving this part to empty " +
        "out into space. You notice a long timber " +
        "that juts out beyond the edge of the tower " +
        "towards a nearby tree, however, that tweaks " +
        "your curiousity. ";

    create_tower();

    add_item(({"timber"}), "@@exa_timber");

    add_exit(RUIN + "ntower3", "south");
}

public int
do_crawl(string str)
{
    if (!str || !strlen(str))
        return 0;

    if (parse_command(str, TP, "'across' / 'along' / 'down' [the] " +
        "'timber'"))
    {
        if ((RUIN + "timber")->query_broken())
        {
            notify_fail("The timber's broken off far " +
                "too short for it to be interesting " +
                "enough to break your neck over.\n");
            return 0;
        }
        write("You carefully " + query_verb() + " out " +
            "across the old timber.\n");
        say(QCTNAME(TP) + " carefully " + query_verb() +
            "s out across the old timber.\n");
        TP->move_living("M", RUIN + "timber", 1, 0);
        say(QCTNAME(TP) + " carefully " + query_verb() +
            "s out onto the timber.\n");
        return 1;
    }
    return 0;
}

public void
init()
{
    ::init();
    add_action(do_crawl, "crawl");
    add_action(do_crawl, "climb");
}
