/*
 *  Filename:       w_smith.c
 *  Description:    This is a wagon for a typical caravan transport.
 *
 *  Copyright (c) Okt. 2003 by Peter Bech Lund, aka. Vencar of Krynn
 *
 *  Change log:
 */

inherit "/w/vencar/caravan/wagon/wagon";

#include "wagon.h"


public string
carriage_short()
{
    if (BurnStep == 0)
        return "wooden hardbox wagon";

    return BurnMsg[BurnStep][WAGON_SHORT];

}

public string
carriage_long()
{
    int     s;
    string  long_descf;

   if (BurnStep == 0)
       long_descf = "The wagon is made of common wood found in the northern " +
       "part of krynn, its bed are reinforced with steel plates, making it " +
       "carry heavy cargo. This wagon is covered with a hardbox with a " +
       "small chimney that billows black smoke after the wagon. From inside " +
       "the cabin the sound of steel hitting steel can be heard clanging " +
       "loudly in a ever so beautiful rythm.\n";

    if (BurnStep > 0)
        long_descf = BurnMsg[BurnStep][WAGON_LONG];

   return long_descf;
}

void
create_krynn_wagon()
{

    add_name( ({ "wooden hardbox wagon" }) );
    set_adj(({ "wooden","hardbox" }));
    set_pshort("wooden hardbox wagons" );

}


public void
create_default_rooms()
{
    add_mapping (R_LEFT, DEFAULT_LEFT);
    add_mapping (R_RIGHT, DEFAULT_RIGHT);
    add_mapping (R_FRONT, DEFAULT_FRONT);
    add_mapping (R_BACK, DEFAULT_BACK);
    add_mapping (R_WAGON, (( { WAGON + "wr_smith", 0 } )) );

}



public int
add_room_items()

{

    /* global items are added in left,right,front,back,rooms.
     items can be added to one of those instead with add_xxx_item */

}

void
init()
{
    ::init();
}

