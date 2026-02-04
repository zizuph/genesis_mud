/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * cave03.c
 *
 * Red Dragon Lair
 * Tomas  -- Dec. 1999
 */

#include "/d/Terel/include/Terel.h"
inherit MOUNTAIN_DIR + "redlair/cave_room";
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>

int opendoor = 0;
int unlock_door(string str);
object key;


public void
close_door()
{
    if (opendoor == 1) 
    {
       tell_room(this_object(), "The northern wall shimmers slighty " +
          "as the exit northeast disappears.\n");
       remove_exit("northeast");
       opendoor = 0;
    }
    return;
}


/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();

    set_long(query_long() +
             "The path decends deeper into the cave towards the southeast.\n");
    
    DARK;

    add_item(("grooves"),"You notice what looks like a rough impression " +
       "of a human hand in one of the grooves.\n");

    add_item(("impression"),"It looks like someone carved out a rough " +
        "impression of a hand in the groove.\n");

    add_exit(MOUNTAIN_DIR + "redlair/cave02", "northwest");
    add_exit(MOUNTAIN_DIR + "redlair/cave04", "southeast");

    reset_room();
}


void init()
{
    ::init();
       add_action(unlock_door,"press");
       add_action(unlock_door,"place");
       add_action(unlock_door,"push");
} 

int
unlock_door(string str)
{

   
   if((str == "hand on impression") || (str == "hand in impression") || (str == "hand in indentation")) 
     { 
       if(present("terel:severed_hand", TP))
        {
           key=present("terel:severed_hand", TP);
           write("The rock wall shimmers slightly revealing " +
               "a tunnel to the northeast " +
               "as you press the " + key->short() + 
               " against the impression.\n");
         say(QCTNAME(TP) + " presses something against " +
            "the northern rock wall. The wall shimmers slightly " +
            "revealing a dark tunnel leading northeast.\n");
         opendoor=1;
         add_exit(MOUNTAIN_DIR + "redlair/hideout/shaft01", "northeast");
         set_alarm(20.0, 10.0, close_door);

         write_file(TEREL_DIR + "log/severed_hand",
            TP->query_name()+" " + ctime(time()) + "\n");
         return 1;
        }
         write("You press your hand against the impression, but nothing happens.\n");
         say(QCTNAME(TP) + " presses " +HIS_HER+ " hand against " +
            "the wall.\n");
         return 1;
     }
     else
     {
        write("Place hand on what?\n");
        return 1;
     }
      return 0;
}






/*
 * Function name: smell_desc
 * Description:   What does the air smell like here?
 * Returns:       The description of the smell
 */ 
public string
smell_desc()
{
    return "The air smells stale. There is a trace of sulphur here as well.\n";
}


public string
touch_desc()
{
    return "The walls feel a little warmer than the room to the northwest.\n";
}

