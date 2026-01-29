
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

string colour = "red";

public string
carriage_short()
{
    return "long strong wagon";
}

public string
carriage_long()
{
    string  long_descf;

   long_descf ="This is a long wagon which has been crafted for military "+
               "use. The sides are made from massive beams dyed + colour."+
               "and a tall slender iron plate forms the back. It has two "+
               "sets of strong wheels and it seems to have seen an extended "+
               "use as of late.\n";


   return long_descf;
}


void
create_krynn_wagon()
{

    add_name( ({ "long strong wagon" }) );
    set_adj(({ "long", "strong" }));
    set_pshort( "long strong wagons" );

}


public void
create_default_rooms()
{
    add_mapping (R_LEFT, DEFAULT_LEFT);
    add_mapping (R_RIGHT, DEFAULT_RIGHT);
    add_mapping (R_FRONT, DEFAULT_FRONT);
    add_mapping (R_BACK, DEFAULT_BACK);
    add_mapping (R_WAGON, (( { WAGON + "wr_trooptransport", 0 } )) );

}


string
driver()
{
    string str;

    str = "He is a simple human wearing a farmers hat with a broad brim"+
          "and " + colour + " clothes. \n";

    return str;
}

string
sides()
{
    string str;

    str = "Beams coloured " + colour + " forms the sides of the troop transport.\n";

    return str;
}


string
wheels()
{
    string str;

    str = "Thick oakwood wheels, supported with metal strappings and nails support "+
          "and transport the troop transport across the realms.\n";

    return str;
}



string
horse()
{
    string str;

    str = "A pack of tall strong warhorses clad in light armour pull this wagon forth.\n";

    return str;
}

string
plate()
{
    string str;

    str = "This tall iron plate serves as both a protective backside and shield "+
          "when raised and as a sturdy walking plank for the troops to board "+
          "and disembark the transport when lowered. \n";

    return str;
}



public int
add_room_items()
{

    add_global_item("driver" , driver );
    add_global_item("plate", plate);
    add_global_item("wheels", wheels);
    add_global_item(({"beams", "sides"}), sides);
    add_global_item(({"horse", "horses"}), horse);

}


void
init()
{
    ::init();
}

