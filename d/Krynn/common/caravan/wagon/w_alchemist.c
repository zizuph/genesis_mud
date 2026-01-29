
/*
 *  Filename:       w_alchemist.c
 *  Description:    This is a wagon for a typical caravan transport.
 *
 *  Copyright (c) Feb. 2004 by Peter Bech Lund, aka. Vencar of Krynn
 *
 *  Change log:
 */

inherit "/w/vencar/caravan/wagon/wagon";

#include "wagon.h"


public string
carriage_short()
{
    return "small sturdy wagon";
}

public string
carriage_long()
{
    string  long_descf;

   long_descf ="It's a small sturdy wagon, the walls are of mixed materials "+
               "and the design obviously arcanely gnomish. It has five sets "+
               "of small strong metal wheels. A small drainpipe on the top "+
               "seems to function as a chimney and a peculiar smoke erupts "+
               "from its shining outlet. Also you notice a strange driver "+
               "on the front side. There is one window on each side.\n";

   return long_descf;
}

string
materials()
{
    string str;
    if (query_burnstep())
        return STANDARD_EXA_ITEM_OUTSIDE_BURNING;

    str = "Everything from raw iron to polished silver and puzzling woodsorts. "+
          "Only gnomish engineers would know the purpose and idea of using so many "+
          "and perhaps superfluous materials.\n";

    return str;
}

string
driver()
{
    string str;

    if (query_burnstep())
        return STANDARD_EXA_ITEM_OUTSIDE_BURNING;

    str = "The driver of this wagon seems to be a strange construct. A metal gnome "+
          "that nevertheless control the reins rather tolerably. He is made of bronze "+
          "and gleams slightly. Instead of a seat he is attached directly to the front "+
          "of the wagon.\n";

    return str;
}


string
wheels()
{
    string str;

    if (query_burnstep())
        return STANDARD_EXA_ITEM_OUTSIDE_BURNING  ;

    str = "A composite of steel and granite these small wheels can bear the wagon far "+
          "and wide and across most terrain. Gnomish design at is best and worst.. \n";

    return str;
}


void
create_krynn_wagon()
{

    add_name( ({ "small sturdy wagon" }) );
    set_adj(({ "small", "sturdy" }));
    set_pshort( "small sturdy wagons" );

}


public void
create_default_rooms()
{
    add_mapping (R_LEFT, DEFAULT_LEFT);
    add_mapping (R_RIGHT, DEFAULT_RIGHT);
    add_mapping (R_FRONT, DEFAULT_FRONT);
    add_mapping (R_BACK, DEFAULT_BACK);
    add_mapping (R_WAGON, (( { WAGON + "wr_alchemist", 0 } )) );

}

string
chimney()
{
    string str;

    if (query_burnstep())
        return STANDARD_EXA_ITEM_OUTSIDE_BURNING  ;

    str = "Nothing more than a thin metal pipe on the wagon roof. A curious "+
          "greenish smoke erupts from the outlet. What could be burning, or "+
          "boiling in there...\n";

    return str;
}

string
windows()
{
    string str;

    if (query_burnstep())
        return STANDARD_EXA_ITEM_OUTSIDE_BURNING  ;

    str = "There is a small crystal window on each side. You would have to enter "+
          "to get a clear view of the inside however.\n";

    return str;
}

string
horse()
{
    string str;

    str = "A pair of solemn brown ponies pull this wagon forth. They seem very strong "+
          "and reliable.\n";

    return str;
}



public int
add_room_items()
{

    add_global_item("driver" , driver );
    add_global_item("materials", materials);
    add_global_item("wheels", wheels);
    add_global_item(({"chimney", "drainpipe", "outlet", "smoke"}), chimney);
    add_global_item(({"window", "windows"}), windows);
    add_global_item(({"pony", "ponies"}), horse);

}


void
init()
{
    ::init();
}

