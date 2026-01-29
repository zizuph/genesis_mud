/*
 *  Bilbo's room
 * By Finwe, January 1998
 */
 
#pragma strict_types
 
#include "local.h"
 
inherit HOUSE_IN_BASE;
static object bilbo;

void
create_house_room()
{
    set_short("A small guestroom");
    set_long("This guestroom is cozy and comfortable. The " +
        "most noticeable features of the room are " +
        "the leaves, parchments and books scattered across a " +
        "desk and table in the room. A small bed sits in one " +
        "corner of the room. A round door opens out to the " +
        "garden outside with a large window on either side of it. " +
        "In another corner of the room are a row of pegs.\n");

    add_item(({"clothing"}),
        "You see coats and hats hanging from the pegs by the door.\n");
    add_item("coats",
        "They are about the right size for small people and " +
        "dark in color. Some are brown, grey, dark green and " +
        "other earth colours. They are hanging from the pegs by " +
        "the door.\n");
    add_item("hats", 
       "There are different styles of hats. Some are floppy " +
       "while others are simple in style. They are all small " +
       "and in various earth colours. The hats hang from some " +
       "pegs by the door.\n");
    add_item(({"memoirs", "memoir"}),
        "They are a collection of life histories, stories, and " +
        "other musings written down for others to enjoy.\n");
    add_item("furniture",
        "All the furniture is exquistely carved from fine wood. " +
        "You see a bed, a desk, a table, and some chairs. An " +
        "odd feature of all this is the furniture is is short " +
        "and small. It certainly wouldn't fit an elf.\n"); 
    add_item(({"parchments", "leaves", "documents", "books"}),
        "They are scattered about the room and stacked in " +
        "piles on the desk and table. They appear to be " +
        "memoirs, letters to and from friends, and stories or " +
        "histories of the occupant's life.\n");
    add_item("desk",
        "The desk is made of fine wood. The craftsmanship is " +
        "superb. Piles of documents and books are scattered " +
        "across the top of the desk. You also see some quills " +
        "and an inkpot for writing.\n");
    add_item("table",
        "Made of fine wood, the table is sturdy but cluttered. " +
        "On one end are the remains of the last meal while at " +
        "the other end are stacks of documents and books.\n");
    add_item(({"chair","chairs"}),
        "Both chairs are sturdy and made of fine wood. They are " +
        "both pushed in. Bright cushions are on both seats.\n");
    add_item(({"door", "round door"}),
        "The door is about the height of a hobbit. It's painted " +
        "green with a brass doorknob in the center. It leads " +
        "out to the garden.\n");
    add_item(({"brass doorknob", "doorknob"}),
        "The doorknob is in the exact center of the door. It is " +
        "fashioned from brass and gleams in the light.\n");
    add_item(({"pegs", "row of pegs"}),
        "The rows of peg are set into the wall. They are " +
        "fashioned of oak. Each peg has a silver ball attached " +
        "to its top. Various items of clothing hang from some " +
        "of the pegs.\n");
    add_item(({"clothes", "items of clothing", 
            "various items of clothing"}),
        "You see cloaks, shirts, coats, and other clothing " +
        "hanging from the pegs. They are brightly colored and " +
        "in excellent condition.\n");
    add_item(({"cloaks", "shirts", "coats", "other clothing"}),
		"They are brightly colored and in excellent condition. " +
        "They hang from some pegs in a corner of the room.\n");
    add_item(({"silver ball", "ball"}),
        "A little silver ball decorates the end of each peg. It " +
        "is plain and smooth to the touch.\n");
    add_item(({"quill", "quills"}),
        "The quills are fashioned from eagle feathers with a " +
        "sharp tip at the ends. There are traces of ink on " +
        "their tips.\n"); 
    add_item("inkpot",
        "The inkpot is small and half full of black ink. Traces" +
        "of ink are on the edges of the pot where excess ink " +
        "has been tapped off of the quills.\n");
    add_item(({"feathers", "eagle feathers"}),
        "The feathers are dark brown and golden colored. Such " +
        "magnificent feathers can only be a gift from a noble " +
        "creature.\n");
    add_item(({"bed","small bed"}),
        "The bed is small, constructed of strong maple and " +
        "polished to a golden shine. The grain of the wood " +
        "stands out nicely in contrast with the mattress, " +
        "bedcover, and pillows.\n");
    add_item("mattress",
        "The mattress is thick and comfortable looking. It is full of " +
        "feathers and covered with a white cotton linen cloth.\n");
    add_item(({"bedcover", "large bedcover"}),
        "The bedcover is dark green and covered with a leaf motif. " +
        "It is thick and luxurious and stuffed with down feathers. " +
        "The bedcover is spread across the bed.\n");
    add_item(({"pillows", "pillow"}),
        "Several soft pillows sit on the bed. They are bright " +
        "purple and are decorated with a leaf motif.\n");

    add_item(({"south window", "southern window"}), 
        "@@south_down@@\n");
    set_extra_window("@@window_position@@ set into the " +
        "south wall.");
    add_cmd_item(({"curtains", "drapes"}), "close",
        "@@close_curtains@@");
    add_cmd_item(({"curtains", "drapes"}), "open",
            "@@open_curtains@@");
    add_item("cord",
        "The cord is silver. It gathers the curtains and " +
        "attaches to the wall, keeping them open.\n");

    num_of_windows=2;

    add_cmd_item(({"hats", "hat", "coat", "coats"}), 
    ({"take", "get"}), "@@get_hat@@");


    reset_shire_room();

    add_exit(VALLEY_DIR + "d_cor08", "north");
    add_exit(VALLEY_DIR + "garden08",  "south");
}


void
reset_shire_room()
{

    if (!bilbo)
	bilbo = clone_object(RNPC_DIR + "bilbo");
    if (!present(bilbo,this_object()))
	bilbo->move(this_object());

}

string get_hat()
{
    return "You start to take it, but decide not to since it " +
        "doesn't belong to you.\n";
}
