/*
 *  Filename:       wr_merchant.c
 *  Description:    This is the room on top of the merchant wagon w_merchant.
 *
 *  Copyright (c) Sep. 2003 by Peter Bech Lund, aka. Vencar of Krynn
 *
 *  Change log:
 */

#pragma strict_types
#include "/sys/language.h"
#include "wagon.h"


inherit WAGON_ROOM_INDOOR;


public string
long_desc(string longdesc)
{
    string desc;

    if (!objectp(myWagon))
        return "I don't have a wagon, so I'm buggy.\n";

    switch (myWagon->query_burnstep())
    {
        case 0:
        {
            desc =  "You are on top of " + LANG_ADDART(myWagon->short()) +
                    ", under the dirty canvas.\n" +
                    "The wagon is filled with boxes of different sizes.\n" ;
            break;
        }
        case 1:
        {
            desc =  "You are on top of " + LANG_ADDART(myWagon->short()) +
                    ", under the dirty canvas.\n" +
                    "The wagon is filled with boxes of different sizes.\n " +
                    "The front part of the canvas stretching over the " +
                    "top of the wagon are burning.\n";
            break;
        }
        case 2:
        {
            desc =  "You are on top of " + LANG_ADDART(myWagon->short()) +
                    ", under the wildly burning canvas.\n" +
                    "The wagon is filled with boxes of different sizes, " +
                    "a few of them on fire.\n " +
                    "The canvas are roaring with a fire, sending dark " +
                    "smoke into the air, leaving a smoketrail behind " +
                    "the wagon.\n";
            break;
        }
        case 3..4:
        {
            desc =  "You are on top of " + LANG_ADDART(myWagon->short()) +
                    ". The wagon is entirely engulfed in the flames " +
                    "making it impossible to get a clear look of what or " +
                    "who is in it.\n ";
                  break;
        }
        case 5..100:
        {
            desc = "You are standing in the smouldering remains of what " +
                   "once was a wagon, burned out boxes are littering the " +
                   "ground inside the frame of the wagon.\n";
            break;
        }
    }

    return desc;
}


public string
short_desc(string shortdesc)
{
    string desc;

    if (!objectp(myWagon))
        return "I don't have a wagon, so I'm buggy.\n";

    switch (myWagon->query_burnstep())
    {
        case 0:
        {
            desc =  "Inside the wagon, beneath the canvas";
            break;
        }
        case 1:
        {
            desc =  "Inside the wagon, beneath the burning canvas";
            break;
        }
        case 2:
        {
            desc =  "Inside the wagon, beneath the wildly burning canvas";
            break;
        }
        case 3:
        {
            desc =  "Inside the burning wagon";
            break;
        }
        case 4:
        {
            desc =  "In a wagon in the middle of a fire";
            break;
        }
        case 5..100:
        {
            desc =  "In the the smouldering remains of a wagon";
            break;
        }
    }

    return desc;

}


string
crates()
{
    string str;

    switch (myWagon->query_burnstep())
    {
        case 0..1:
        {
            str = "Boxes are stacked from floor to roof, with different " +
                  "symbols on.\n";
            break;
        }
        case 2:
        {
            str = "Boxes are stacked from floor to roof, with different " +
                  "symbols on, a few of the boxes are on fire.\n";
                  break;
        }
        case 3..4:
        {
            str = "It is impossible to see through the heavy smoke that " +
                  "fills the wagon.\n";
                  break;
        }
        case 5..100:
        {
            str = "Badly scorched boxes, crates burnt out entirely, some " +
                  "black-sooted iron lamps lying around in half-burned boxes" +
                  ", are littering the inner of the remains of the frame of " +
                  "a wagon.\n";
            break;
        }
    }

    return str;

}

string
symbol()
{
    string str;

    switch (myWagon->query_burnstep())
    {
        case 0..1:
        {
            str =  "Some of the boxes have a symbol of a leather-jacket, " +
                   "others have symbols of lamps.\n";
            break;
        }
        case 2:
        {
            str =  "Some of the burning boxes have a symbol of a " +
                   "leather-jacket, others have symbols of lamps.\n";
            break;
        }
        case 3..100:
        {
            str = "You find no symbols.\n";
            break;
        }
    }

    return str;
}

string
remains()
{
    string desc;
    desc = myWagon->remains();
    return desc;
}


void
init()
{
    ::init();
}


void
create_wagon_room()
{

    add_item(({ "boxes", "crates" }), crates);
    add_item(({ "symbols", "symbol" }), symbol);
    add_item(({ "frame", "remains" }), remains);

}


