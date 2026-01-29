/*
 *  /d/Gondor/guilds/rangers/hq/armroom.c
 *
 *  The armoury of Central Headquarters
 *
 *  Coded by Elessar
 *  Modification log:
 *    Alto, 29 June 2001, changed to fit CH theme
 *    Gwyneth, 3/24/02, added a function call to the weapon rack to aid in
 *       managing the listings.
 *    Tigerlily, January, 2004
 *    --removed torches and janitor
 *    Gwyneth - Neatened up
 *    ?, 22 August 2004, last update?
 *    Lavellan, 29 October 2010, changed for new saving rack system
 */
inherit "/d/Gondor/std/room.c";
#include "../rangers.h"

inherit RANGERS_HQ_DIR + "ch_funcs.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

// Prototypes:
void               add_stuff();
public string      read_plaque();
public string      long_desc();

static object  gJar, gArack, gWrack, gCrate, gShelf;

string
long_desc()
{
    return "Looking around the room, you see various racks for storing "
        + "armours and weapons. For those items that will "
        + "not last very long, there is a large crate against the north "
        + "wall. On the south wall is a large shelf containing various "
        + "items unsuitable for the equipment racks. The room looks "
        + "like a place that should be kept very tidy. Torchstands in " 
        + "each corner hold long-burning torches that are kept " 
        + "constantly lit. A large plaque hangs on the wall just " 
        + "above the crate.\n";

}

public void
create_gondor()
{
    set_short("the armoury of Central Headquarters");
    set_long(&long_desc());

    hideout_add_items();
    
    add_item("plaque", &read_plaque());
    add_cmd_item("plaque", "read", &read_plaque());

    add_item(({"room"}), &long_desc());
    add_item(({"armours", "weapons"}), "This looks like a good place "
        + "to keep such things when they are not being used.\n");
    add_item(({"wall", "walls"}), "There are three walls here: a north "
        + "wall, a south wall and an east wall.\n");
    add_item(({"north wall"}), "A large plaque is mounted on the north "
        + "wall. There is also an interesting crate resting beneath it.\n");
    add_item(({"south wall"}), "Mounted on the south wall are racks for "
        + "storing armours and weapons when they are not in use. There is "
        + "also an iron torch stand placed between the two racks.\n");
    add_item(({"east wall"}), "The east wall is made from native wood "
        + "milled from the Druedain forest.\n");
    add_item(({"torchstands", "torchstand"}),
        "Iron torchstands hold long-burning " 
        + "torches that are kept constantly lit.\n");
    add_item(({"torch", "torches"}), "Special long-burning "
        + "torches are kept constantly lit in this enclosed "
        + "room.\n");
    
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_NO_CLEANUP, 1);
    add_prop(ROOM_I_LIGHT, 1);

    add_exit(RANGERS_HQ_DIR + "ucorridor1", "west", 0, 1);

    add_stuff();

    reset_room();
}

/*
 * Function name: add_stuff
 * Description  : Adds crate, racks, shelf and jar to room.
 */
void
add_stuff()
{
    if (!objectp(gCrate))
    {
//        gCrate = clone_object(RANGERS_OBJ + "crate");
        gCrate = clone_object(RANGERS_OBJ + "racks/hq_crate");
        gCrate->move(TO);
    }

    if (!objectp(gArack))
    {
//        gArack = clone_object(RANGERS_OBJ + "a_rack");
        gArack = clone_object(RANGERS_OBJ + "racks/hq_a_rack");
        gArack->move(TO);
    }

    if (!objectp(gWrack))
    {
//        gWrack = clone_object(RANGERS_OBJ + "w_rack");
        gWrack = clone_object(RANGERS_OBJ + "racks/hq_w_rack");
        gWrack->set_save_file(RANGERS_OBJ + "hq_list");
        gWrack->remove_non_glowing();
        gWrack->move(TO);
    }

    if (!objectp(gShelf))
    {
//        gShelf = clone_object(RANGERS_OBJ + "shelf");
        gShelf = clone_object(RANGERS_OBJ + "racks/hq_shelf");
        gShelf->move(TO);
    }

    if (!objectp(gJar))
    {
//         gJar = clone_object(RANGERS_OBJ + "herbjar2");
         gJar = clone_object(RANGERS_OBJ + "racks/hq_herbjar");
        gJar->add_prop(OBJ_M_NO_GET, "The jar seems to have been glued "
            + "to the floor!\n");
        gJar->move(TO);
    }
}

public string
read_plaque()
{
   write(read_file(RANGERS_HQ_DIR + "lib/ch_plaque.txt"));
   return "";
}
