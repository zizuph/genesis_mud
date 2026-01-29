/*
 * Den in the vampire manor
 * Louie 2006
 */  
#pragma strict_types
#include "defs.h"

inherit VAMP_ROOM_DIR + "vamp_room";

#include <stdproperties.h>

void
create_vamp_room()
{
    set_short("den");
    set_long("This small room used to function as a den, but now it "+
        "is cleared and abandoned.  "+
        "The only items left in the room is a large wooden desk "+
        "and an empty bookcase.  "+
        "\n");

    add_exit("entry.c", "south");

    add_item(({"bookcase","book case","case","empty bookcase",
        "empty case"}),
        "The bookcase is made of wood and appears well constructed, with "+
        "a large mirror providing an elegant backing to the many "+
        "empty shelves.\n");

    add_item(({"den"}),
        "You are standing in the den of the manor.  "+
        "It is empty except for the large wooden desk and the "+
        "empty bookcase.\n");

    add_item(({"mirror"}),
        "The mirror is extremely polished and provides an excellent "+
        "reflection.  When you look at something in the mirror, "+
        "its image appears backwards.\n");

    add_item(({"shelves","book shelves"}),
        "The shelves of the bookcase are empty and "+
        "surprisingly clear of any dust, although one of the shelves "+
        "appears to have a carving etched into it.\n");

    add_item(({"shelves in mirror","shelves through mirror",
        "shelves in the mirror","shelves through the mirror",
        "book shelves through mirror","book shelves in mirror",
        "book shelves through the mirror",
        "book shelves in the mirror"}),
        "The shelves appear the same when viewed through the mirror, "+
        "empty and surprisingly clear of dust.  The carving etched "+
        "the shelf still appears visible as well.\n");
    
    add_item(({"bookcase in mirror","bookcase in the mirror",
        "bookcase through the mirror","bookcase through mirror"}),
        "The bookcase is too large to view through the mirror, but "+
        "you do not see anything special about it when viewing its "+
        "reflection.\n");

    add_item(({"carving","shelf","carving on shelf"}),
        "The shelf has a carving that appears to have wavy lines "+
        "representing water, with a small "+
        "girl flying over it.  Small circles, perhaps tears, fall "+
        "from the child into the water.\n");

    add_item(({"carving through mirror","carving in mirror",
        "carving in the mirror","carving through the mirror",
        "shelf in the mirror","shelf through the mirror","shelf in mirror",
        "shelf through mirror","carving on shelf through mirror",
        "carving on shelf through the mirror",
        "carving on the shelf through mirror",
        "carving on the shelf through the mirror",
        "carving on shelf in mirror",
        "carving on shelf in the mirror",
        "carving on the shelf in mirror",
        "carving on the shelf in the mirror"}),
        "Looking at the carving on the shelf through the mirror, "+
        "it appears there "+
        "are wavy lines representing water, with a small girl laying "+
        "helpless under the waves.  Small circles, perhaps her last "+
        "breath, float up from her body to the top of the water.\n");

    add_item(({"desk","large desk","wooden desk"}),
        "The large wooden desk has nothing special about it.\n");

    add_item(({"desk in mirror","desk in the mirror",
        "desk through mirror","desk through the mirror"}),
        "Looking at the desk through the mirror does not make it any "+
        "more interesting, it is simply backwards.\n");

    add_item(({"me in mirror","myself in mirror"}),
        "Looking at yourself in the mirror, you see nothing special.\n");

    add_item(({"south","hall","entry hall","main hall"}),
        "To the south is the entry hall of the manor.\n");

}
