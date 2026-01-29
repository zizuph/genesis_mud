/*
 * Main Room of Tom's House
 * By Finwe, January 2001
 *
 * 2002/01/30 Last modified
 * 2011/07/19 Lavellan - Fixed doorknob VBFC
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h" 
#include "../local.h"
 
inherit HOUSE_BASE;

object bombadil;
 
void add_npcs();

void
create_house_room()
{
    set_short("The main room");
    set_long("This is a long low room, filled with the light of " +
        "lamps swinging from the beams of the roof and many candles. " +
        "Against the north wall is a large table of dark polished "+
        "wood with chairs surrounding it. At the south end are " +
        "chairs and a large fireplace. Opposite the front door is a " +
        "large chair surrounded by clay vessels that are full of " +
        "water.\n");

    add_item("furniture",
        "All the furniture is exquisitely carved from fine wood. " +
        "There is a dining room table, several chairs, foot stools, " +
        "and bookshelves. Clay vessels surround a large chair set " +
        "against the east wall.\n"); 
    add_item(({"parchments", "leaves", "documents", "books"}),
        "They are stacked neatly in the bookcases. Looking at them, " +
        "the books are made of bound leather, and the documents, " +
        "leaves, and parchments are made of paper.\n");
    add_item(({"table", "dining room table", "kitchen table"}),
        "Made of fine wood, the table is polished to a dark color. " +
        "It is large enough for several people to sit around it. " +
        "Comfortable high-back chairs surround the table.\n");
    add_item(({"chair","chairs"}),
        "There are several different types of chairs in the room. " +
        "There are high back chairs surrounding the dining room " +
        "table, easy chairs, and a large chair set against a wall. " +
        "They are all made of fine wood and exquisitely carved " +
        "from fine wood.\n");
    add_item(({"door", "front door", "entrance"}),
        "The front door is carved from fine, dark wood. The top " +
        "half has nine window panes set in it to allow the owner " +
        "to look out. A brass doorknob is set just below the windows, " +
        "about half way down the door and on the left side.\n");
    add_item(({"threshold", "stone threshold"}),
        "It is made of stone and lies directly under the door. " +
        "It's a common term for the entrance of a house.\n");
    add_item(({"brass doorknob", "doorknob"}),
        "The doorknob is on the left hand side of the door about " +
        "half way down. It is under the windows and is fashioned " +
//        "from brass. It gleams in the @@day_light@@ light.\n");
        "from brass. It gleams in the @@daylight_desc@@.\n");
    add_item(({"dining room chairs", "high back chairs"}),
        "The chairs are made of fine wood and look very stout. " +
        "The backs curve out slightly and are tall with flat, " +
        "horizontal slats of wood. The seats are padded.\n");
    add_item(({"easy chairs", "easy chair"}),
        "The easy chairs are very heavy looking chairs. They are " +
        "cushioned and arranged around the fireplace. They look " +
        "extremely comfortable with a footstool set before each " +
        "chair.\n");
    add_item(({"large chair"}),
        "The large chair is ornate carved and made from very fine " +
        "wood. The back is very high, like a throne with two arm " +
        "rests. A green cushion is set on the seat making it very " +
        "comfortable. Surrounding the large chair are clay vessels.\n ");
    add_item(({"green cushion"}),
        "The green cushion sits on the large chair. It is fluffy " +
        "looking and decorated with embroidered flowers.\n");
    add_item(({"footstools", "footstool"}),
        "Each footstool is set before an easy chair. It is large " +
        "and cushioned, to provide the person sitting in the easy " +
        "chair a more relaxing sitting. The footstools are made " +
        "from fine wood.\n");
    add_item(({"vessels", "clay vessels", "clay vessel", "vessel", 
            "earthenware", "clay earthenware"}),
        "The clay vessels are large and bowl shaped. They are " +
        "green and brown colored and are full of water. Floating " +
        "in each vessel are beautiful lilies. The effect from the " +
        "vessels is reminiscent of a river with floating lilies.\n");
    add_item(({"wood"}),
        "The wood is very beautiful and expertly carved. Its " +
        "grain is rich and reminiscent of oak or walnut.\n");

    add_item(({"west window", "western window"}), 
        "@@west_down@@\n");
    set_extra_window("@@window_position@@ set into the " +
        "west wall on either sides of the door.");
    add_cmd_item(({"curtains", "drapes"}), "close",
        "@@close_curtains@@");
    add_cmd_item(({"curtains", "drapes"}), "open",
            "@@open_curtains@@");

    num_of_windows=2;
    reset_shire_room();
    set_add_fireplace();

    add_exit(ROOMS_DIR + "rm_hall01", "east");
    add_exit(ROOMS_DIR + "path06",  "west", "@@leave_house@@");
}

void
reset_shire_room()
{
    add_npcs();
}

void
add_npcs()
{

    if(!objectp(bombadil))
    {
        bombadil = clone_object(NPC_DIR + "tom");
        bombadil->set_restrain_path("/d/Shire/bombadil/");
        bombadil->set_random_move(2);
        bombadil->move(TO);
    }
}



void leave_house()
{
    write("You cross the hearth and leave the small house.\n");
}