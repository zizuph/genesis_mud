/*
 * Clyptas - August 2017
 */
 
#pragma strict_types

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "defs.h"

#define PATH "/d/Faerun/menzo/rooms/camp/tunnel1"
 
inherit "std/room";
 
public void
create_room()
{
    
    //0 means outdoors, and 1 means indoors for this prop
    add_prop(ROOM_I_INSIDE, 0);
    
    set_short ("A hidden trail leading deeper into the forest.\n");

    set_long("You follow the trail to the north, leaves and twigs snapping " +
         "beneath your feet. The trail seems to stop here unexpectedly at " +
         "base of a very high cliff.\n");
    
    add_item(({"underbrush","undergrowth","briars","nettles","leaves"}),
        "The underbrush grows scarce here.\n");
   
    add_item(({"trail","path"}),
        "The trail is well worn, as if it's been used many times.\n");
    
    add_item(({"brush"}),
        "The underbrush is strewn over the path, to make the path hidden.\n");
    
    add_item(({"cliff"}),
        "The cliff face is tall and looms high above you. You notice though, " +
        "that it seems to cast an irregular shadow over the ground.\n");
        
    add_item(({"shadow"}),
        "The shadow seems to flicker in the light, perhaps there is more to " +
        "the rock than meets the eye.\n");
        
    add_item(({"rock","wall","cave"}),
        "You peer closer at the rock and it flickers slightly before you, " +
        "through the illusion you see a deep cave looming up in front of " +
        "you.\n");
        
    add_exit(CAMP_DIR + "hidden_trail1","south");
    add_exit(CAMP_DIR + "tunnel1", "north", 0, 1, 1);
}
void

init()
{
    ::init();
    add_action("do_enter","enter");
}

public string
do_search(object pl, string arg)
{
    if (IN_ARRAY(arg,
        ({ "cliff", 
           "cave",
		   "rock",
		   "wall",}) ) == 0)
    {
        return "Your search reveals nothing special.\n";
    }

        return "The image of the rock wall seems almost " +
		     "transparent.\n";

}

public int
do_enter(string str)
{
    if(!strlen(str))
    {
        notify_fail("What did you wish to enter?\n");
        return 0;
    }

    if (!parse_command(str, ({}),
        " [in] [through] [into] [the] [dark]"
      + " [looming] 'cave'"))
    {
        notify_fail("Enter what? The cave?\n");
        return 0;
    }

    write("You step through the image of rock and find yourself in a dark " +
	     "cave.\n");
    tell_room(this_object(), QCTNAME(this_player()) + " arrives through the " +
        "image of a cliff into a deep, dark cave.\n");
    tell_room(PATH, QCTNAME(this_player()) + " arrives " +
        "through the illusion.\n");
    this_player()->move_living("M", PATH, 1, 0);
    return 1;
}