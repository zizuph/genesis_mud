/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * ribos_road.c
 *
 * A generic road room.
 * Shinto 12-13-99
 *
 *  Modified: 3 May 2003, by Bleys
 *      - fixed a typo or two
 *
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

/*
 * Function name: init
 * Description:   Add the 'command items' of this object.
 */
init()
{
    ::init();
    add_action("do_smell", "smell");
}

/*
 * Function name: do_smell
 * Description:   Handle the smell action
 * Returns:       1/0
 */
public int
do_smell(string what)
{
    string poss, str, *smells;
    object *ob;
    int i;

    ob = all_inventory(TO);
    poss = POSSESSIVE(TP);
    smells = ({"pine trees", "oak trees", "cedar trees"});
    for (i = 0; i < sizeof(ob); i++) {
    if (living(ob[i]) && !ob[i]->query_wiz_level() && ob[i] != TP) {
        smells += ({QTNAME(ob[i])});
    }
    }
    str = "You inhale deeply through your nose, and recognise the " +
    "smell of ";
    TP->catch_msg(str + smells[random(sizeof(smells))] + ".\n");
    say(QCTNAME(TP) + " inhales deeply through " + poss + " nose.\n");
    return 1;
}

public void
create_room()
{
    set_short("west road");
    set_long("You are travelling on a dirt road that heads east and " +
        "west. The Silver Forest borders the north side of the road, " +
        "and the Enchanted Forest borders the south. This road " +
        "connects the town of Ribos to the west and Calathin to " +
        "the east. ");

    add_item(({"trees", "tree", "oak tree", "oak trees", "cedar trees",
               "cedar tree", "pine tree", "pine trees"}),
        "The trees surround the road on the "+
        "north and south sides, where they expand into the Silver " +
        "and Enchanted Forests.\n");
    add_item(({"silver forest", "Silver forest", "Silver Forest",
               "silver Forest"}),
        "The Silver Forest expands out to the north, blanketed by the " +
        "crisp, brilliantly sparkling snow which gives it its name.\n");
    add_item(({"enchanted forest", "Enchanted Forest",
               "Enchanted forest", "enchanted Forest"}),
        "The Enchanted forest spreads out to the south of the road. "+
        "The forest is said to be inhabited by magical creatures.\n");
    add_item(({"forest", "forests"}),
        "Which forest, the Silver Forest or the "+
        "Enchanted Forest?\n");
    add_item(({"road", "dirt road"}),
        "A road of dirt with small rocks scattered here and there.\n");

    add_item(({"rocks", "small rocks"}),
        "Small rocks are strewn about the road in various places. More "+
        "than likely, the cold climate here has brought them to the "+
        "surface.\n");
}
