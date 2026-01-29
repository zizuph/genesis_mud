// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/c4.c
// creator(s):       Casca, 11/13/99
// revisions:
// purpose:
// note:           
// bug(s):
// to-do:

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/dark/albus_base.c";
inherit "/d/Avenir/inherit/avenir_time";

/* Include the local area defines, etc */
#include "/d/Avenir/common/dark/dark.h"  
#include "/d/Genesis/gems/gem.h"

/* Now create the room.  */
void
create_albus_room()
{
    set_short("Southern wall");
    set_long("You are near the southern wall of a large, dimly "+
        "lighted cavern. There are several campfires scattered "+
        "about this section, and near them, small tents and "+
        "piles of bedding material.\n");

    add_exit("c2", "northeast");
    add_exit("c8", "northwest");
    add_exit("c3", "east");
    add_exit("c5", "north");


    /*
     * Put additional add_items below. 
     */


    add_cavern_room();
       /* start the call_out - it also automatically updates the time */
        start_avtime();

    reset_albus_room();
}

void
reset_albus_room()
{
    object    ob;
    int i;

    i = get_avenir_hour();

    switch (i)
    {
        case 0 .. 2:
            ob = RANDOM_GEM_BY_RARITY(GEM_RARE);      break;
        case 3 .. 4:
            ob = clone_object(HOLM + "wolf/pelvic");  break;
        case 5 .. 6:
            ob = clone_object(HOLM + "wolf/toe");     break;
        case 7 .. 12:
            ob = clone_object(DARK +"obj/t_torch");   break;
    }

    ob->move(this_object(), 1);          
}