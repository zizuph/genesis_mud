/*
 * Shed in the Garden of the Elementalist Temple
 *
 * This shed contains the tools that are necessary to properly tend
 * the garden.
 *
 * Created by Petros, May 2011
 */

#pragma strict_types

#include <files.h>
#include <stdproperties.h>
#include <language.h>
#include "../defs.h"

inherit ROOM_OBJECT;
inherit "/d/Calia/lib/try_item";
inherit "/d/Calia/lib/room_tell";

// Global Variables
public int          Num_hoes = 3;
public int          Num_shears = 3;

/*
 * Function:    create_room
 * Description: Set up defaults for the garden shed
 */
public void
create_room()
{
    set_short("Inside a wooden garden shed");
    set_long("This is a small simple garden shed hardly big enough for one "
        + "individual. The west wall of the shed is lined with shelves "
        + "containing various gardening tools. The shed seems to contain "
        + "everything necessary for tending a garden.\n\n"); 
               
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_ATTACK, "This garden is a peaceful place! There will "
        + "be no combat in the sanctity of this location.\n");
        
    try_item( ({ "garden", "walled garden" }),
        "You are standing inside the garden shed. There are bits of light "
      + "streaming through the spaces between the boards, but with no "
      + "windows, you do not get a good view of the garden outside.\n");
    
    try_item( ({ "spaces", "boards", "light", "bits of light", "board",
                 "wooden board", "wooden boards", "space" }),
        "The light streaming through the spaces between the boards provides "
      + "just enough light for you to see rather well in here.\n");
      
    try_item( ({ "wall", "walls" }),
        "The wooden boards make up all the walls of the shed. There are "
      + "some spaces between the boards through which the light from the "
      + "outside garden stream in. There are no windows in this shed.\n");
      
    try_item( ({ "ground", "floor" }),
        "The floor boards are also wooden. The shed looks very clean, with "
      + "very little dust on the ground.\n");
    
    try_item( ({ "ceiling" }),
        "The shed's ceiling is rather uninteresting. There are no light "
      + "sources above you. All the light you need seems to be streaming "
      + "in from the outside.\n");
    
    try_item( ({ "tools", "tool", "gardening tool", "gardening tools" }),
        "The gardening tools in this room are all stored on the four "
      + "shelves that line the west wall of the shed.\n");
      

    // Clone the shelves here
    object shelf;
    
    shelf = clone_object(GARDENING_SHED_SHELF);
    shelf->move(this_object());
    shelf->set_shelf_type("basket");
    
    shelf = clone_object(GARDENING_SHED_SHELF);
    shelf->move(this_object());
    shelf->set_shelf_type("watering can");

    shelf = clone_object(GARDENING_SHED_SHELF);
    shelf->move(this_object());
    shelf->set_shelf_type("secateur");

    shelf = clone_object(GARDENING_SHED_SHELF);
    shelf->move(this_object());
    shelf->set_shelf_type("hoe");

    add_exit(ELEMENTALIST_GARDEN + "diabrecho_g", "out");
}
