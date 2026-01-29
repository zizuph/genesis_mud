/*
 * Copyright notice, please read.
 *
 * Copyright Chalmers Datorf|rening, 1992
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "../defs.h"

string
mylong()
{
    string s;

    s = "You are standing on a small mountain ledge, not far from a\n"+
        "roaring waterfall that emerges from a dark hole in the mountain.\n"
        +"A few meters above you, partly hidden by some bushes, is a\n"+
	"small cave, towards which the path leads.\n";

    if(TP->query_race()=="dwarf")
        s+="There are two obvious exits: up and east.\n";
    else
        s+="There is one obvious exit: up.\n";

    return s;
}

void
create_room()
{
    set_noshow_obvious(1);

    set_short("Waterfall");
    set_long("@@mylong");
    add_item("waterfall","It is a huge, noisy waterfall.\n");
    add_item("bushes", "They look pretty and are deep green in color.\n");
    add_item("ledge", "It looks narrow, watch your step!\n");
    add_item("hole","The hole serves as an outlet for an underground river.\n");
    add_item("path", "It looks very travelled.\n");
    add_item("cave","The cave is large enough for you to enter it.\n");

    add_exit(LVL2 + "edge1","up");

    add_exit(LVL1 + "corr1","east","@@bl");

}

int
bl()
{
    if(TP->query_race()=="dwarf")
        return 0;
  
    TP->catch_msg("There is no obvious exit east!\n");
    return 1;
}

int
enter(string s)
{
    NF("Enter what? The cave??\n");
    if(s!="" && s!="cave")
        return 0;

    set_dircmd("cave");
    TP->move_living("into the cave",LVL1+"corr1");
    return 1;
}

void
init()
{
    ::init();

    add_action(enter,"enter");
}
