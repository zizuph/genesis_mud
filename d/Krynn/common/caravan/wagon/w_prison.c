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

object door,door2;

public string
carriage_short()
{
    return "steel cage wagon";
}

public string
carriage_long()
{
    string  long_descf;

   long_descf ="It's a cage on top of a steel construction dragged by a " +
               "single white horse, the bars on the cage are thicker than " +
               "normal bars, and are formed into a cubic form that makes " +
               "room for only a few prisoners inside the cage.\nThe floor " +
               "of the cage are metal bars too, making travels quite " +
               "uncomfortable for those inside it. In the front side, " +
               "there is a metal grid forming a door.\n";

   return long_descf;
}

string
cage()
{
    string str;

    str = "The cage are made of steel, making it practically impossible " +
          "to break through, it is made in a design that publically " +
          "shows who the condemned are, displaying him in a fashion " +
          "so that everyone can get a good look on them.\nIt is also " +
          "very uncomfortable, as one have to stand with a foot on " +
          "each of two bars or sit across them hurting the backside, " +
          "draining the willpower of the condemned.\n";

    return str;
}

string
driver()
{
    string str;

    str = "You find no driver.\n";

    return str;
}

void
create_krynn_wagon()
{

    add_name( ({ "steel cage wagon" }) );
    set_adj(({ "steel", "cage" }));
    set_pshort( "steel cage wagons" );

}


public void
create_default_rooms()
{
    add_mapping (R_LEFT, DEFAULT_LEFT);
    add_mapping (R_RIGHT, DEFAULT_RIGHT);
    add_mapping (R_FRONT, DEFAULT_FRONT);
    add_mapping (R_BACK, DEFAULT_BACK);
    add_mapping (R_WAGON, (( { WAGON + "wr_prison", 0 } )) );

}

public int
check_enter_wagon(string str)
{

    if (door2->query_open())
    {
        return 1;
    }
    else
    {
        NF("Enter through a closed door?\n");
        return 0;
    }

}

public int
check_leave_wagon(string str)
{

    if (door->query_open())
        return 1;
    else
    {
        write("Leave through a closed door?\n");
        return 0;
    }

}


public int
add_room_items()
{

    add_global_item("driver" , driver );
    add_global_item(({"cage", "floor"}), cage);

    door2 = clone_object(OBJ + "cagedoor1");
    door = clone_object(OBJ + "cagedoor2");

    door2->make_connection(file_name(query_room(R_WAGON, M_OBJECT)), door);
    door2->move(query_room(R_LEFT,M_OBJECT), 1);

    door->make_connection(file_name(query_room(R_LEFT, M_OBJECT)), door2);
    door->move(query_room(R_WAGON,M_OBJECT), 1);

}


void
init()
{
    ::init();
}

