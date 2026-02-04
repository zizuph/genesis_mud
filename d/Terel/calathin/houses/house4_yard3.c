/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * house4_yard3.c
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

public void
create_room()
{
    ::create_room();

    set_short("backyard");
    set_long("The backyard is well maintained. A row of small shrubs " +
       "outline the white graveled path leading east.\n");

    add_item(({"shrubs","shrub"}),
       "Small bushes clipped and pruned to the same proportions. " +
       "The shrubs outline the white graveled path.\n");

    add_item(({"yard","backyard"}),
       "The yard looks well maintained. The snow has been cleared away.\n");
 
    add_item(({"white graveled path","path","gravel","white gravel"}),
       "The path is covered in small white colored stones forming " +
       "the walkway to through the backyard.\n");

    add_exit(CALATHIN_DIR + "houses/house4_yard","east",0,1);
    
    door = clone_object(CALATHIN_DIR + "houses/obj/house4fa_door");
       door->move(TO);


    set_up_herbs( ({ ONE_OF_LIST(ANY_HERBS),
                     ONE_OF_LIST(FROST_HERBS),
                     ONE_OF_LIST(FOREST_HERBS),
                  }),
                  ({"yard","shrubs","shrub"}) , 
                   3 );

    reset_room();


}


void
reset_room()
{    
  
   
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
    smells = ({"mint", "blueberries", "cedar trees", "holly"});
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
