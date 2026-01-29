
/*
 *  Filename:       w_prison.c
 *  Description:    This is a wagon for a typical caravan transport.
 *
 *  Copyright (c) Sep. 2003 by Peter Bech Lund, aka. Vencar of Krynn
 *
 *  Change log:
 */

inherit "/w/vencar/caravan/wagon/wagon";

#include "wagon.h"


public string
carriage_short()
{
    return "white wooden wagon";
}

public string
carriage_long()
{
    string  long_descf;

   long_descf ="It's a hard wooden case on wheels. It appears more luxurious "+
               "than most wagons you'd see on the roads these days. With the "+
               "large crests on both sides of the wagon it becomes obvious it is "+
               "a wagon belonging to the Knighthood of Solamnia. Slender windows "+
               "and a tall door are the most significant features to the outside "+
               "of this heavy passenger wagon.\n";

   return long_descf;
}


void
create_krynn_wagon()
{

    add_name( ({ "white wooden wagon" }) );
    set_adj(({ "white", "wooden" }));
    set_pshort( "white wooden wagons" );

}


public void
create_default_rooms()
{
    add_mapping (R_LEFT, DEFAULT_LEFT);
    add_mapping (R_RIGHT, DEFAULT_RIGHT);
    add_mapping (R_FRONT, DEFAULT_FRONT);
    add_mapping (R_BACK, DEFAULT_BACK);
    add_mapping (R_WAGON, (( { WAGON + "wr_kofficer", 0 } )) );

}

string
driver()
{
    string str;

    str = "A tall man who appears to have seen his time of military service as well.\n";

    return str;
}



string
walls()
{
    string str;

    str = "The walls are constructed from white planks of what could be birch.\n";

    return str;
}

string
itemcase()
{

    string str;

    str = "It's what you would call a very small wooden house on wheels. White walls, "+
          "slender windows and a door.\n";

    return str;
}

string
wheels()
{

    string str;

    str = "Large wooden wheels with steel nailings and reinforcement. \n";

    return str;

}

string
windows()
{
    string str;

    str = "Slender windows, tall and proud gives you a glimpse of a sparse yet "+
          "grand furnishing. \n";

    return str;

}

string
door()
{
    string str;

    str = "It's a tall white door that allows passage into the white wagon. \n";

    return str;

}

string
crests()
{
    string str;

    str = "These marvel crests are expertly crafted and with gleaming colours "+
          "depicting the symbols for the Orders of the Knighthood of Solamnia: "+
          "Crown, Sword, Rose and Kingfisher. With large gilded letters a script "+
          "beneath each crest states: My Honour is My Life! \n";

    return str;

}




public int
add_room_items()
{

    add_global_item("driver", driver );
    add_global_item(({"walls", "sides"}), walls);
    add_global_item(({"case", "house"}), itemcase);
    add_global_item("wheels", wheels);
    add_global_item("windows", windows);
    add_global_item("door", door);


}


void
init()
{
    ::init();
}

