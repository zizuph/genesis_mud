// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/add/r8.c
// creator(s):       unknown
// revisions:        grace april 1995
//                       lilith july 1996
//                       Casca, 11/25/99
//                   Manat, 01/16/01  Made the move to l2/add actually work
// purpose:          
// note:             formerly was n5.c moved to put wolf in a more 
//                      realistic area
// bug(s):           
// to-do:            

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/dark/darkl2_base.c";

/* Include the local area defines, etc */
#include "/d/Avenir/common/dark/dark.h"

#include <tasks.h>


void
init()
{
    ::init();
    add_action("climbledge","climb");
}


/* Now create the room.  */
void
create_tunnel_room()
{
    set_short("cavern");
    set_long("This is a very large natural cavern that somehow feels "+
        "out of place. "+
        "The ceiling is very high, lost in the darkness above you. "+
        "There are animal footprints in the dust here, and loose "+
        "tufts of fur roll about, disturbed by the air of your "+
        "passage. You notice several ledges high up on the walls "+
        "of the cavern.\nYou have an odd feeling about this place.\n");


    add_exit("t10","northwest");

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    add_item(({"wall","walls","cave","caves"}),"The cave rises far "+
        "overhead, meeting the ceiling somewhere in the darkness. "+
        "On the east wall there is a low ledge which opens up to "+
        "the cave. It looks as if it would be easy to climb to. "+
        "Higher up on the north wall is a second ledge, climbing "+
        "to that one could present quite a challenge.\n");
    add_item(({"floor","ground"}),"The ground here is covered with "+
        "dirt and mud in many places, in which you find many prints.\n");
    add_item(({"ceiling","roof","above"}),"The upper reaches of the "+
        "caverns are lost in the darkness and shadows far above.\n");
    add_item(({"prints","paw prints","tracks"}),"There are many prints "+
        "in the dirt and mud of the floor. Most are obscured by time "+
        "and overlapping tracks, but the whole prints you can see "+
        "appear to be that of a large dig or wolf.\n");
    add_item(({"fur","tufts"}),"Balls of golden fur swirl about the "+
        "floor in the gentle wind.\n");

    add_tell("From the edge of vision you see a flash of "+
        "irridescent rainbow-hued light in the darkness above.\n");
    add_tell("A tuft of fur, caught in an eddy of wind, swirls about "+
        "the floor.\n");
    add_tell("A low ghostly howl whispers through the cavern.\n");


    reset_tunnel_room();
}

mixed
climbledge(string str)
{
    if (!str)
    {
        write ("Climb what?\n");
        return 1;
    }

    if ((str=="east wall")||(str=="to first ledge")||
       (str=="to lower ledge")||(str=="to low ledge"))
    {
        write("You slowly work your way up the "+
            "east wall towards the ledge.\n");
        say(QCTNAME(this_player())+ " slowly climbs "+
            "up the east wall to the ledge above.\n");
	set_dircmd("east wall");
        TP->move_living("M", L2 +"add/r9");
        tell_room(environment(this_player()), QCTNAME(this_player()) +
            " appears from over the lip of the ledge.\n", this_player());
        return 1;
    }

    if ((str=="north wall")||(str=="to middle ledge")||
       (str=="to second ledge"))
    {
        write("You slowly climb up the north wall "+
            "to the ledge high above you.\n");
        say(QCTNAME(this_player())+ " slowly climbs "+
            "up the north wall to the ledge above.\n");
	set_dircmd("north wall");
        TP->move_living("M", L2 +"add/r10");
        tell_room(environment(this_player()), QCTNAME(this_player()) +
            " appears from over the lip of the ledge.\n", this_player());
        return 1;
    }

    notify_fail("Climb what? There are a couple of choices.\n");
    return 0;
   
}
