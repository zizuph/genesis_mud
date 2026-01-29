
/*
 * hallway.c
 *
 * Hallway for the Spirit Circle of Psuchae Temple
 * Only guild members may go north from this room
 * (except wizards).
 *
 * Copyright (C): Jaacar (Mike Phipps), July 29th, 2003
 *
 */
 
#pragma strict_types
#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

#include "defs.h"
#include SPIRIT_HEADER

int door_locked = 0;

void
set_hidden_lock(int i)
{
    door_locked = i;
}

int
is_spirit(object living)
{
    return living->query_guild_name_occ() == SPIRIT_GUILD_NAME;
}

void
create_room()
{
    set_short("Hallway");
    set_long("This long hallway connects the regular portion of "+
        "the temple to what looks to be something added on after "+
        "construction. It runs north to south. On the east side "+
        "are two large windows, looking out to the outside of "+
        "the temple.\n");

    add_item(({"tree","trees"}),"The trees sprout up from the "+
        "lush green grass outside.\n");
    add_item(({"grass","lush grass"}),"Through the windows you see "+
        "the lush green grass.\n");
    add_item(({"wall","outside wall"}),"Through the windows you "+
        "see the outside wall of the temple. Its rough grey stone "+
        "exterior sharply contrasts with the lush green grass "+
        "and trees.\n");
    add_item(({"window","windows","two windows","large window",
        "two large windows"}),"The two large windows look outside "+
        "of the temple. There you see lush grass, trees and even "+
        "the outside wall of the temple.\n");
    add_item(({"east side","east wall"}),"On the east wall are "+
        "two large windows, looking out to the outside of the "+
        "temple.\n");

    IN;
    add_prop(ROOM_M_NO_ATTACK,"You cannot attack in here, you are in a "+
        "sacred place!\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK,"You cannot attack in here, you are in "+
        "a sacred place!\n");

    add_exit(SPIRIT_TEMPLE+"startroom","north","@@check_spirit",1);
    add_exit(SPIRIT_TEMPLE+"antechamber","south",0,1);
}

int
check_spirit()
{
    if (is_spirit(TP))
        return 0;
    
    if(TP->query_wiz_level())
    {
        write("Normally you would not be allowed in this chamber, "+
            "but since you are a wizard an exception can be made.\n");
        return 0;
    }
    
    write("A wall of shadow appears in front of you. You hear a voice from "+
        "above:\nOnly those who follow the Spiritual Path may pass.\n\n"+
        "The wall of shadow disappears.\n");
    return 1;
}

int
do_enter(string str)
{   
    if (str == "hidden door")
    {
        if (door_locked)
        {
            write("The door is locked from the inside. You "+
                "cannot get in.\n");
            tell_room(SPIRIT_TEMPLE+"meeting_room","You hear "+
                "someone try the door from the other side.\n");
            return 1;
        }

        write("You quickly and quietly sneak through the door "+
            "in the west wall.\n");
        set_dircmd("hidden door");
        TP->move_living("the room in an unknown direction",
            SPIRIT_TEMPLE+"meeting_room");
        return 1;
    }

    return 0;
}

void
init()
{
    ::init();
    add_action(do_enter,"enter");
}
