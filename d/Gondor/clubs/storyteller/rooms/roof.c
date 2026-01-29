/*
 * /d/Gondor/clubs/storyteller/rooms/roof.c
 * Copyright, Rolf Braun a.k.a. Elessar. Genesis, 1998.
 *
 * This is the second floor sitting room of the clubhouse
 */
inherit "/d/Gondor/std/room";
inherit "/d/Gondor/open/room_chairs/room_chairs";
inherit "/d/Gondor/open/fireplace/fireplace";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/open/room_chairs/room_chairs.h"
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <composite.h>
#include "/d/Gondor/open/fireplace/fireplace.h"

public nomask string sitting_look(string arg);
public string fire_desc(string arg);
public int look_desc(string str);
public string exa_desc(string str);

void
create_gondor()
{
    set_short("rooftop of the Teller's");
    set_long("The roof of the Teller's club opens into " +
        "what appears to be a forest with lush green " +
        "plants and trees all around. A fire pit fills the " +
        "center of the roof and has large wooden logs " +
        "surrounding it. A spy glass, which has been firmly " +
        "mounted to a stand, sits in the corner. " +
        fire_desc("light") + "\n");

    add_item(({"plants", "plant", "tree", "trees", "green plant",
        "green plants", "lush plant", "lush green plants",}),
        "Upon closer examination, the trees and bushes are " +
        "actually growing out of barrels and wooden boxes, " +
        "while still giving the impression of being in the " +
        "wilderness.\n");
    add_item(({"spyglass", "spy glass",}),
        "This is a powerful spy glass that was once mounted " +
        "aboard a grand sailing ship. It is constructed of " +
        "the finest lenses and brass fittings. You can use " +
        "it to spy in any direction.\n");
    add_item(({"lenses", "lens", "fittings", "brass fittings",
        "stand", "tripod", "tripod stand",}),
        "The lenses, fittings, and tripod stand are used to " +
        "allow the spy glass to function properly.\n");
    add_item(({"log", "logs", "wooden logs", "wooden log",
        "large logs", "large wooden logs", "large log",
        "large wooden log",}), "Wooden logs have been placed in a ring " +
        "around a large fire pit. They must be used to sit upon while " +
        "sharing stories.\n");

    add_item(({"pit", "fire pit", "large fire pit", "large pit",}),
        &fire_desc("pit"));
    add_item(({"fire", "flames", "flame", "red flames", "gold flames",
        "red flame", "gold flame", }), &fire_desc("fire"));
    add_item(({"firelight", "light", "fire light", }),
        &fire_desc("light"));
    add_item(({"ash", "ashes", "ash in pit", "ashes in pit",
        "ash in fire pit", "ashes in fire pit", }), &fire_desc("ashes"));
    add_item(({"wood", "firewood", "wood in pit", "wood in fire pit",
        "firewood in pit", "firewood in fire pit",}), &fire_desc("wood"));
    add_item(({"city", "pelargir", "streets" }), &exa_desc("city"));
    add_item(({"dock", "docks", "harbor", "pier", "piers" }), &exa_desc("dock"));
    add_item(({"supply", "wood supply", "firewood supply", "bin",
        "firewood bin", "small bin", "firewood in bin",}),
        "A small bin next to the pit holds a supply of  firewood.\n");
    add_chair("log", "[down] [on] [the] 'log'", 10, "on"); //"in"
    add_item(({"log", "sitting log", "logs", "sitting logs", }),
        &sitting_look("log"));

    /*
    add_cmd_item(({"west", "east", "north", "south", "up", "sky",
      "down", "ground",}), "spy", look_desc);
    */


    add_prop(ROOM_I_LIGHT, 2);
    add_exit(STORYT_DIR + "rooms/3rdfloor", "down", check_sitting, 0);
}

nomask public void
reset_room()
{
    set_wood(100);
    tell_room(TO, "A servant silently enters the room, " +
        "replenishing the firewood in the bin by the fire pit before " +
        "quietly departing again.\n");
}

string exa_desc(string str)
{
    write("You decide the spy glass will afford you a better view, and turn "+
        "it toward the "+str+".\n");
    look_desc(str);
    return "";
}

public void
do_sit_msgs(object pl, string prep, string name)
{
    if (name == "log")
    {
        write("You sit down on one of the logs surrounding the fire " +
            "pit.\n");
        say(QCTNAME(pl) + " sits down on one of the logs surrounding " +
            "the fire pit.\n", pl);
    }
    else
        ::do_sit_msgs(pl, prep, name);
}

public void
do_stand_msgs(object pl, string name)
{
    if (name == "log")
    {
        write("You stand up from the log.\n");
        say(QCTNAME(pl) + " stands up from the log.\n", pl);
    }
    else ::do_stand_msgs(pl, name);
}

nomask public string
sitting_look(string arg)
{
    string  occupants;
    if (arg == "log")
    {
        return "Wooden logs have been placed in a ring around " +
            "a large fire pit. They must be used to sit upon while " +
            "sharing stories. \n" + sitting_on_chair("log", TP, 0);
    }

}


nomask public string
fire_desc(string arg)
{
    int fire_state = query_fire_state();
    string desc;

    switch(arg)
    {
    case "pit":
        switch (fire_state)
        {
        case FIRE_BURNING:
            return "A nice fire is burning in the fire pit, " +
                "emitting a comfortable heat throughout " +
                "the roof top. A small bin stands next " +
                "to the pit, holding extra firewood. \n" +
                sitting_on_chair("pit", TP, 0);
        case FIRE_UNLIT_WOOD:
            return "In the center of the room is a fire pit, " +
                "a stack of firewood  placed within " +
                "it ready to be lit. A small bin next to the " +
                "pit holds extra firewood. " +
                sitting_on_chair("pit", TP, 0) + "\n";
        default:
            return "A fire pit set into the middle of the " +
                "rood top, dark and empty at the moment. A " +
                "small bin next to it holds an extra supply of " +
                "firewood. " + sitting_on_chair("pit", TP, 0) + "\n";
        }
    case "fire":
        if (fire_state == FIRE_BURNING)
            return "Gold and red flames cast a weak light over the room.\n";
        else
            return "You find no fire.\n";
    case "wood":
        switch (fire_state)
        {
        case FIRE_BURNING:
            return "The wood in the fire pit burns warmly, " +
                "emitting a pleasant warmth. In " +
                "the small bin next to the pit more wood " +
                "has been stacked.\n";
        case FIRE_UNLIT_WOOD:
            return "Wood has been piled up in the fire pit, " +
                "waiting to be lit. An extra supply lies in the " +
                "small bin next to the pit.\n";
        default:
            return "A small bin next to the fire pit holds " +
                "a supply of firewood.\n";
        }
    case "ashes":
        switch (fire_state)
        {
        case FIRE_BURNING:
            return "Beneath the brightly burning fire, ashes " +
                "cover the bottom of the fire pit.\n";
        case FIRE_UNLIT_WOOD:
            return "Beneath the firewood, ashes cover the " +
                "bottom of the fir pit.\n";
        default:
            return "Ashes cover the bottom of the fire pit.\n";
        }
    case "light":
        if (fire_state == FIRE_BURNING)
            return "The flames in the fire pit cast a weak light " +
                "over the room.\n";
        if (!strlen(Exa_arg))
            return "";
        if (Exa_arg != "light")
            return "You find no fire.\n";
    }
    return "";
}

void
init()
{
    ::init();
    init_room_chairs();
    init_fire();

    add_action("look_desc", "spy");
}

void
leave_inv(object obj, object to)
{
    leave_inv_room_chairs(obj, to);
    ::leave_inv(obj, to);
}

string *get_room_filenames(string str)
{
    string *tmp = get_dir(str), *rooms = ({ });
    object room;
    int i, size;

    if (!sizeof(tmp))
        return ({ "none", });

    for (i = 0, size = sizeof(tmp); i < size; i++)
        if ((room = find_object(str + tmp[i])) != 0)
            if (!room->query_prop(ROOM_I_INSIDE))
                rooms += ({ str + tmp[i] });

    if (sizeof(rooms))
        return rooms;
    else
        return ({ "none", });
}

string
dock_desc()
{
    string *roomfiles;
    object *inv, *live, *dead, room;
    int i, size;

    roomfiles = get_room_filenames("/d/Gondor/pelargir/docks/");

    inv = ({});

    for (i = 0, size = sizeof(roomfiles); i < size; i++)
    {
        if ((room = find_object(roomfiles[i])) != 0)
          inv += all_inventory(room);
    }

    if (inv && sizeof(inv) > 0)
    {
        live = FILTER_LIVE(inv);
        live -= ({ TP });
        dead = filter((inv), &->id("corpse"));
        if (sizeof(live) > 0 && sizeof(dead) > 0)
            return ("At the docks to the east, you can see " +
                COMPOSITE_LIVE(live) + ", as well as " +
                COMPOSITE_DEAD(dead) + ".\n");
        else if (sizeof(live) > 0)
            return ("At the docks to the east, you can see " +
                COMPOSITE_LIVE(live) + ".\n");
        else if (sizeof(dead) > 0)
            return ("At the docks to the east, you can see " +
                COMPOSITE_DEAD(dead) + ".\n");
    }
    return ("The docks of Pelargir look totally empty, surely that "+
        "is a bad sign.\n");
}

string
pelargir_desc()
{
    string *roomfiles;
    object *inv, *live, *dead, room;
    int i, size;

    roomfiles = get_room_filenames("/d/Gondor/pelargir/streets/");

    inv = ({});

    for (i = 0, size = sizeof(roomfiles); i < size; i++)
    {
        if ((room = find_object(roomfiles[i])) != 0)
          inv += all_inventory(room);
    }

    if (inv && sizeof(inv) > 0)
    {
        live = FILTER_LIVE(inv);
        live -= ({ TP });
        dead = filter((inv), &->id("corpse"));
        if (sizeof(live) > 0 && sizeof(dead) > 0)
            return ("In the city below, you can see " +
                COMPOSITE_LIVE(live) + ", as well as " +
                COMPOSITE_DEAD(dead) + "!\n");
        else if (sizeof(live) > 0)
            return ("In the city below, you can see " +
                COMPOSITE_LIVE(live) + ".\n");
        else if (sizeof(dead) > 0)
            return ("In the city below, you can see " +
                COMPOSITE_DEAD(dead) + "!\n");
    }
    return ("The streets of Pelargir look totally empty, surely that "+
        "is a bad sign.\n");
}

public int
look_desc(string str)
{
    string text;

    switch(str)
    {
    case "city":
    case "pelargir":
    case "streets":
    case "around":
        text = pelargir_desc();
        break;
    case "dock":
    case "docks":
    case "pier":
    case "piers":
    case "harbor":
        text = dock_desc();
        break;
    case "east":
        write("To the east you see the dock area, which "+
            "you can examine closer.\n");
        return 1;
    case "west":
        write("To the west, you see only the city, which you "+
            "can examine closer.\n");
        return 1;
    case "north":
        write("To the north you see the road that stretches "+
            "out from Pelargir to the city of Minas Tirith.\n");
        return 1;
    case "south":
        write("To the south you see the area beyond the "+
            "city of Pelargir.\n");
        return 1;
    case "down":
    case "ground":
        write("Turning the spy glass downwards, you get "+
            "a closeup view of the ground at your feet.\n");
        return 1;
    default:
        write("You cannot see anything that way.\n");
        return 1;
    }

    write(text);
    return 1;
}

