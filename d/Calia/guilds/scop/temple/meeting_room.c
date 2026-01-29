
/*
 * meeting_room.c
 *
 * A meeting room for the Spirit Circle of Psuchae Temple
 * This room is for guild members to speak with prospective
 * guild members.
 *
 * Copyright (C): Jaacar (Mike Phipps), August 9th, 2003
 *
 */
 
#pragma strict_types
#pragma save_binary

inherit "/std/room";
inherit "/d/Calia/std/room_tell_room";

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>

#include "defs.h"
#include SPIRIT_HEADER

#define SITTING_ON_COUCH  "_sitting_on_couch"
#define HALLWAY           "/d/Calia/guilds/scop/temple/hallway"

int door_locked = 0;
int book_on_mantle = 1;

void
create_room()
{
    set_short("Meeting Chamber");
    set_long("This is a small meeting chamber in the holy temple. "+
        "On the western wall there is a small fireplace with a "+
        "mantle above it. On the floor are two very comfortable "+
        "looking couches. There is a door leading back to the "+
        "east.\n");

    add_item(({"fireplace","small fireplace"}),"There is a small "+
        "fireplace on the western wall. Burning in it is a bright "+
        "orange fire.\n");
    add_item(({"mantle","marble mantle"}),"There is a white marble mantle sitting above "+
        "the small fireplace. @@check_book@@ @@check_button@@\n");
    add_item(({"fire","orange fire","bright fire","bright orange fire"}),
        "A bright orange fire crackles in the fireplace. It gives off "+
        "just enough heat and light to make this room very comfortable "+
        "both in temperature and lighting.\n");
    add_item(({"couch","couches"}),"These couches are very comfortable "+
        "looking and made from an opulent leather. You could probably "+
        "sit on one of them if you wished. <sit on couch>\n");
    add_item("door","The door leads back out "+
        "to the hallway to the east.\n");
    add_item(({"wall","walls"}),"The walls are made from a smooth "+
        "grey stone.\n");
    add_item(({"roof","ceiling"}),"The ceiling is made from a smooth "+
        "grey stone.\n");
    add_item("floor","The floor is made from a smooth grey stone.\n");

    IN;
    add_prop(ROOM_M_NO_ATTACK,"You cannot attack in here, you are in a "+
        "sacred place!\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK,"You cannot attack in here, you are in "+
        "a sacred place!\n");
    add_prop(ROOM_M_NO_TELEPORT,"This is a sacred place. You cannot use "+
        "teleportation magic here.\n");
    set_tell_time(120);
    add_tell("The fire crackles, soothing your soul.\n");
    add_tell("The heat from the fire warms you nicely.\n");
    add_tell("The fire spits and sputters momentarily.\n");
    add_tell("A shadow dances around the room as the fire flares "+
        "momentarily.\n");
    add_tell("The smell of the fire soothes your soul.\n");

    add_exit(SPIRIT_TEMPLE+"hallway","east","@@check_door",1);
}

string
check_button()
{
    if (!IS_MEMBER(TP))
        return "";
    else
        return "There is a small button on the underside of the "+
            "mantle that you could press. <press button>";
}

string
check_book()
{
    if (book_on_mantle)
        return "There is a sacred book on the mantle.";
    else
        return "";
}

int
check_door()
{
    if (present("_spirit_info_book_",TP))
    {
        write("You cannot leave the room with the sacred book.\n");
        return 1;
    }

    if (!TP->query_prop(SITTING_ON_COUCH))
    {
        if (!door_locked)
            return 0;
        else
        {
            write("The door is locked.\n");
            say(QCTNAME(TP)+" tries to leave through the door, but "+
                "finds it locked.\n");
            return 1;
        }
    }
    
    write("You attempt to leave but realize that you are still "+
        "sitting on the couch. You are quickly sucked back into "+
        "the most comfortable couch you have ever sat on.\n");
    say(QCTNAME(TP)+" attempts to leave while still sitting on "+
        "the couch but is quickly sucked back into it!\n");
    
    return 1;
}

int
do_sit(string str)
{
    if ((!str) && (str != "down") && (str != "on couch"))
    {
        NF("Sit where? On the couch? <sit on couch>\n");
        return 0;
    }

    if (TP->query_prop(SITTING_ON_COUCH))
    {
        NF("You are already sitting on the couch.\n");
        return 0;
    }

    TP->add_prop(SITTING_ON_COUCH,1);
    write("You sit down on one of the couches. It is so comfortable "+
        "that you just do not want to stand up.\n");
    say(QCTNAME(TP)+" sits down on one of the couches.\n");
    TP->add_prop(LIVE_S_EXTRA_SHORT," is sitting on one of the couches");
    return 1;
}

int
do_stand(string str)
{
    if ((!str) && (str != "up"))
    {
        NF("Stand what?  Up? <stand up>\n");
        return 0;
    }

    if (!TP->query_prop(SITTING_ON_COUCH))
    {
        NF("You are already standing.\n");
        return 0;
    }

    TP->remove_prop(SITTING_ON_COUCH);
    write("It takes every ounce of willpower that you have to stand "+
        "up from the amazingly comfortable couch.\n");
    say(QCTNAME(TP)+" stands up.\n");
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
    return 1;
}

int
do_press(string str)
{
    if (!IS_MEMBER(TP))
        return 0;
    
    if (door_locked)
    {
        write("You secretly press the button, unlocking the door.\n");
        tell_room(environment(TP),"You hear a click from the door "+
            "as it unlocks.\n");
        door_locked = 0;
        HALLWAY->set_hidden_lock(0);
        tell_room(SPIRIT_TEMPLE+"hallway","You hear a click from "+
            "somewhere.\n");
        return 1;
    }
    
    write("You secretly press the button, locking the door.\n");
    tell_room(environment(TP),"You hear a click from the door as it "+
        "locks.\n");
    HALLWAY->set_hidden_lock(1);
    tell_room(SPIRIT_TEMPLE+"hallway","You hear a click from "+
        "somewhere.\n");
    door_locked = 1;
    return 1;
}

int
do_get(string str)
{
    object book;

    if (str != "book from mantle")
        return 0;

    if (!IS_MEMBER(TP))
    {
        write("You dare not touch the sacred book unless it is "+
            "given to you.\n");
        return 1;
    }

    if (!book_on_mantle)
    {
        write("There is no book on the mantle for you to take.\n");
        return 1;
    }

    book = clone_object(SPIRIT_OBJECTS+"info_book");
    book->move(TP);
    write("You reach up on the mantle and carefully remove the sacred "+
        "book.\n");
    say(QCTNAME(TP)+" reaches up on to the mantle and removes the sacred "+
        "book.\n");
    book_on_mantle = 0;
    return 1;
}

int
do_return(string str)
{
    object book;

    if (!IS_MEMBER(TP))
    {
        NF("You dare not place anything on the mantle.\n");
        return 0;
    }

    if (str != "book" && str != "book on mantle")
    {
        NF("Return what? The book on the mantle? <return book>\n");
        return 0;
    }

    if (book_on_mantle)
    {
        NF("The sacred book is already on the mantle.\n");
        return 0;
    }

    if (!present("_spirit_info_book_",TP))
    {
        NF("You don't have the sacred book to return.\n");
        return 0;
    }

    book = present("_spirit_info_book_",TP);
    book->remove_object();
    write("You reach up and return the sacred book to the mantle.\n");
    say(QCTNAME(TP)+" reaches up and returns the sacred book to the "+
        "mantle.\n");
    book_on_mantle = 1;
    return 1;
}

void
init()
{
    ::init();
    add_action(do_sit,"sit");
    add_action(do_stand,"stand");
    add_action(do_press,"press");
    add_action(do_get,"get");
    add_action(do_return,"return");
}
