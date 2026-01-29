/* Castle_room09-The Library.
 * Coded by Marisol (09/11/98)
 * Copyright (c) Marisol Ramos 1998
 */

#pragma strict_types
#include "defs.h"
inherit CASTLE_OV;

void
create_castle_room()
{

    set_short("The Library");
    set_long("This is the library of this residence. Rows upon "+
        "rows of books are lined on redwood bookcases. A small "+
        "fireplace is set at the end of the room giving warm "+
        "to any guest reading on the comfortable couches and "+
        "sofas place tastefully all around the room. Footstools are "+
        "place in front of the couches for the comfort of guests with "+
        "weary feet. Torches are lit to provide good light for "+
        "reading. Nice rugs absorbe the noise of walking feet "+
        "making reading a pleasure in this room. A tall stained-glass "+
        "window graces the wall adjacent to the fireplace.\n");

    add_item("books",
        "Leather-bound books are set rows upon rows in the wooden "+
        "bookcase. The books are from different languages and topics: "+
        "elvish and common tongue books, geography and philosophy "+
        "are some of the books found here.\n");

    add_item(({"redwood bookcases", "bookcases"}),
        "Tall redwood bookcases rest in the walls of the library. The "+
        "wood has a rich red color that is characteristic from this "+
        "type of lumber.\n");

    add_item("fireplace",
        "A small, cheery fireplace. It is burning and warm heat is "+
        "coming from it, warming the body and soul.\n");

    add_item(({"couches", "sofas"}),
        "Really plush and soft couches and sofas are place strategically "+
        "to offer the best comfort while reading in this room. They "+
        "are russet in color, matching perfectly with the redwood "+
        "of the bookcases. They are perfect to read and to take a nap "+
        "too.\n");

    add_item("rugs",
        "These rugs are so thick that you can't only hear your "+
        "footsteps, you can't either see your feet. They are plaid "+
        "in color, with green, red, yellow and orange all weave "+
        "together to give a lively look to this room\n");

    add_item(({"stained-glass window", "window"}),
        "A tall stained-glass window is set in the wall on top of the "+
        "fireplace. This window looks like the ones set "+     
        "in the walls of the foyer. The design for this one, though "+
        "is not a mythological beast, but a natural animal, in this "+
        "case a lyre bird.\n");

    add_item(({"lyre bird", "bird"}),
        "A bright colored lyre bird. The tail' feathers of this bird "+
        "look like the namesake musical instrument. Two long yellow and "+
        "black feathers rise at the base of the tail. Many fluffy feathers "+
        "rise in the middle of the two long ones like the strings of "+
        "that instrument.\n");

    add_exit("castle1_04.c", "east");

    reset_room();
}                                                            
