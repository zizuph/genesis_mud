/*
 *  /d/Gondor/guilds/rangers/north/r_corridor.c
 *
 *  The armoury of the North Hideout
 *
 *  Coded by Elessar
 *    Modified by Alto, 17 July 2001, changed to fit revised theme
 *    Modified by Gwyneth, 3/24/02, added a function call to w_rack
 *    to aid in managing the listings.
 *    Modified by Alto, 29 March 2002, added tunnel to RoI and
 *    exit restrictions.
 *    Updated by Tigerlily, 16 Feb. 2004, removed tunnel
 *      and tweaked descriptions, removed Janitor, made room
 *      permanently 'lit'
 *    Modified by ?, 18 March 2005: previous update?
 *    Modified by Lavellan, 29 October 2010: to use new saving rack system
 *    Modified by Gorboth, 17, Feb, 2014: Added arrow rack.
 *
 */
inherit "/d/Gondor/std/room.c";

#include "../rangers.h"
inherit RANGERS_NOR_DIR + "north_funcs.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "check_exit.c"

// Prototypes:
public void        add_stuff();
public string      read_plaque();
public string      long_desc();

static object  gJar, gARack, gWRack, gCrate, gShelf;


string
long_desc()
{
 
    return "Looking around the room, you see various racks for storing "
        + "armours and weapons. For those items that will not last very "
        + "long, there is a large crate against the south wall. Above the "
        + "crate is a large shelf containing various items unsuitable for "
        + "the equipment racks. The room looks like a place that should be "
        + "kept very tidy. A large plaque hangs on the wall just above the "
        + "shelf, while a vivid tapestry hangs on the east wall. "
        + "The room is lit by an iron torch stand mounted on the east wall.\n";
}

public void
create_gondor()
{
    set_short("the armoury of the North Hideout");
    set_long(&long_desc());

    north_add_items();
    
    add_item("plaque", read_plaque);
    add_cmd_item("plaque", "read", read_plaque);

    add_item(({"room"}), &long_desc());
    add_item(({"armours", "weapons"}), "This looks like a good place "
        + "to keep such things when they are not being used.\n");
    add_item(({"wall", "walls"}), "There are two walls here: a west "
        + "wall and an east wall.\n");
    add_item(({"west wall"}), "A large plaque is mounted on the west "
        + "wall. There is also an interesting shelf on the wall beneath "
        + "it. On the floor rests a crate.\n");
    add_item(({"east wall"}), "Mounted on the east wall are racks for "
        + "storing armours and weapons when they are not in use. There is "
        + "also an iron torch stand placed between the two racks. Next to "
        + "the torch stand hangs a vivid tapestry.\n");
    add_item(({"tapestry", "vivid tapestry"}), "The tapestry shows Turin, "
        + "one of the strongest fighters of the First Age, wielding the black "
        + "sword Gaurthang. He has dealt the death stroke to Glaurung, the "
        + "Father of Dragons, close to Cabed-in-Aras. Cabed-in-Aras is a "
        + "high cliff by the river of Esgalduin in long lost Beleriand.\n");
    
    add_item(({"sentinel", "grey-cloaked sentinel"}), "You are too late! "
        + "Ranger sentinels are usually too busy with their duties to "
        + "stand around long enough to be looked at.\n");
    add_item(({"torch stand", "torch", "iron torchstand", "stand"}), "An iron "
        + "torch stand holds a lit torch that casts a flickering " 
        + "light in the room.\n");
    add_exit(RANGERS_NOR_DIR + "start", "west");
    add_stuff();

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_NO_CLEANUP, 1);
    add_prop(ROOM_I_LIGHT, 1);

    room_add_object(RANGERS_OBJ + "racks/north_arrow_rack");
}

public void
add_stuff()
{
    if (!objectp(gCrate))
    {
//        gCrate = clone_object(RANGERS_OBJ + "crate");
        gCrate = clone_object(RANGERS_OBJ + "racks/north_crate");
        gCrate->move(TO);
    }

    if (!objectp(gARack))
    {
//        gARack = clone_object(RANGERS_OBJ + "a_rack");
        gARack = clone_object(RANGERS_OBJ + "racks/north_a_rack");
        gARack->move(TO);
    }

    if (!objectp(gWRack))
    {
//        gWRack = clone_object(RANGERS_OBJ + "w_rack");
        gWRack = clone_object(RANGERS_OBJ + "racks/north_w_rack");
        gWRack->set_save_file(RANGERS_OBJ + "north_list");
        gWRack->remove_non_glowing();
        gWRack->move(TO);
    }

    if (!objectp(gShelf))
    {
//        gShelf = clone_object(RANGERS_OBJ + "shelf");
        gShelf = clone_object(RANGERS_OBJ + "racks/north_shelf");
        gShelf->move(TO);
    }

    if (!objectp(gJar))
    {
//        gJar = clone_object(RANGERS_OBJ + "herbjar2");
        gJar = clone_object(RANGERS_OBJ + "racks/north_herbjar");
        gJar->add_prop(OBJ_M_NO_GET, "The jar seems to have been glued "
            + "to the floor!\n");
        gJar->move(TO);
    }
}

public string
read_plaque()
{
    write(read_file(RANGERS_NOR_DIR + "lib/north_plaque.txt"));
    return "";
}
