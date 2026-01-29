/*
 * Woodsmen village in Mirkwood.
 * Varian 2015
 */

#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>


inherit MIRKWOOD_STD_DIR + "room";

#pragma save_binary
#pragma strict_types


void
create_room()
{
    set_short("Upstairs at the Wild Boar Inn");
    set_long("You are currently in a large common room above the Wild " +
        "Boar Inn. Gazing about the room, you notice that it is rather sparsely " +
        "furnished. There are several beds scattered around the room, offering " +
        "a place to sleep for anyone who might wish to spend the night and there " +
        "are some half-broken old, wooden tables sprinkled around the room haphazardly. " +
        "On the northern wall, light spills in from two dirty windows which gaze out " +
        "upon the quiet village of Weanting. A wide, wooden staircase in the east " +
        "wall winds down towards the rest of the inn.\n");
  
    add_item_light(({"floor", "wooden floor", "planks", "wooden planks"}),
        "This floor is nothing more than dozens of rough, wooden planks " +
        "which stretch out across the room. The planks have been cleanly " +
        "sanded, so as to avoid getting any splinters.\n", LIGHT_ALL);
    add_item_light(({"beam", "beams", "long beam", "long beams", "wooden beam", "wooden beams"}),
        "The long, wooden beams of the ceiling reach out in one solid length, " +
        "supporting the roof of the inn.\n", LIGHT_ALL);
    add_item_light(({"ceiling", "wooden ceiling"}),
        "The ceiling of this inn seems to be a network of long, wooden beams " +
        "which either cross the room or slope up to a peak to support the " +
        "roof of the building.\n", LIGHT_ALL);
    add_item_light(({"wall", "walls"}),
        "Which wall did you want to look at? The northern?, " +
        "eastern?, southern? or western wall?\n", LIGHT_ALL);
    add_item_light(({"west wall", "western wall"}),
        "This is a wooden wall, it helps to keep you warm and dry inside.\n", LIGHT_ALL);
    add_item_light(({"south wall", "southern wall"}),
        "This is a wooden wall, it helps to keep you warm and dry inside.\n", LIGHT_ALL);
    add_item_light(({"north wall", "northern wall"}),
        "The northern wall of this common room boasts two dirty windows which let " +
        "in light and look down upon the village of Weanting.\n", LIGHT_ALL);
    add_item_light(({"east wall", "eastern wall"}),
        "The eastern wall of this common room is broken up by the mouth of a wide, " +
        "wooden staircase which leads down to the rest of the inn.\n", LIGHT_ALL);
    add_item_light(({"staircase", "stairs", "wide staircase", "wooden staircase"}),
        "This is the wide, wooden staircase that you climbed to get up into this common " +
        "room in the first place. You can see a landing just below, where the staircase " +
        "splints into two, the northern branch leading to the tables where the customers " +
        "sit and the southern branch leading towards the fireplace.\n", LIGHT_ALL);
    add_item_light(({"window", "windows"}),
        "There are two windows, side by side, set into the northern wall of this common " +
        "room. The windows are rather dirty, but they still let in a lot of light and you " +
        "can make out the rest of the village of Weanting when you look through them.\n", LIGHT_ALL);
    add_item_light(({"bed", "beds"}),
        "These beds are mostly just beds in name. They consist of little more than a " +
        "sturdy box filled with clean straw, with brown, woolen blankets draped over top.\n", LIGHT_ALL);
    add_item_light(({"table", "tables"}),
        "There are a couple of old, wooden tables here in this common room, but apparently " +
        "no chairs. The tables do not look to be in very good condition, almost as if the " +
        "innkeeper just took any table which was damaged in the inn down below and dumped " +
        "it up here.\n", LIGHT_ALL);
    add_item_light(({"room", "common room"}),
        "This large common room is above the Wild " +
        "Boar Inn. There are several beds scattered around the room, offering " +
        "a place to sleep for anyone who might wish to spend the night. On the " +
        "northern wall, light spills in from two dirty windows which gaze out " +
        "upon the quiet village of Weanting. A wide, wooden staircase in the east " +
        "wall winds down towards the rest of the inn\n", LIGHT_ALL);
    add_item_light(({"village", "weanting"}),
        "You can see the small village of Weanting out through the windows in the " +
        "northern wall.\n", LIGHT_ALL);
    add_item_light(({"splinter", "splinters"}),
        "Hmm... nope! You cannot seem to find any splinter here.\n", LIGHT_ALL);
    add_item_light(({"roof", "outside"}),
        "You cannot see the roof outside from here!\n", LIGHT_ALL);
    add_item_light(({"straw", "box"}),
        "These boxes full of clean straw is what this inn uses for bedding.\n", LIGHT_ALL);
    add_item_light(({"blanket", "blankets", "wool", "wool blanket", "wool blankets", "woolen blanket", "woolen blankets"}),
        "These brown, wool blankets look fairly clean and are thick enough to be comfortably warm.\n", LIGHT_ALL);

    add_prop(ROOM_I_INSIDE,1);

    add_exit(WOODSMEN_DIR + "weant_inn.c", "down");

}

