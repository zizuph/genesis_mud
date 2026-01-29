#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_dung.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("A dark narrow corridor");
    set_long("This is a dark narrow corridor below the temple and it " +
        "leads off to the north and south. Both the floor and " +
        "walls are bare. Two small archways lead west " +
        "and southwest into small rooms.\n");

    add_item(({ "archway", "large archway" }),
        "Both archways made of smooth black stones.\n");

    add_item(({ "stones", "black stones", "smooth stones" }),
        "These stones are black and very smooth to the touch. " +
        "They are carved into blocks and placed on top of " +
        "eachother to form archways.\n");

    add_exit( DUNGONE  + "corr7.c", "northeast" );
    add_exit( DUNGONE  + "corr9.c", "south" );
//    add_exit( DUNGONE  + "armoury.c", "west" );
//    add_exit( DUNGONE  + "eqshop.c", "southwest" );

    setuid();
    seteuid(getuid());
    
    clone_object(DOOR + "armoury1")->move(this_object());
    clone_object(DOOR + "eqshop1")->move(this_object());
}
