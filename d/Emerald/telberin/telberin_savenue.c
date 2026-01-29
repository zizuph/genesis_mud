#include "defs.h"

inherit TELBERIN_STREET;

public void
create_south_avenue()
{
}

nomask void
create_telberin_street()
{
    
    set_short("South Avenue");
    set_em_long("You are standing at the wonderful South Avenue. "+
        "The South Avenue leads north through two of Telberin’s famous gardens. "+
        "The long expanse of South Avenue draws your attention and you look down "+
        "its length to see the great buildings of the Royal Circle.\n");

    add_item(({"south avenue", "avenue"}),
        "You look closer at the South Avenue and find it to be very wide and "+
        "it stretches to the north in a seamless pattern of cobblestones. "+
        "The street is warm and inviting, calling you down its path to "+
        "experience the many treasures that await you.\n");

    add_item(({"buildings", "building", "great buildings"}),
        "From here you can see the beautiful buildings in the Royal Circle "+
        "rising majestically toward the sky and you are filled with awe at "+
        "such architecture.\n");


    add_item(({"fruit", "fruits", "fruit garden"}),
        "You can see the tops of tall trees bursting above the tall hedges "+
        "that surround the lovely fruit garden. You can also see many "+
        "different size, shapes and colors of fruit hanging from their "+
        "limbs.\n");

    add_item(({"royal circle"}),
        "Royal Circle is the center of the city where the Palace, "+
        "Keepers of Telberin, Temple, and other government buildings are. "+
        "The road that surrounds the Royal Circle bares the same name.\n");

    add_item(({"ri circle"}),
        "The Ri Circle is the main road that runs through all four quarters of "+
        "Telberin. It is made from cobblestones and you can reach the many shops "+
        "that are open.\n");

    
create_south_avenue();
}
