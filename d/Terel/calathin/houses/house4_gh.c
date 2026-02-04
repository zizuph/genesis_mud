/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * house4_gh.c  -- greenhouse
 * Calathin external house.
 * 09/30/1999 -- TOMAS
 */

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/include/herb_arrs.h"

#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>

inherit STDROOM;
inherit "/d/Terel/std/herbsearch.c";

#define SE_HERBS  ({ (HERB_DIR + "blueberry"),\
                     (HERB_DIR + "holly"),\
                     (HERB_DIR + "mint"),\
                     (HERB_DIR + "attanar"),\
                     (HERB_DIR + "suranie"),\
                     (HERB_DIR + "blung"),\
                     (HERB_DIR + "catnip"),\
                     (HERB_DIR + "frostheal"),\
                     (HERB_DIR + "sumac"),\
                  })

#define  ONE_OF_LIST(array) ((array)[random(sizeof(array))])


#include <stdproperties.h>

object door;
object gardener = 0;

public void
create_room()
{
    ::create_room();
    INSIDE;

    set_short("greenhouse");
    set_long("The greenhouse is well maintained as are " +
       "the plants contained within.\n");

    add_item(({"plants","plantlife","plant"}),
       "Various plants grow here. Some are marked as edible " +
       "others for show.\n");

    add_item(({"walls","glass","glass panes","panes"}),
       "The walls and ceiling are made of large glass panes.\n");
 
    add_cmd_item(("glass"),"break","You decide that breaking the glass " +
       "is rather childish for one so mighty such as yourself.\n");


    door = clone_object(CALATHIN_DIR + "houses/obj/house4_gha_door");
       door->move(TO);

    set_up_herbs( ({ ONE_OF_LIST(SPICE_HERBS),
                     ONE_OF_LIST(GARDEN_HERBS),
                     ONE_OF_LIST(GARDEN_HERBS),
                  }),
                  ({"plants","plantlife","plant"}) , 
                   3 );


    reset_room();

}


void
reset_room()
{    
  
    if(!gardener)
    {
       gardener = clone_object(CALATHIN_DIR + "houses/npc/gardener");
       gardener->move(TO);
   
    }
}

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
    smells = ({"mint", "blueberries", "parsley"});
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

