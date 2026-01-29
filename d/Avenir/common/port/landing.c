// Bazaar Street4 (/d/Avenir/common/port/landing.c)
// creator(s):	Lilith Jun 2004. 
// last update: 
// purpose:
// note:
// bug(s):
// to-do:

inherit "/std/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "port.h"
#include "/d/Avenir/include/relation.h"

void
create_room()
{
    add_exit(BAZAAR +"intr/innroom", "south", 0 , 2);
    add_exit("/d/Avenir/common/clubs/dance/clubroom", "north", "@@test_north");
    add_exit(BAZAAR +"intr/inn", "down", 0 , 2);

    set_short("stairwell landing");
    set_long("This is a shadowy stairwell above the great hall of the "+
        "Stormy Haven Inn and Pub. South of here is the guest room "+
        "for visitors to Sybarus. From what you can see, it is a "+
        "fairly comfortable and simple lodging. North you can see "+
        "very little, but you can smell the scents of citrus and "+
        "sandalwood.\n");
   reset_room();
   
   IN
}

int
test_north()
{
    if (IS_SYBARITE(this_player()))
        return 0;
    if (IS_DANCER(this_player()))
        return 0;
    if (IS_MUMMER(this_player()))
        return 0;
    else
        write("A voice shouts: Outlanders use the south room!\n");
    return 1;
}
