/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * hideout.c
 * 
 * One of the notorious hand cell hideouts
 */

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <macros.h>
#include <stdproperties.h>
#include <language.h>

inherit "/d/Terel/std/room_tell.c";
inherit STDROOM;

#define  DEFAULT   MOUNTAIN_DIR + "redlair/hideout/"


object pebble;



/*
 * Function name: init
 * Description:   Add the 'command items' of this object. 
 */
public void
init()
{
    ::init();
    add_action("do_smell",  "smell",  0);
    add_action("do_touch",  "touch",  0);
    start_room_tells();
}

/*
 * Function name: smell_desc
 * Description:   What does the air smell like here?
 * Returns:       The description of the smell
 */ 
public string
smell_desc()
{
    return "It smells faintly of dust and sulfur.\n";
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


/*
 * Function name: touch_desc
 * Description:   Is the wall warm or cold?
 * Returns:       The description of the temp. of the walls
 */ 
public string
touch_desc()
{
    return "The walls feel cool to the touch.\n";
}

/*
 * Function name: do_touch
 * Description:   Handle the touch action
 * Returns:       1/0
 */ 
public int
do_touch(string str)
{
    NF("Touch what?\n");
    if (!strlen(str))
        return 0;
    
    if (str == "wall" || str == "walls" || str == "the walls") {
        write(touch_desc());
        return 1;
    }
    return 0;
}


/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{

    ::create_room();
    set_short("in an old mine shaft");
    set_long("The old mine shaft appears to have been abandoned " +
             "a long time ago. The shaft floor is littered with " +
             "various sized fallen rocks and deposits of dust. " +
             "Over the years, the wooden support timbers have " +
             "twisted and sagged under the massive weight of the " +
             "solid rock ceiling above. ");

    set_tell_time(500 + random(200));

    add_item(({"shaft", "mine shaft"}),
             "The mine shaft looks very old and in big need of " +
             "repair.\n");
    add_item(({"darkness"}),
             "A dark black void. You cant see anything beyond.\n");
    add_item(({"shaft floor", "floor","ground"}),
         "The floor is littered in various sized rocky debris. " +
         "Large deposits of dust built up over the years blankets " +
         "everything.\n");
    add_item(({"rocky debris","debris","rocks"}),
       "The floor is littered with various sized rocks fallen " +
       "from the ceiling above.\n");
    add_item(({"deposits","dust"}),
       "Deposits of dust collect around the rocks,support beams " +
       "and the shaft floor. You notice several manmade boot " +
       "prints on the dusty floor\n");
    add_item(({"footprints","prints","boot prints"}),
       "You notice several boot prints on the dusty floor.\n");
    add_item(({"ceiling"}),"The rocky ceiling above is held at bay " +
       "by several wooden support beams spaced evenly throughout " +
       "the shaft.\n"); 
    add_item(({"wooden support beams","wood","support beams","beams"}),
       "The thick beams appear twisted and have splintered over the " +
       "years. Most sag under the constant pressure from the ceiling " +
       "above. You hope that they hold a little while longer.\n");
    add_item(({"walls","wall"}),"The walls rocky surface appear to be " +
       "marred by manmade tools.\n"); 
    add_tell("The wooden support beams creak and groan as the ceiling shifts.\n");
    add_tell("Dust falls from the ceiling.\n");

    add_cmd_item(({"rocks","rock","pebble","pebbles"}),
                 ({"collect","gather","get"}),"@@get_pebble");
    INSIDE;
}


get_pebble()
{
    object pebble;

    seteuid(getuid(TO));
    pebble = clone_object(CALATHIN_DIR + "houses/obj/pebble");
    pebble->move(TP);
    write("You pickup a pebble from the ground.\n");
       say(QCTNAME(TP) + " reaches down and picks up a pebble.\n");
    return 1;
}