/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * port_room.c
 *
 * A generic port room.  Most port rooms will inherit this object.
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
    smells = ({
        "salt water", "rotten fish", "your own odour",
        "bilge waste", "an icy ocean breeze", "fresh shellfish"});
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
