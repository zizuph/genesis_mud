/*
 * In the attick of the AG in Bree.
 * A hidden item for the /d/Shire/eastroad/western/foam_mug_up quest is here.
 * 
 * Raymundo, Jan 2020
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include "/d/Shire/waymeet/defs.h"

inherit "/d/Shire/std/room.c";

int search_room = (random(5));
int find = 1;
string search_location();

void
create_shire_room()
{
    set_short("In the attic");
    set_long("The attic is so full of stuff you can hardly move. It's not "
        + "like anything is of particular value; it's just stuff. The floor "
        + "is almost completely covered. A stack of boxes lines the back "
        + "wall. In front of the boxes is a heap of weapons and a pile "
        + "of armours. There are clothes scattered everywhere, almost at "
        + "random. It would take a while to search through all of this junk. "
        + "There is an open window behind you, leading back to the roof "
        + "top from whence you came.\n");
        
    add_item("floor", "The floor is almost compeltely covered with stuff. "
        + "It looks sturdy, though, which is something. You think it'd take "
        + "a while to look through all this stuff.\n");
    add_item( ({"stuff", "junk"}), 
        "Where to start, even! The stuff... boxes, armours, "
        + "weapons, clothes... why is all this stuff stored up here?\n");
    add_item( ({ "heap"}),
        "You see swords, axes, spears, clubs and daggers. None of them "
        + "are of particularly good design. Likely small adventurers left "
        + "them in the guild below when better weapons were found. Most of "
        + "the weapons look rusty. This is quite the heap!\n");
    add_item( ({"pile"}),
        "Wow... what a pile of armours. It's almost like a mini-"
        + "mountain of amours. You see shields, breastplates, "
        + "boots, greaves, bracers, and even helmets. Most of them are "
        + "dented and rusty and would be of no use to a serious warrior. "
        + "What a pile!\n");
    add_item("clothes", "There are clothes for boys and girls, men and women, "
        + "scattered about the room. They are on top of everything as well as "
        + "being underfoot.\n");
    add_item("everything", "All this stuff!\n");
    add_item("boxes", "Made of cheap looking wood, the boxes have been nailed "
        + "together and nailed shut. They're stacked against the back wall.\n");
    add_item("ceiling", "It's the bottom of the roof.\n");
    add_item( ({"wall", "walls"}), "The walls look the same on the inside "
        + "of the building as they did on the outside, basically big logs "
        + "stacked one on top of the other.\n");
    add_item("back wall", "The back wall looks like all the others, but it "
        + "has boxes in front of it.\n");
    add_item( ({"window", "open window"}), "The window is quite large--big "
        + "enough for you to walk through--and wide open.\n");
    
    add_exit(ROAD_DIR + "roof1", "out");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(OBJ_S_SEARCH_FUN, "search_stuff");
    reset_shire_room();
}



void
reset_shire_room()
{
    search_room = (random(5)); //so what we're looking for changes
    find = 1;
}

void
init()
{
    ::init();
    add_action("list_location", "list");
}

//Randomizes the location of the hidden object
string search_location()
{
    switch(search_room)
    {
        case 0:
        return("floor");
        
        case 1:
        return( "boxes" );
        
        case 2:
        return( "clothes" );
        
        case 3:
        return( "pile" );
        
        case 4:
        return ("heap");
    }
}

//Note that the search accesses search_location() so that the actual item to search is randomized.
string
search_stuff(object me, string arg)
{
    if(arg == "stuff" | arg == "everything")
    {
        return("You try to search through everything at once. "
            + "That didn't work well.\n");
    }
    
    if(find == 0)
    {
        return("");
    }
    if(arg == search_location())
    {
        object pipe;
        pipe = clone_object(WAYM_OBJ_DIR + "still_pipe_2");
        pipe->move(TP);
        find = 0;
        return("You find a " + pipe->query_short() + " in the "
            + search_location() + "!\n");
    }
            
    else
        return("");
}

//For testing purposes, we need to know where the quest item loads.

int
list_location(string str)
{
    if(!TP->query_wiz_level())
    {
        return 0;
    }
    if(str != "location")
    {
        notify_fail("List locaiton maybe?\n");
        return 0;
    }
    else
    {
        write("The pipe is hidden in the " + search_location()
            + ".\n");
        return 1;
    }
}