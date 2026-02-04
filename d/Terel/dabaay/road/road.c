/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * road.c
 *
 * A generic road room.
 * Goldberry August 9, 1999
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
    add_item(({"road","dirt road"}),
        "A road of dirt with small rocks scattered here and there.\n");

    add_item(({"rocks","small rocks"}),
        "Small rocks are strewn about the road in various places. More "+
        "than likely, the cold climate here has brought them to the "+
        "surface.\n");
}
