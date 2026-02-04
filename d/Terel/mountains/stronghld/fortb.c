/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 *
 * Dwarven Stronghold
 * Tomas  -- Jan. 2000
 */

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <stdproperties.h>

inherit STDROOM;
inherit MOUNTAIN_DIR + "stronghld/passageway";

/*
 * Function name: init
 * Description:   Add the 'command items' of this object. 
 */
public void
init()
{
    ::init();
    add_action("do_smell",  "smell",  0);
}


/*
 * Function name: smell_desc
 * Description:   What does the air smell like here?
 * Returns:       The description of the smell
 */ 
public string
smell_desc()
{
    return "You smell a faint scent of horses and molten metal.\n";
}

/*
 * Function name: do_smell
 * Description:   Handle the smell action
 * Returns:       1/0
 */ 
public int
do_smell(string str)
{
    NF("Smell what?\n");
    if (!strlen(str))
        return 0;
    
    if (str == "air" || str == "scent" || str == "strange scent") {
        write(smell_desc());
        return 1;
    }
    return 0;
}


public void
create_room()
{
    ::create_room();
    INSIDE;
    set_short("Passageway");
    set_long(query_long() + "The passageway continues west and east. " +
       "To the north smells like the stables. To the south looks like " +
       "the blacksmith shop.\n");

    add_tell("You hear the sounds of hammering coming from the south.\n");

    add_exit(MOUNTAIN_DIR + "stronghld/forta","east",0,1);
    add_exit(MOUNTAIN_DIR + "stronghld/fortd","north",0,1);
    add_exit(MOUNTAIN_DIR + "stronghld/fortc","south",0,1);
    add_exit(MOUNTAIN_DIR + "stronghld/forte","west",0,1);
    
    reset_room();

}


