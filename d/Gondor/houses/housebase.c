/*
 * housebase.c
 *
 * A base file for houses in Genesis towns
 *
 * Varian - Jan 2020
 *
 */

#pragma strict_types

#include "/d/Gondor/houses/defs.h"

inherit HOUSE_BASE;
inherit "/d/Gondor/common/lib/room_tell";

#include <macros.h>

void set_items_bedroom();
void set_items_kitchen();
void set_items_living();
void set_items_yard();
void set_items_wood();
void set_items_stone();

#define NO_COFFIN_PLACEMENT     "_no_coffin_placement"

/*
 * Function name:        create_house_room
 * Description  :        Use create_house_room() to make rooms in
 *                       player houses across Genesis.
 */

void create_house_room() 
{
}

nomask void create_room() 
{

    create_house_room();

    add_prop(NO_COFFIN_PLACEMENT, 1);
    add_prop(ROOM_M_NO_TELEPORT_TO, block_teleport);
    set_tell_time(random(350) + 100);
	set_junkyard_room("/d/Shire/bree/rooms/road/broad03");
    set_house_name("bree1");
    add_prop(ROOM_M_NO_TELEPORT_TO, block_teleport);
}

public void hook_notify_item_returned(object ob, object to)
{
    //This can be replaced by custom messaging if desired.
    ::hook_notify_item_returned(ob, to);
}

public void hook_notify_item_tossed(object ob, object junkyard)
{
    //This can be replaced by custom messaging if desired.
    ::hook_notify_item_tossed(ob, junkyard);
}

public void hook_notify_item_destroyed(object ob)
{
    //This can be replaced by custom messaging if desired.
    ::hook_notify_item_destroyed(ob);
}


/*
 * Function name:        set_items_bedroom
 * Description  :        Items added to house rooms when you include
 *                       the line set_items_bedroom(); 
 *                       May also add room specific tells in here.
 *                       Use for bedrooms in houses
 */

public void
set_items_bedroom()
{
    add_item( ({"bedroom", "bed room"}),
        "This is the bedroom of the house, where the owner sleeps.\n");

}

/*
 * Function name:        set_items_kitchen
 * Description  :        Items added to house rooms when you include
 *                       the line set_items_kitchen(); 
 *                       May also add room specific tells in here.
 *                       Use for kitchens in houses
 */

public void
set_items_kitchen()
{
    add_item( ({"kitchen"}),
        "This is the kitchen of the house.\n");

}

/*
 * Function name:        set_items_living
 * Description  :        Items added to house rooms when you include
 *                       the line set_items_living(); 
 *                       May also add room specific tells in here.
 *                       Use for living rooms in houses
 */

public void
set_items_living()
{
    add_item(({"living room", "living"}),
        "This is the living room of the house.\n");
}

/*
 * Function name:        set_items_yard
 * Description  :        Items added to house rooms when you include
 *                       the line set_items_yard(); 
 *                       May also add room specific tells in here.
 *                       Use for yards of houses
 */

public void
set_items_yard()
{
    add_item(({"yard", "lawn"}),
        "This pleasant yard is private property, belonging to " +
        "the owner of this house.\n");
}

/*
 * Function name:        set_items_wood
 * Description  :        Items added to wooden houses when you
 *                       include the line set_items_wood(); 
 *                       May also add room specific tells in here.
 *                       Use for houses made of wood
 */

public void
set_items_wood()
{
    add_item(({"wall", "walls"}),
        "The walls of this house are made from rows of wide " +
        "wooden planks.\n");
    add_item(({"floor", "ground"}),
        "Like the rest of the house, the floor here is made of wood.\n");
    add_item(({"ceiling", "up"}),
        "Like the rest of the house, the ceiling here is made of wood.\n");
    add_item(({"planks", "wooden planks"}),
        "The base structure of the inside of this house appears to " +
        "be almost completely covered with rows upon rows of wide " +
        "wooden planks.\n");
}

/*
 * Function name:        set_items_stone
 * Description  :        Items added to stone houses when you include
 *                       the line set_items_stone(); 
 *                       May also add room specific tells in here.
 *                       Use for houses made of stone
 */

public void
set_items_stone()
{
    add_item(({"wall", "walls"}),
        "The walls of this house are made from solid blocks of stone, " +
        "each of them so finely cut and placed that you could barely " +
        "fit a knife blade in the gap.\n");
    add_item(({"floor", "ground"}),
        "The floor is a colourful mosaic of smooth stones laid down " +
        "in a bed of mortar. The stones have been carefully placed " +
        "in such a manner that a simple geometric design repeats " +
        "itself as it runs through the house.\n");
    add_item(({"ceiling", "up"}),
        "Smooth blocks of stone arch above your head to form a " +
        "strong, sturdy ceiling.\n");
    add_item(({"mosaic", "mosaics", "design", "geometric design",
            "stones", "smooth stones", "colourful mosaic"}),
        "The mosaic running across the floor appears to be mostly " +
        "made from a white marble, while smaller pieces of green, " +
        "blue and orange stones intertwine with each other as " +
        "they form a simple, if intricate, geometric design which " +
        "spreads out across the entire floor.\n");
}