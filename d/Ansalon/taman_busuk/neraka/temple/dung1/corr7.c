#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_dung.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("A dark narrow corridor");
    set_long("This is a dark narrow corridor below the temple. " +
        "It leads off to the south and a stairway can be seen to the " +
        "north. Both the floor and walls are bare. A large archway " +
        "opens up into a circular chamber to the west.\n");

    add_item(({ "archway", "large archway" }),
        "This is a large archway made of carved black stones.\n");

    add_item(({ "stones", "black stones", "carved stones" }),
        "These stones are made of black rock with dark-red veins. " +
        "They are carved into smooth blocks and placed on top of " +
        "eachother to form a large archway.\n");

    add_item(({ "chamber", "circular chamber" }),
        "You would get a better look from inside the room itself.\n");

    add_exit( DUNGONE  + "stair0.c", "north" );
    add_exit( DUNGONE  + "corr8.c", "southwest" );

    setuid();
    seteuid(getuid());
    
    clone_object(DOOR + "labbey1")->move(this_object());
//    add_exit( DUNGONE  + "darkabbey.c", "west" );
}
