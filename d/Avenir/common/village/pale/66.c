// file name: d/Avenir/common/village/pale/01.c
// creator(s): Lilith June 2004
// last update:
// purpose:    A base for all the pales to be build off of
// note:	
// bug(s):
// to-do:       

#pragma strict_types

#include "../village.h"  
inherit PALE_BASE;

void create_pale_room()
{
    set_short("a room in a pale");
    set_long("This is the long for room 00"+
        " "+
        " "+
        " "+
        " "+
        " "+
        " "+
        ".\n");
       
    add_exit(PALE + "","north", 0);
    add_exit(PALE + "","east", 0);
    add_exit(PALE + "","west", 0);
    add_exit(PALE + "","south", 0);

    add_exit(PALE + "","northwest", 0);
    add_exit(PALE + "","northeast", 0);
    add_exit(PALE + "","southeast", 0);
    add_exit(PALE + "","southwest", 0);

    // See base file for functionality
    add_exit_views();

} // create_room()

