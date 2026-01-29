// file name:        /d/Avenir/common/holm/shore/pool.c
// creator(s):       Lilith, April 97
// revisions:
// purpose:
// note:
// bug(s):
// to-do:

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/inherit/water";

/* Include the local area defines, etc */
#include "../holm.h"

/* For the set_up_herbs() in the room */
#include "/d/Avenir/common/herbs/herbsearch.h"
public string *sea = HERB_MASTER->query_herbs( ({"sea"}) );

public void 
reset_room(void)
{
    set_searched(0);
}

/* Now create the room.  */
public void
create_room(void)
{
    underwater_room();

    set_short("beneath the surface of an intertidal pool");
    set_long("You are at the bottom of an intertidal pool. "+
        "The walls of the dark stone seem to absorb most "+
        "of the light, making it very difficult to see "+
        "clearly.\n");

    add_item(({"walls", "wall", "stone"}), "The walls are "+
        "slick with algae in places.\n");

    add_exit("sh16", "up");

    set_up_herbs(({ ONEOF(sea), ONEOF(sea), ONEOF(sea) }), 
        ({ "walls", "rock", "wall", "algae", "pool", 
           "intertidal pool" }), 5);

    reset_room();
}

