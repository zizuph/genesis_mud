/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * ne_path.c
 *
 * A generic room for the northeastern path off the Dabaay road.
 * Goldberry August 9, 1999
 */

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/include/herb_arrs.h"

inherit STDROOM;
inherit "/d/Terel/std/herbsearch.c";

#define  ONE_OF_LIST(array) ((array)[random(sizeof(array))])


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
    smells = ({"mint", "blueberries", "cedar trees", "parsley"});
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
create_terel_room()
{

   
    set_up_herbs( ({ ONE_OF_LIST(ANY_HERBS),
                     ONE_OF_LIST(FOREST_HERBS),
                     ONE_OF_LIST(FOREST_HERBS) }), ({"garden"}) ,  3 );


}
   
