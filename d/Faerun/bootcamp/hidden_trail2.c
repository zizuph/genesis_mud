/*
 * Clyptas - August 2017
 */
 
#pragma strict_types

#include "/d/Faerun/defs.h"
 
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
        
    add_exit("/d/Faerun/bootcamp/hidden_trail1","south");
    add_exit("/d/Faerun/bootcamp/tunnel1","cave");
}