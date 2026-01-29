/*
 *  Filename:       armoured.c
 *  Description:    This is a special wagon for a typical caravan transport.
 *
 *  Copyright (c) Sep. 2003 by Peter Bech Lund, aka. Vencar of Krynn
 *
 *  Change log:
 */

inherit "/w/vencar/caravan/wagon/wagon";

#include "wagon.h"

object door, door2;

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
check_elves_alive()
{
    return 1;
}

public string
upperslit()
{
    string str;

    if (check_elves_alive())
        str =   "Looking closer at the upper slit you stare right into " +
                "the almond-green eyes of someone. The eyes looks warm " +
                "alive and seems to be searching you for any kind of " +
                "troubles.\n";
    else
        str =   "Looking closer at the upper slit you stare into the " +
                "darkness of the treasury room.\n";

    return str;

}


public string
edge()
{
    string str;

    if (check_elves_alive())
        str =   "You realize you are looking directly at an arrowhead inside " +
                "the lower slit.\n";
    else
        str =   "Not much is seen inside the lower slit.\n";

    return str;
}


public string
slits()
{
    string str;

    if (check_elves_alive())
        str =   "Looking closer at the slits you realize that the upper slit " +
                "are at level with the eyes of an adult, while the lower " +
                "slit seems to have some pointy edge gleaming in the light.\n";
    else
        str =   "Looking closer at the slits you realize that the upper slit " +
                "are at level with the eyes of an adult, while the lower " +
                "slit seems to be at hands height.\n";

    return str;
}


void
create_krynn_wagon()
{
    set_short("heavily armoured steel-clad wagon");
    set_long("It is a wagon clad in heavy steel plates," +
             "with two long narrow slits large enough to peek through " +
             "in both sides of the wagon.\n" +
             "The wagon is heavily armoured making it well protected " +
             "against attacks, pretty good " +
             "for carrying valuable treasury.\n");
    add_name( ({"heavily armoured steel-clad wagon", "steel-clad wagon",
                "heavily armoured wagon" }) );
    set_adj(({"steel","steel-clad", "heavily armoured"}));


}


public int
add_room_items()
{

    /* notice this wagon can't burn... */

    add_global_item(({ "plates", "steel plates" }),
        "The steel conical plates have their tips directed " +
        "away from the wagon. they shines brightly as if they were " +
        "just buffed up.\n");
    add_room_item(({ "slit", "slits" }), slits, R_LEFT);
    add_room_item(({ "slit", "slits" }), slits, R_RIGHT);
    add_room_item(({ "edge", "pointy edge", "lower slit" }),edge, R_LEFT);
    add_room_item(({ "edge", "pointy edge", "lower slit" }),edge, R_RIGHT);
    add_room_item(({ "upper slit" }), upperslit, R_LEFT);
    add_room_item(({ "upper slit" }), upperslit, R_RIGHT);


    door2 = clone_object(OBJ + "armdoor1");
    door = clone_object(OBJ + "armdoor2");

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
