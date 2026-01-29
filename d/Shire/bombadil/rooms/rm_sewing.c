/*
 * Sewing room in Tom's house
 * By Finwe, January 2001
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h" 
#include "../local.h"
 
inherit HOUSE_BASE;

void
create_house_room()
{
    set_short("A sewing room");
    set_long("This large room is cluttered with shelves and some " +
        "work tables. Some shelves line one wall which are full " +
        "of sewing implements and fabrics. The floor is plain " +
        "with no rugs, to make it easier to find dropped items.\n");
    add_item(({"implements", "sewing implements"}),
        "On the shelves and on the work tables are an array of " +
        "items used for sewing, including pins, needles, pincushions, " +
        "threads, fabrics, and patterns.\n");

    add_item(({"cloth","sheets","sheets of cloth","fabrics",
            "sheets of fabrics", "scraps", "fabric scraps", "swatches",
            "fabric swatches", "cloth scraps", "cloth swatches",
            "material", "material scraps", "material swatches"}),
        "Multi-colored scraps and rolls of fabric are tucked away " +
        "on the shelves. They are bright colored and are used for " +
        "making clothes. The fabric looks like it is cotton and " +
        "appears soft.\n");
    add_item(({"rolls of fabric", "rolls", "fabric rolls", 
            "rolls of material", "material rolls"}),
        "The rolls of fabric are stacked on the shelves. Some " +
        "look like they were recently purchased and others have " +
        "pieces cut from them..\n");
    add_item(({"spools of thread", "thread"}),
        "Spools of thread are stacked on the shelves and the " +
        "tables. They are all different colors and sizes and used " +
        "to sew new clothes or hem holes in garments.\n");
    add_item(({"needles","needle"}),
        "The needles are long, smooth pieces of steel. The " +
        "bottom has a sharp point while the top has a narrow " +
        "hole to insert thread into it. Some needles stick out of " +
        "pincushions, others are stored in glass jars on the " +
        "shelves, and others are scattered about on the tables.\n");
    add_item(({"parchment", "parchments", "paper", "patterns"}),
        "They are thin pieces of paper with patterns written on " +
        "them. The parchments lie neatly stacked on the shelves.\n");
    add_item(({"pins", "steel pins"}),
        "They are made of very small, thin nails of steel. One " +
        "end of each pin has a point while the other end has a " +
        "flattened top. They lie in piles on the table, " +
        "stuck in pincushions, or in small jars on the shelves.\n");
    add_item(({"pincushions", "pincushion"}),
        "They are bulging, stuffed balls of fabric neatly stacked " +
        "on the tables and the shelves. They have pins and needles " +
        "sticking out of them.\n");
    add_item("scissors",
        "These marvelous contraptions are made from two sharp " +
        "blades. They are joined together by a large pin that " +
        "enables the blades to be opened and closed, allowing the " +
        "worker to easily cut anything. The tops of the blades " +
        "are pointed and the bottoms have circular handles to " +
        "allow the worker to grasp them with their fingers. " +
        "There are a pair of scissors on the table and the shelves.\n");
    add_item(({"jars", "glass jars"}),
        "The glass jars are of varying sizes. Some are empty " +
        "while others are full pins and needles.\n");
    add_item(({"work tables", "tables"}),
        "Two work tables are in the room. They are made from " +
        "sturdy wood with patterns, pins, needles, and other " +
        "sewing implements stacked neatly across their surfaces.\n");
    add_item(({"shelves"}),
        "The shelves are made of wood and line one wall. They have " +
        "several shelves and are full of sewing implements.\n");

    reset_shire_room();
    add_item(({"north window", "northern window"}), 
        "@@north_up@@\n");
    add_item(({"east window", "eastern window"}), 
        "@@east_up@@\n");
    add_item(({"west window", "western window"}), 
        "@@west_up@@\n");

    set_extra_window("@@window_position@@ set into the " +
        "north and east walls.");
    add_cmd_item(({"curtains", "drapes"}), "close",
        "@@close_curtains@@");
    add_cmd_item(({"curtains", "drapes"}), "open",
        "@@open_curtains@@");
    num_of_windows=3;

    add_exit(ROOMS_DIR + "rm_hall03",  "south");
}
void
init()
{
    ::init();

}


void
reset_shire_room()
{
}
