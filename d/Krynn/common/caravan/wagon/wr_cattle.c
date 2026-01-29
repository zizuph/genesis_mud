/*
 *  Filename:       wr_cattle.c
 *  Description:    This is the room on top of the cattle wagon w_cattle.
 *
 *  Copyright (c) Aug. 2003 by Peter Bech Lund, aka. Vencar of Krynn
 *
 *  Change log:
 */

#pragma strict_types
#include "/sys/language.h"
#include "wagon.h"


inherit WAGON_ROOM_INDOOR;

string
hay()
{

    string str;

    switch (myWagon->query_burnstep())
    {
        case 0:
        {
            str = "The hay looks dried and fresh, perfect food for cattle.\n";
            break;
        }
        case 1..4:
        {
            str = "The hay on top of the wagon are burning, billowing heavy " +
                  "smoke after the wagon";
                  break;
        }
        case 5..100:
        {
            str = "You find no hay.\n.";
            break;
        }
    }

    return str;
}

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
                     ", in the hay.\n" +
                    "There is hay in bundles everywhere here.\n";
            break;
        }
        case 1:
        {
            desc =  "You are on top of " + LANG_ADDART(myWagon->short()) +
                    ", in the smoking hay.\nThere is hay in bundles " +
                    "everywhere here, some of it is on fire.\n";
                  break;
        }
        case 2:
        {
            desc =  "You are on top of " + LANG_ADDART(myWagon->short()) +
                    ", in the burning hay.\nThere is burning hay " +
                    "everywhere here.\n";
                  break;
        }
        case 3:
        {
            desc =  "You are on top of " + LANG_ADDART(myWagon->short()) +
                    ", in the burning hay.\nThe hay is blazing with fire " +
                    "making it impossible to see very far.\n";
                  break;
        }
        case 4:
        {
            desc =  "You are in " + LANG_ADDART(myWagon->short()) +
                    ", the wagon have almost been consumed entirely by " +
                    "the fire.\n";
                  break;
        }
        case 5..100:
        {
            desc = "You are standing in the remains of what once was a " +
                  "farmer wagon.\n";
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
            desc =  "On top of the wagon, in the hay";
            break;
        }
        case 1:
        {
            desc =  "On top of the wagon, in the smoking hay";
            break;
        }
        case 2:
        {
            desc =  "On top of the wagon, in the burning hay";
            break;
        }
        case 3:
        {
            desc =  "On top of the wagon, in the flaming inferno";
            break;
        }
        case 4:
        {
            desc =  "On top of the wagon, in the smouldering fire";
            break;
        }
        case 5..100:
        {
            desc =  "In the middle of the remains of a farmer wagon";
            break;
        }
    }

    return desc;

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

    string str;

    add_item(({ "hay", "bundles" }), hay);
    add_item("remains", remains);


}


