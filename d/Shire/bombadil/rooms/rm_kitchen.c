/*
 * Kitchen of Tom's House
 * By Finwe, January 2001
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h" 
#include "../local.h"
 
inherit HOUSE_BASE;

object bombadil, door;
 
void
create_house_room()
{
    set_short("A large kitchen");
    set_long("This is a long room, cozy and full of the " +
        "fragrances of good food cooking. A warm glow fills the " +
        "room from the swing lamps on the ceiling and the candles " +
        "scattered about the room. A large stove sits at the " +
        "south end of the room, warming it. Cupboards line the " +
        "west wall and a small table sits against the east wall, " +
        "next to the door leading outside. A small door is " +
        "against the north wall.\n");
    add_item(({"table", "kitchen table"}),
        "The kitchen table is round and small, large enough for " +
        "a few people to gather around it. It is made of wood " +
        "and polished, with a few comfortable chairs surround the " +
        "table.\n");
    add_item(({"chair","chairs"}),
        "The chairs are made of wood and exquisitely carved from " +
        "fine wood. The are placed around the kitchen table.\n");
    add_item(({"back door", "entrance"}),
        "The back door is carved from fine, dark wood. It has a " +
        "large oval window. A brass doorknob is set about half " +
        "down the door on the left side.\n");
    add_item(({"threshold", "stone threshold"}),
        "It is made of stone and lies directly under the door. " +
        "It's a common term for the entrance of a house.\n");
    add_item(({"brass doorknob", "doorknob"}),
        "The doorknob is on the left hand side of the door about " +
        "half way down. It gleams in the @@daylight_desc@@ light.\n");
    add_item(({"wood"}),
        "The wood is very beautiful and expertly carved. Its " +
        "grain is rich and reminiscent of oak or walnut.\n");
    add_item(({"oval window"}),
        "The oval window is set into the top of the back door. " +
        "It is made from elegantly cut glass that catches the " +
        "outdoor light and casts rainbows around the room.\n");
    add_item(({"stove"}),
        "The stove is large and black, dominating the south wall. " +
        "It is made of steel with rounded corners. The surface is " +
        "flat. There are two large doors on the front of the stove.\n");
    add_item(({"steel doors", "large doors"}),
        "The large doors are closed on the front of the stove. " +
        "They open, allowing foods to be baked inside the stove. \n");
    add_item(({"cupboards"}),
        "The cupboards are tall and made of wood. They are closed " +
        "and line the west wall. The cupboards are used to store " +
        "food and kitchen utensils.\n");
    add_item(({"kitchen utensils", "food"}),
        "You don't find any. They are presumably stored in the " +
        "cupboards.\n");
    add_item(({"doors", "door"}),
        "There are two doors in the room. There is a small door " +
        "and an back door.\n");

    add_item(({"east window", "eastern window"}), 
        "@@east_down@@\n");
    set_extra_window("@@window_position@@ set into the " +
        "east wall on either sides of the door.");
    add_cmd_item(({"curtains", "drapes"}), "close",
        "@@close_curtains@@");
    add_cmd_item(({"curtains", "drapes"}), "open",
            "@@open_curtains@@");

    num_of_windows=2;
    reset_shire_room();

    door = clone_object(OBJ_DIR + "kitchen_door");
    door -> move(this_object());


    add_exit(ROOMS_DIR + "rm_hall01", "north");
    add_exit(ROOMS_DIR + "path10",  "east", "@@leave_house@@");
}

void
reset_shire_room()
{
}

void leave_house()
{
    write("You cross the hearth and leave the small house.\n");
}