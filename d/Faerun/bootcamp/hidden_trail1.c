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

    set_long("A hidden trail located behind Jarlaxle's tent. It appears to " +
         "hidden quite well, and by someone. The brush is haphazardly placed " +
         "quite possibly to dissuade anyone from going further.\n");
    
    add_item(({"underbrush","undergrowth","briars","nettles","leaves"}),
        "The underbrush is strewn over the path, to make the path hidden.\n");
   
    add_item(({"trail","path"}),
        "The trail is well worn, as if it's been used many times.\n");
    
    add_item(({"brush"}),
        "The underbrush is strewn over the path, to make the path hidden.\n");
        
    add_exit("/d/Faerun/bootcamp/camp1","camp");
    add_exit("/d/Faerun/bootcamp/hidden_trail2","north");
}
