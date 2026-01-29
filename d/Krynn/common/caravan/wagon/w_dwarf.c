
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
    return "simple low wagon";
}

public string
carriage_long()
{
    string  long_descf;

   long_descf ="It's a simple and low wagon. There are four sets of small "+
               "and well crafted wooden wheels. You would consider this "+
               "a case on wheels if it wasnt for the small windows and the "+
               "broad door. You guess this wagon designed for a person of "+
               "low status - physically. The materials and design only reveals "+
               "that whoever owns this wagon cares for effecient simplicity "+
               "and good craftsmanship.\n";

   return long_descf;
}



void
create_krynn_wagon()
{

    add_name( ({ "simple low wagon" }) );
    set_adj(({ "simple", "low" }));
    set_pshort( "simple low wagons" );

}


public void
create_default_rooms()
{
    add_mapping (R_LEFT, DEFAULT_LEFT);
    add_mapping (R_RIGHT, DEFAULT_RIGHT);
    add_mapping (R_FRONT, DEFAULT_FRONT);
    add_mapping (R_BACK, DEFAULT_BACK);
    add_mapping (R_WAGON, (( { WAGON + "wr_dwarf", 0 } )) );

}

string
wheels()
{
    string str;

    str =   "Four sets of small crafty wheels carry this metal case through the terrain.\n";

    return str;
}

string
windows()
{
    string str;

    str =   "A pair of small windows with frames of oakwood.\n";

    return str;
}

string
horse()
{
    string str;

    str =   "A pair of strong black ponies pull the wagon forth. They seem very strong "+
            "and reliable.\n";

    return str;
}

string
driver()
{
    string str;

    str =   "A small broadchested dwarf wearing a leather cloak and apron. Sitting on top "+
            "of the wagon, he is holding the reins.\n";

    return str;
}

string
materials()
{
    string str;

    str =   "Mostly wooden planks with a touch of good craftsmanship.\n";

    return str;

}

string
door()
{
    string str;

    str =   "Its a low thick door made of wood. It bears a seal of a dwarven hammer.\n";

    return str;

}


public int
add_room_items()
{

    add_global_item("driver" , driver);
    add_global_item(({"materials","walls","case"}), materials);
    add_global_item("wheels", wheels);
    add_global_item(({"window", "windows"}), windows);
    add_global_item(({"pony", "ponies"}), horse);
    add_global_item("door", door);

}


void
init()
{
    ::init();
}

