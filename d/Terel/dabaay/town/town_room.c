/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * town_room.c
 *
 * A generic town square room.  Most rooms Dabaay will inherit this object.
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
    smells = ({"salt water", "rotten fish", "your own odour"});
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
    add_item(({"smell","odour","scent"}),
        "There are several distint odours in the air.\n");

    add_item(({"ships","boats"}),
        "You can see several ships tied to the piers at the "+
        "cove of the bay. Farther in the distant east, you can "+
        "see some more ships sailing or swinging at anchor.\n");

    add_item(({"bay","cove"}),
        "The town wraps around a bay that opens to the east. "+
        "You can see several ships out on the waters.\n");

    add_item(({"shops","pubs","inns"}),
        "All around the town, you can make out the bustling "+
        "business places of shops, pubs, inns, and more.\n");
}
