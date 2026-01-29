
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
    return "brown wooden wagon";
}

public string
carriage_long()
{
    string  long_descf;

   long_descf ="It's a hard wooden case on wheels. It appears a bit more "+
               "luxurious than most wagons you'd see on the roads these days. "+
               "It has a small set of thick windows on all sides and a heavy "+
               "wooden door marks the entrance to this passenger carriage.\n";

   return long_descf;
}


void
create_krynn_wagon()
{

    add_name( ({ "brown wooden wagon" }) );
    set_adj(({ "brown", "wooden" }));
    set_pshort( "brown wooden wagons" );

}


public void
create_default_rooms()
{
    add_mapping (R_LEFT, DEFAULT_LEFT);
    add_mapping (R_RIGHT, DEFAULT_RIGHT);
    add_mapping (R_FRONT, DEFAULT_FRONT);
    add_mapping (R_BACK, DEFAULT_BACK);
    add_mapping (R_WAGON, (( { WAGON + "wr_dofficer", 0 } )) );

}

string
driver()
{
    string str;

    str = "Dressed in noble +colour+ clothing he seem to take his job quite "+
          "seriously.\n";

    return str;
}

string
walls()
{
    string str;

    str = "The walls are crafted out of wooden planks and painted in a brownish hue.\n";

    return str;
}

string
itemcase()
{

    string str;

    str = "It's what you would call a very small wooden house on wheels. Brown walls, "+
          "small thick windows and a door.\n";

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

    str = "Some sort of reinforced crystral serves as very protective "+
          "windows.\n";

    return str;

}

string
door()
{
    string str;

    str = "It's a thick wooden door with a large symbol of the Dragon Armies. \n";

    return str;

}

public int
add_room_items()
{

    add_global_item("driver" , driver);
    add_global_item(({"walls", "sides"}), walls);
    add_global_item("door", door);
    add_global_item(({"window","windows"}), windows);
    add_global_item("wheels", wheels);
    add_global_item("case", itemcase);


}


void
init()
{
    ::init();
}

